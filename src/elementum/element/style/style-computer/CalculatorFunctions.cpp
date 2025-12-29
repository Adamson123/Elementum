#include "StyleComputer.hpp"
#include "../../Element.hpp"

Position StyleComputer::calculateStartPosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;
    Element *prevSibling = element->prevSibling;

    auto computeAxis = [&](StartPosition startPos, float parentPos, float prevSiblingPos, float windowPos) -> float
    {
        switch (startPos)
        {
        case StartPosition::PARENT:
            return parent ? parentPos : 0.f;
        case StartPosition::PREV_SIBLING:
            return prevSiblingPos;
        default:
            return 0.f;
        }
    };

    float parentX = parent ? parent->computedStyle.x : 0.f;
    float parentY = parent ? parent->computedStyle.y : 0.f;

    float prevSiblingX = element->prevSibling ? prevSibling->computedStyle.x + prevSibling->computedStyle.width : 0.f;
    float prevSiblingY = element->prevSibling ? prevSibling->computedStyle.y + prevSibling->computedStyle.height : 0.f;

    Position startPos;
    startPos.x = computeAxis(element->style.getStartX(), parentX, prevSiblingX, 0.f);
    startPos.y = computeAxis(element->style.getStartY(), parentY, prevSiblingY, 0.f);
    return startPos;
}

Position StyleComputer::calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](float value, Unit unit, float startPos, float parentSize, float windowSize) -> float
    {
        // If the unit is percent, calculate based on parent position and size or window size
        // If the unit is px, add directly to parent position
        if (unit == Unit::PERCENT)
        {
            if (parent)
                return startPos + (value / 100.f) * parentSize;
            else
                return startPos + (value / 100.f) * windowSize;
        }
        else // px
        {
            return startPos + value;
        }
    };

    float parentX = parent ? parent->computedStyle.x : 0.f;
    float parentY = parent ? parent->computedStyle.y : 0.f;
    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    // ComputedStartPos startPos = calculateStartPosition(element, currentWindowWidth, currentWindowHeight);

    Position pos;
    pos.x = computeAxis(element->style.x, element->style.unit.x, element->computedStyle.x, parentWidth, currentWindowWidth);
    pos.y = computeAxis(element->style.y, element->style.unit.y, element->computedStyle.y, parentHeight, currentWindowHeight);
    return pos;
}

Size StyleComputer::calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](float value, Unit unit, float parentSize, float windowSize) -> float
    {
        // If the unit is percent, calculate based on parent size or window size
        // If the unit is px, return the value directly
        if (unit == Unit::PERCENT)
        {
            if (parent)
                return (value / 100) * parentSize;
            else
                return (value / 100) * windowSize;
        }
        else
        {
            return value;
        }
    };

    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    Size size;
    size.width = computeAxis(element->style.width, element->style.unit.width, parentWidth, currentWindowWidth);
    size.height = computeAxis(element->style.height, element->style.unit.height, parentHeight, currentWindowHeight);
    return size;
}

float StyleComputer::calculateBorderWidth(Element *element)
{
    Element *parent = element->parent;

    float value = element->style.borderWidth;
    Unit unit = element->style.unit.borderWidth;

    if (unit == Unit::PERCENT)
    {
        float parentSize = parent ? (parent->computedStyle.width + parent->computedStyle.height) / 2.f : (element->computedStyle.width + element->computedStyle.height) / 2.f;
        return (value / 100.f) * parentSize;
    }
    else
    {
        return value;
    }
}