#include "./StyleComputer.hpp"
#include "../../Element.hpp"

void StyleComputer::computePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](float value, Unit unit, float parentStart, float parentSize, float windowSize) -> float
    {
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

    element->computedStyle.x = computeAxis(element->style.x, element->style.unit.x, parentX, parentWidth, currentWindowWidth);
    element->computedStyle.y = computeAxis(element->style.y, element->style.unit.y, parentY, parentHeight, currentWindowHeight);
}

void StyleComputer::computeSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Element *parent = element->parent;

    auto computeAxis = [&](float value, Unit unit, float parentSize, float windowSize) -> float
    {
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

    element->computedStyle.width = computeAxis(element->style.width, element->style.unit.width, parentWidth, currentWindowWidth);
    element->computedStyle.height = computeAxis(element->style.height, element->style.unit.height, parentHeight, currentWindowHeight);
}

void StyleComputer::computeBorderWidth(Element *element)
{

    if (element->style.unit.borderWidth == Unit::PERCENT)
    {
        element->computedStyle.borderWidth = (element->style.borderWidth / 100) * element->computedStyle.width;
    }
    else
    {
        element->computedStyle.borderWidth = element->style.borderWidth;
    }
}