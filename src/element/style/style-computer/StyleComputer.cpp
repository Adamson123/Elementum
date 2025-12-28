#include "./StyleComputer.hpp"
#include "../../Element.hpp"

void StyleComputer::computePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Position pos = calculatePosition(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.x = pos.x;
    element->computedStyle.y = pos.y;
    element->x = pos.x;
    element->y = pos.y;
}

void StyleComputer::computeSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Size size = calculateSize(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.width = size.width;
    element->computedStyle.height = size.height;
    element->width = size.width;
    element->height = size.height;
}

void StyleComputer::computeBorderWidth(Element *element)
{
    float borderWidth = calculateBorderWidth(element);
    element->computedStyle.borderWidth = borderWidth;
}