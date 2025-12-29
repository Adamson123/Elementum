#pragma once
#include "../Element.hpp"

class Widget;

/**
 * The Window class, derived from Element, represents a UI window that can contain child widgets, track which element was clicked, and handle click events at specific coordinates.
 *  It provides methods for creating widgets as children and maintains its type as UIType::WINDOW.
 *
 */
class Window : public Element
{
public:
    Window(float x, float y, float width, float height);

    // Pointer to the element that was clicked within the window
    Element *clickedElement = nullptr;

    /** Creates a new Widget as a child of the Window */
    std::unique_ptr<Widget> createWidget(float x = 0, float y = 0, float width = 0, float height = 0);

    // TODO:
    /** Handles a click event within the window at the specified coordinates */
    void handleClickWithIn(float mouseX, float mouseY);
    // TODO:
    //  void onWindowResize(float newWidth, float newHeight);

private:
    UIType type = UIType::WINDOW;
};