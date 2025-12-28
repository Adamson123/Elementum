#pragma once

class ComputedStyle
{
private:
    float width;
    float height;
    float x;
    float y;
    float borderWidth;

    friend class Painter;
    friend class StyleComputer;
    friend class Element;
};
