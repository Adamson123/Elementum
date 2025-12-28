#include "StyleComputer.hpp"
#include "../../Element.hpp"

Position StyleComputer::calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](float value, Unit unit, float parentStart, float parentSize, float windowSize) -> float
    {
        // If the unit is percent, calculate based on parent position and size or window size
        // If the unit is px, add directly to parent position
        if (unit == Unit::PERCENT)
        {
            if (parent)
                return parentStart + (value / 100.f) * parentSize;
            else
                return (value / 100.f) * windowSize;
        }
        else // px
        {
            if (parent)
                return parentStart + value;
            else
                return value;
        }
    };

    float parentX = parent ? parent->computedStyle.x : 0.f;
    float parentY = parent ? parent->computedStyle.y : 0.f;
    float parentWidth = parent ? parent->computedStyle.width : currentWindowWidth;
    float parentHeight = parent ? parent->computedStyle.height : currentWindowHeight;

    Position pos;
    pos.x = computeAxis(element->style.x, element->style.unit.x, parentX, parentWidth, currentWindowWidth);
    pos.y = computeAxis(element->style.y, element->style.unit.y, parentY, parentHeight, currentWindowHeight);
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