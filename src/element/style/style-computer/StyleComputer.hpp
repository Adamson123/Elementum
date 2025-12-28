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

struct ComputedStartPos
{
    float startX;
    float startY;
};

class Element;

class StyleComputer
{
public:
    void compute(Element *element, float currentWindowWidth, float currentWindowHeight);

private:
    void computePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeBorderWidth(Element *element);

    // Calculator functions will return computed values
    Position calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    Size calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    ComputedStartPos calculateStartPosition(Element *element, float currentWindowWidth, float currentWindowHeight);

    float calculateBorderWidth(Element *element);
};
