#include "./style/Style.hpp"
#include "./Element.hpp"

void Element::setWidth(float value, Unit unit)
{
    style.width = value;
    style.unit.width = unit;
    layoutDirty = true;
    // paintDirty = true;
}

void Element::setHeight(float value, Unit unit)
{
    style.height = value;
    style.unit.height = unit;
    layoutDirty = true;
    // paintDirty = true;
}

void Element::setMargin(float value, Unit unit)
{
    style.margin = value;
    style.unit.margin = unit;
    layoutDirty = true;
    // paintDirty = true;
}

void Element::setMarginLeft(float value, Unit unit)
{
    style.marginLeft = value;
    style.unit.marginLeft = unit;
    layoutDirty = true;
    // paintDirty = true;
}
void Element::setMarginRight(float value, Unit unit)
{
    style.marginRight = value;
    style.unit.marginRight = unit;
    layoutDirty = true;
    // paintDirty = true;
}
void Element::setMarginTop(float value, Unit unit)
{
    style.marginTop = value;
    style.unit.marginTop = unit;
    layoutDirty = true;
}

void Element::setMarginBottom(float value, Unit unit)
{
    style.marginBottom = value;
    style.unit.marginBottom = unit;
    layoutDirty = true;
    // paintDirty = true;
}

void Element::setBackgroundColor(SDL_Color color)
{
    style.backgroundColor = color;
    // paintDirty = true;
}

void Element::setBorderColor(SDL_Color color)
{
    style.borderColor = color;
    // paintDirty = true;
}

void Element::setColor(SDL_Color color)
{
    style.color = color;
    // paintDirty = true;
}

void Element::setBorderWidth(float value, Unit unit)
{
    style.borderWidth = value;
    style.unit.borderWidth = unit;
    layoutDirty = true;
    // paintDirty = true;
}

void Element::setFontSize(int size)
{
    style.fontSize = size;
    // paintDirty = true;
    // textDirty = true;
}
void Element::setFontFamily(const std::string &family)
{
    style.fontFamily = family;
    // paintDirty = true;
    // textDirty = true;
}
void Element::setDisplay(Display display)
{
    style.display = display;
    layoutDirty = true;
    // paintDirty = true;
}

// void Element::setStartX(StartPosition startX)
// {
//     style.startX = startX;
//     layoutDirty = true;
// }

// void Element::setStartY(StartPosition startY)
// {
//     style.startY = startY;
//     layoutDirty = true;
// }