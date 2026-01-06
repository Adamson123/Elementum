#pragma once

/** Represents the computed style properties of an element after applying all style rules and calculations */
class ComputedStyle
{
private:
    float width;
    float height;

    float margin;
    float marginLeft;
    float marginRight;
    float marginTop;
    float marginBottom;
    float x;
    float y;

    float borderWidth;

    friend class Painter;
    friend class StyleComputer;
    friend class Element;
};
