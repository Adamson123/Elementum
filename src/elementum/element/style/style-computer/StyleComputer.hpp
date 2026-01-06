#pragma once
#include <string>
#include <vector>

struct Position
{
    float x;
    float y;
};

struct Margin
{
    float margin;
    float marginLeft;
    float marginRight;
    float marginTop;
    float marginBottom;
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
    /** Computes the size of the element based on the current window dimensions. */
    void computeSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the position of the element based on the current window dimensions. */
    void computePosition(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the display position of the element based on the current window dimensions. */
    // void computeDisplay(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Computes the border width of the element based on its styles. */
    void computeBorderWidth(Element *element);

    // Calculator functions will return computed values:

    /** Calculates the size of the element based on the current window dimensions. */
    Size calculateSize(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Calculates the position of the element based on the current window dimensions. */
    Margin calculateMargin(Element *element, float currentWindowWidth, float currentWindowHeight);
    /** Calculates the display position of the element based on the current window dimensions. */
    Position calculateDisplay(Element *element, float currentWindowWidth, float currentWindowHeight);
    Element *findVisiblePrevElement(Element *element);
    void handleInlineBlock(Element *element, Element *visiblePrevElement, Position &pos);
    void handleBlock(Element *element, Element *visiblePrevElement, Position &pos);
    float findLargestVerticalMargin(std::vector<Element *> &elements, std::string direction);

    /** Calculates the border width of the element based on its styles. */
    float calculateBorderWidth(Element *element);
};
