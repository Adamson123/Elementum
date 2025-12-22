#pragma once
#include "../Element.hpp"
#include "../window/Window.hpp"

class Rectangle : public Element
{
public:
    Rectangle(float x, float y, float width, float height) : Element(x, y, width, height) {};

    Window *window;

    void assignToClickedElement(int mouseX, int mouseY)
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
};