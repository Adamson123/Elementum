#include "./StyleComputer.hpp"
#include "../../Element.hpp"
#include <iostream>

void StyleComputer::compute(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    // computeStartPosition(element, currentWindowWidth, currentWindowHeight);
    computeSize(element, currentWindowWidth, currentWindowHeight);
    computePosition(element, currentWindowWidth, currentWindowHeight);
    computeBorderWidth(element);
}

void StyleComputer::computeSize(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Size size = calculateSize(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.width = size.width;
    element->computedStyle.height = size.height;
}

std::vector<Element *> findAllPrevElementInRow(Element *element)
{
    std::vector<Element *> elements;
    for (Element *sibling = element; sibling != nullptr; sibling = sibling->prevSibling)
    {
        if (sibling->style.getDisplay() == Display::INLINE_BLOCK)
        {
            elements.push_back(sibling);
        }
        else if (sibling->style.getDisplay() == Display::BLOCK)
        {
            break;
        }
    }
    return elements;
}

float StyleComputer::findLargestVerticalMargin(std::vector<Element *> &elements, std::string direction)
{
    float largestMargin = 0.0f;

    for (Element *el : elements)
    {
        float marginValue = 0.0f;
        if (direction == "top")
        {
            marginValue = el->computedStyle.marginTop;
        }
        else if (direction == "bottom")
        {
            marginValue = el->computedStyle.marginBottom;
        }

        if (marginValue > largestMargin)
        {
            largestMargin = marginValue;
        }
    }

    return largestMargin;
}

void StyleComputer::computePosition(Element *element, float currentWindowWidth, float currentWindowHeight)
{
    Margin margin = calculateMargin(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.margin = margin.margin;
    element->computedStyle.marginLeft = margin.marginLeft;
    element->computedStyle.marginRight = margin.marginRight;
    element->computedStyle.marginTop = margin.marginTop;
    element->computedStyle.marginBottom = margin.marginBottom;

    Element *visiblePrevElement = findVisiblePrevElement(element);

    Position pos = calculateDisplay(element, currentWindowWidth, currentWindowHeight);
    element->computedStyle.x = pos.x; // parentX + pos.x; // visiblePrevElement ? pos.x : parentX + pos.x;
    element->computedStyle.y = pos.y; // visiblePrevElement ? pos.y : parentY + pos.y;

    //  Align vertical margin
    if (element->style.display == Display::INLINE_BLOCK)
    {
        std::vector<Element *> elements = findAllPrevElementInRow(element);
        float largestTopMargin = findLargestVerticalMargin(elements, "top");
        float largestBottomMargin = findLargestVerticalMargin(elements, "bottom");

        for (auto &el : elements)
        {
            el->computedStyle.y = el->computedStyle.y + (largestTopMargin - el->computedStyle.marginTop);
            el->computedStyle.marginTop = largestTopMargin;
            el->computedStyle.marginBottom = largestBottomMargin;
        }
    }

    if (element->style.display == Display::BLOCK && !element->style.width.has_value())
    {
        element->computedStyle.width = element->parent->computedStyle.width - (element->computedStyle.marginLeft + element->computedStyle.marginRight);
    }

    std::cout << "Element X: " << element->computedStyle.x << " Y: " << element->computedStyle.y << ", className: " << element->className << std::endl;
}

void StyleComputer::computeBorderWidth(Element *element)
{
    float borderWidth = calculateBorderWidth(element);
    element->computedStyle.borderWidth = borderWidth;
}