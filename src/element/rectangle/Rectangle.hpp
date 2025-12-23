#pragma once
#include "../Element.hpp"
#include "../window/Window.hpp"

class Window;

class Rectangle : public Element
{
public:
    Rectangle(float x, float y, float width, float height) : Element(x, y, width, height) {};

    Window *window = nullptr;

    void assignToClickedElement(int mouseX, int mouseY);
};