#include "StyleComputer.hpp"
#include "../../Element.hpp"
#include <optional>
#include <vector>
#include <iostream>

float computeAxis(Element *parent, std::optional<float> value, Unit unit, float parentSize, float windowSize)
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

Size StyleComputer::calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    Size size;
    // Example:
    // if width is 50% and parent width is 200px, then width = 50/100 * 200 = 100px;
    size.width = computeAxis(parent, element->style.width, element->style.unit.width, parentWidth, currentWindowWidth);
    size.height = computeAxis(parent, element->style.height, element->style.unit.height, parentHeight, currentWindowHeight);

    return size;
}

//
Margin StyleComputer::calculateMargin(Element *element, float currentWindowWidth, float currentWindowHeight)
{

    Element *parent = element->parent;
    // Element *parent = element->parent;
    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    Margin margin;
    // Example:
    // if margin left is 10% and parent width is 200px, then margin left = 10/100 * 200 = 20px;
    margin.margin = computeAxis(parent, element->style.margin, element->style.unit.margin, parentWidth, currentWindowWidth);
    margin.marginLeft = element->style.marginLeft.has_value() ? computeAxis(parent, element->style.marginLeft, element->style.unit.marginLeft, parentWidth, currentWindowWidth) : margin.margin;
    margin.marginRight = element->style.marginRight.has_value() ? computeAxis(parent, element->style.marginRight, element->style.unit.marginRight, parentWidth, currentWindowWidth) : margin.margin;
    margin.marginTop = element->style.marginTop.has_value() ? computeAxis(parent, element->style.marginTop, element->style.unit.marginTop, parentHeight, currentWindowHeight) : margin.margin;
    margin.marginBottom = element->style.marginBottom.has_value() ? computeAxis(parent, element->style.marginBottom, element->style.unit.marginBottom, parentHeight, currentWindowHeight) : margin.margin;

    return margin;
}

Element *StyleComputer::findVisiblePrevElement(Element *element)
{
    for (Element *sibling = element->prevSibling; sibling != nullptr; sibling = sibling->prevSibling)
    {
        if (sibling->style.getDisplay() != Display::NONE)
        {
            return sibling;
        }
    }
    return nullptr;
}

// RULE: if we are adding previuos element computed position, we do not add parent position again.
void StyleComputer::handleInlineBlock(Element *element, Element *visiblePrevElement, Position &pos)
{
    Element *parent = element->parent;
    float parentY = parent ? parent->computedStyle.y : 0.0f;
    float parentX = parent ? parent->computedStyle.x : 0.0f;

    if (!visiblePrevElement)
    {
        // If there's no visible previous element, position relative to parent plus margin
        pos.x = parentX + element->computedStyle.marginLeft;
        pos.y = parentY + element->computedStyle.marginTop;
        return;
    }

    if (visiblePrevElement->style.display == Display::BLOCK)
    {

        pos.x = parentX + element->computedStyle.marginLeft;
        /* Position below the previous block element, by adding the previous element's height + bottom margin + top margin of the current element */
        pos.y = visiblePrevElement->computedStyle.y + visiblePrevElement->computedStyle.height + visiblePrevElement->computedStyle.marginBottom + element->computedStyle.marginTop;
    }

    if (visiblePrevElement->style.display == Display::INLINE_BLOCK)
    {
        /* Position to the right of the previous inline-block element, by adding the previous element's width + right margin + left margin of the current element */
        pos.x = visiblePrevElement->computedStyle.x + visiblePrevElement->computedStyle.width + visiblePrevElement->computedStyle.marginRight + element->computedStyle.marginLeft;
        /* Position aligned vertically with the previous inline-block element, remove the top margin of the previous element and add the top margin of the current element */
        pos.y = (visiblePrevElement->computedStyle.y - visiblePrevElement->computedStyle.marginTop) + element->computedStyle.marginTop;
    }
}

Element *findPrevElementWithLargestHeight(Element *element)
{

    if (element->prevSibling->style.getDisplay() == Display::BLOCK)
    {
        return element->prevSibling;
    }

    Element *parent = element->parent;
    float largestHeight = 0.0f;
    Element *targetElement = nullptr;

    for (Element *sibling = element->prevSibling; sibling != nullptr; sibling = sibling->prevSibling)
    {

        if (sibling->style.getDisplay() == Display::INLINE_BLOCK)
        {
            if (sibling->getHeight() > largestHeight)
            {
                largestHeight = sibling->getHeight();
                targetElement = sibling;
            }
        }

        if (sibling->style.getDisplay() == Display::BLOCK)
        {
            break;
        }
    }

    return targetElement;
}

void StyleComputer::handleBlock(Element *element, Element *visiblePrevElement, Position &pos)
{
    Element *parent = element->parent;
    float parentY = parent ? parent->computedStyle.y : 0.0f;
    float parentX = parent ? parent->computedStyle.x : 0.0f;

    if (!visiblePrevElement)
    {
        // If there's no visible previous element, position relative to parent plus margin
        pos.x = parentX + element->computedStyle.marginLeft;
        pos.y = parentY + element->computedStyle.marginTop;
    }

    if (visiblePrevElement)
    {

        pos.x = parentX + element->computedStyle.marginLeft;
        /*
             if previous element is block we will just use it
             Else if it's inline-block we will find the prev element with the largest height until we get to a block element
             */
        Element *targetElement = findPrevElementWithLargestHeight(element);
        // if (targetElement)
        pos.y = targetElement->computedStyle.y + targetElement->computedStyle.height + targetElement->computedStyle.marginBottom + element->computedStyle.marginTop;
        // else
        //     pos.y = visiblePrevElement->computedStyle.y + visiblePrevElement->computedStyle.height + visiblePrevElement->computedStyle.marginBottom + element->computedStyle.marginTop;
    }
}

Position StyleComputer::calculateDisplay(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;
    Element *visiblePrevElement = findVisiblePrevElement(element);

    Position pos;

    // TODO: Or if parent is flex
    if (element->style.display == Display::INLINE_BLOCK)
    {
        handleInlineBlock(element, visiblePrevElement, pos);
    }
    else if (element->style.display == Display::BLOCK)
    {
        handleBlock(element, visiblePrevElement, pos);
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