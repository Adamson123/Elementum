#include "StyleComputer.hpp"
#include "../../Element.hpp"
#include <optional>

Position StyleComputer::calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](std::optional<float> value, Unit unit, float parentSize, float windowSize) -> float
    {
        // If the unit is percent, calculate based on parent position and size or window size
        // If the unit is px, add directly to parent position
        if (unit == Unit::PERCENT)
        {
            if (parent)
                return (value.value_or(0.f) / 100.f) * parentSize;
            else
                return (value.value_or(0.f) / 100.f) * windowSize;
        }
        else // px
        {
            return value.value_or(0.f);
        }
    };

    float parentX = parent ? parent->computedStyle.x : 0.f;
    float parentY = parent ? parent->computedStyle.y : 0.f;
    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    // ComputedStartPos startPos = calculateStartPosition(element, currentWindowWidth, currentWindowHeight);

    Position pos;
    pos.x = computeAxis(element->style.x, element->style.unit.x, parentWidth, currentWindowWidth);
    pos.y = computeAxis(element->style.y, element->style.unit.y, parentHeight, currentWindowHeight);
    return pos;
}

Size StyleComputer::calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](std::optional<float> value, Unit unit, float parentSize, float windowSize) -> float
    {
        // If the unit is percent, calculate based on parent size or window size
        // If the unit is px, return the value directly
        if (unit == Unit::PERCENT)
        {
            if (parent)
                return (value.value_or(0.f) / 100) * parentSize;
            else
                return (value.value_or(0.f) / 100) * windowSize;
        }
        else
        {
            return value.value_or(0.f);
        }
    };

    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    Size size;
    size.width = computeAxis(element->style.width, element->style.unit.width, parentWidth, currentWindowWidth);
    size.height = computeAxis(element->style.height, element->style.unit.height, parentHeight, currentWindowHeight);
    return size;
}

Element *findPrevElementWithDisplay(Display display, Element *element)
{
    for (Element *sibling = element->prevSibling; sibling != nullptr; sibling = sibling->prevSibling)
    {
        if (sibling->style.getDisplay() == display)
        {
            return sibling;
        }
    }
    return nullptr;
}

Element *findPrevElementThatIsNotWithDisplay(Display display, Element *element)
{
    for (Element *sibling = element->prevSibling; sibling != nullptr; sibling = sibling->prevSibling)
    {
        if (sibling->style.getDisplay() != display)
        {
            return sibling;
        }
    }
    return nullptr;
}

Element *findPrevElementMostClosestToBottom(Element *element)
{
    Element *closest = nullptr;
    float closestBottom = -1.0f;

    for (Element *sibling = element->prevSibling; sibling != nullptr; sibling = sibling->prevSibling)
    {
        float siblingBottom = sibling->getY() + sibling->getHeight();
        if (siblingBottom > closestBottom)
        {
            closestBottom = siblingBottom;
            closest = sibling;
        }
    }

    return closest;
}

Position StyleComputer::calculateDisplay(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;
    Element *prevSibling = findPrevElementThatIsNotWithDisplay(Display::NONE, element); // element->prevSibling;

    Display display = element->style.display;
    Position pos;

    float parentX = parent ? parent->computedStyle.x : 0;
    float parentY = parent ? parent->computedStyle.y : 0;

    float elementX = element->computedStyle.x;
    float elementY = element->computedStyle.y;

    // If no prevSibling, let start position default to parent
    if (!prevSibling)
    {
        pos.x = elementX + parentX;
        pos.y = elementY + parentY;
    }
    else
    {
        Element *closestToBottom = findPrevElementMostClosestToBottom(element);
        float prevSiblingRight = closestToBottom->computedStyle.x + closestToBottom->computedStyle.width;   // prevSibling->computedStyle.x + prevSibling->computedStyle.width;
        float prevSiblingBottom = closestToBottom->computedStyle.y + closestToBottom->computedStyle.height; // prevSibling->computedStyle.y + prevSibling->computedStyle.height;

        Element *prevSiblingBlock = findPrevElementWithDisplay(Display::BLOCK, element);

        // DISPLAY, INLINE_BLOCK
        if (display == Display::INLINE_BLOCK)
        {
            // If prevSibling is inline block
            if (prevSibling->style.display == Display::INLINE_BLOCK)
            {
                pos.x = elementX + prevSiblingRight;
                // Element y should be relative to prev last block element bottom else to the parent y
                pos.y = elementY + (prevSiblingBlock ? prevSiblingBlock->computedStyle.y + prevSiblingBlock->computedStyle.height : parentY);
            }

            // If prevSibling is block
            if (prevSibling->style.display == Display::BLOCK)
            {
                pos.x = elementX + parentX;
                pos.y = elementY + prevSiblingBottom;
            }
        }

        // DISPLAY, BLOCK
        if (display == Display::BLOCK)
        {
            if (!element->style.width.has_value())
                element->computedStyle.width = parent ? (parent->computedStyle.width - elementX) : (currentWindowWidth - elementX);

            pos.x = elementX + parentX;
            pos.y = elementY + prevSiblingBottom;
            // element->computedStyle.width = parent ? parent->computedStyle.width : currentWindowWidth;
            // element->computedStyle.width = currentWindowWidth - (pos.x - parentX);
        }

        // DISPLAY, NONE
        // if (display == Display::NONE)
        // {
        //     return pos;
        // }
    }

    return pos;
}

float StyleComputer::calculateBorderWidth(Element *element)
{
    Element *parent = element->parent;

    std::optional<float> value = element->style.borderWidth;
    Unit unit = element->style.unit.borderWidth;

    if (unit == Unit::PERCENT)
    {
        float parentSize = parent ? (parent->computedStyle.width + parent->computedStyle.height) / 2.f : (element->computedStyle.width + element->computedStyle.height) / 2.f;
        return (value.value_or(0.f) / 100.f) * parentSize;
    }
    else
    {
        return value.value_or(0.f);
    }
}