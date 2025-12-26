#pragma once
#include "../Element.hpp"

class Widget;

class Window : public Element
{
public:
    Window(float x, float y, float width, float height);

    Element *clickedElement = nullptr;

    unique_ptr<Widget> createWidget();
    unique_ptr<Widget> createWidget(float x, float y, float width, float height);

    void handleClickWithIn(float mouseX, float mouseY);

private:
    string type = "window";
};