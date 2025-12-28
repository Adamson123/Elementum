#pragma once
#include "../Element.hpp"

class Widget;

class Window : public Element
{
public:
    Window(float x, float y, float width, float height);

    Element *clickedElement = nullptr;

    // unique_ptr<Widget> createWidget();
    unique_ptr<Widget> createWidget(float x = 0, float y = 0, float width = 0, float height = 0);

    void handleClickWithIn(float mouseX, float mouseY);
    // void onWindowResize(float newWidth, float newHeight);

private:
    UIType type = UIType::WINDOW;
};