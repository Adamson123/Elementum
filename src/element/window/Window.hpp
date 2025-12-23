#pragma once
#include "../Element.hpp"
#include "../rectangle/Rectangle.hpp"

#pragma once
#include "../Element.hpp"

class Rectangle;

class Window : public Element
{
public:
    Window(float x, float y, float width, float height);

    Element *clickedElement;

    Rectangle *createRectangle();
    Rectangle *createRectangle(int x, int y, int width, int height);
};