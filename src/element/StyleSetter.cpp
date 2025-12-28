#include "./style/Style.hpp"
#include "./Element.hpp"

void Element::setWidth(float value, Unit unit)
{
    style.width = value;
    style.unit.width = unit;
    layoutDirty = true;
    paintDirty = true;
}

void Element::setHeight(float value, Unit unit)
{
    style.height = value;
    style.unit.height = unit;
    layoutDirty = true;
    paintDirty = true;
}

void Element::setX(float value, Unit unit)
{
    style.x = value;
    style.unit.x = unit;
    layoutDirty = true;
    paintDirty = true;
}

void Element::setY(float value, Unit unit)
{
    style.y = value;
    style.unit.y = unit;
    layoutDirty = true;
    paintDirty = true;
}

void Element::setBackgroundColor(SDL_Color color)
{
    style.backgroundColor = color;
    paintDirty = true;
}

void Element::setBorderColor(SDL_Color color)
{
    style.borderColor = color;
    paintDirty = true;
}

void Element::setColor(SDL_Color color)
{
    style.color = color;
    paintDirty = true;
}

void Element::setBorderWidth(float value, Unit unit)
{
    style.borderWidth = value;
    style.unit.borderWidth = unit;
    layoutDirty = true;
    paintDirty = true;
}

void Element::setFontSize(int size)
{
    style.fontSize = size;
    paintDirty = true;
    textDirty = true;
}
void Element::setFontFamily(const std::string &family)
{
    style.fontFamily = family;
    paintDirty = true;
    textDirty = true;
}