#pragma once

struct Position
{
    float x;
    float y;
};

struct Size
{
    float width;
    float height;
};

class Element;

class StyleComputer
{
public:
    void computePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeBorderWidth(Element *element);

private:
    // Calculator functions will return computed values
    Position calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    Size calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    float calculateBorderWidth(Element *element);
};
