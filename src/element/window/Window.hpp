#pragma once
#include "../Element.hpp"
#include "../rectangle/Rectangle.hpp"

class Window : public Element
{
public:
    Window(float x, float y, float width, float height);

    Element *clickedElement;

    unique_ptr<Rectangle> createRectangle();
    unique_ptr<Rectangle> createRectangle(int x, int y, int width, int height);
};