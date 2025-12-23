#include "./Rectangle.hpp"

void Rectangle::assignToClickedElement(int mouseX, int mouseY)
{

    auto sortedChildren = getSortedChildren();

    if (isInside(mouseX, mouseY))
    {
        window->clickedElement = this;
    }

    for (auto &child : sortedChildren)
    {
    }
}