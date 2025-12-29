#include "./StyleComputer.hpp"
#include "../../Element.hpp"

void StyleComputer::compute(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    computeStartPosition(element, currentWindowWidth, currentWindowHeight);
    computePosition(element, currentWindowWidth, currentWindowHeight);
    computeSize(element, currentWindowWidth, currentWindowHeight);
    computeBorderWidth(element);
}

void StyleComputer::computeStartPosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Position pos = calculateStartPosition(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.x = pos.x;
    element->computedStyle.y = pos.y;
}

void StyleComputer::computePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Position pos = calculatePosition(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.x = pos.x;
    element->computedStyle.y = pos.y;
}

void StyleComputer::computeSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Size size = calculateSize(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.width = size.width;
    element->computedStyle.height = size.height;
}

void StyleComputer::computeBorderWidth(Element *element)
{
    float borderWidth = calculateBorderWidth(element);
    element->computedStyle.borderWidth = borderWidth;
}