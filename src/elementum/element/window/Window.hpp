#pragma once
#include "../Element.hpp"

class Widget;

/**
 * The Window class, derived from Element, represents a UI window that can contain child widgets, track user interactions like clicks.
 *  It provides methods for creating widgets as children and maintains its type as UIType::WINDOW.
 *
 */
class Window : public Element
{
public:
    Window(float width, float height);

    // Pointer to the element that was clicked within the window
    Element *clickedElement = nullptr;

    /** Creates a new Widget as a child of the Window */
    std::unique_ptr<Widget> createWidget();

    // TODO:
    /** Handles a click event within the window at the specified coordinates */
    void handleClickWithIn(float mouseX, float mouseY);
    // TODO:
    //  void onWindowResize(float newWidth, float newHeight);

private:
    UIType type = UIType::WINDOW;
};