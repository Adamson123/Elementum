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

/**
 * Computes element's style into computed style used for rendering and layout.
 */
class StyleComputer
{
public:
    /** Computes and applies the appropriate styles to the specified Element based on the current window width and height. */
    void compute(Element *element, float currentWindowWidth, float currentWindowHeight);

private:
    /** Computes the start position of the element based on the current window dimensions. */
    void computeStartPosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the position of the element based on the current window dimensions. */
    void computePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the size of the element based on the current window dimensions. */
    void computeSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the border width of the element based on its styles. */
    void computeBorderWidth(Element *element);

    // Calculator functions will return computed values
    /** Calculates the start position of the element based on the current window dimensions. */
    Position calculateStartPosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Calculates the position of the element based on the current window dimensions. */
    Position calculatePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Calculates the size of the element based on the current window dimensions. */
    Size calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Calculates the border width of the element based on its styles. */
    float calculateBorderWidth(Element *element);
};
