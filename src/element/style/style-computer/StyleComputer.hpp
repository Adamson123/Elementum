#pragma once

class Element;

class StyleComputer
{
public:
    void computePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    void computeBorderWidth(Element *element);
};
