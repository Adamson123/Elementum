#pragma once
#include "../Element.hpp"
#include "../window/Window.hpp"

class Window;

/**
 * Represents a user interface widget that inherits from the Element class, providing properties for window association, click propagation, and UI type, as well as methods to handle click assignment and propagation.
 *  The Widget class is constructed with position and size parameters and manages its interaction state within a UI system.
 */
class Widget : public Element
{
public:
    Window *window = nullptr;

    // Determines whether the click event should propagate to parent elements
    bool isPropagateClick = true;

    /** Assigns the widget to the element located at the specified mouse coordinates (mouseX, mouseY). This function is typically used to handle user interactions by associating the widget with the element that was clicked. */
    void assignToClickedElement(float mouseX, float mouseY);
    /** Propagates the click event to parent elements if the propagation flag is set. */
    void propagateClick();

private:
    UIType type = UIType::WIDGET;
};