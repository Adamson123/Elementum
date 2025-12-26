#pragma once
#include "../Element.hpp"
#include "../window/Window.hpp"

class Window;

class Widget : public Element
{
public:
    Widget(float x, float y, float width, float height) : Element(x, y, width, height) {};

    Window *window = nullptr;

    bool isPropagateClick = true;

    void assignToClickedElement(float mouseX, float mouseY);
    void propagateClick();

private:
    string type = "widget";
};