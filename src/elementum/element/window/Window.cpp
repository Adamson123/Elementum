#include <memory>
#include <iostream>
#include "Window.hpp"
#include "../Element.hpp"
#include "../widget/Widget.hpp"

Window::Window(float x, float y, float width, float height) : Element(x, y, width, height) {}

std::unique_ptr<Widget> Window::createWidget(float x, float y, float width, float height)
{
    auto widget = std::make_unique<Widget>(x, y, width, height);

    widget->window = this;
    widget->styleApplier = styleApplier;
    widget->painter = painter;
    widget->styleComputer = styleComputer;

    return std::move(widget);
}

void Window::handleClickWithIn(float mouseX, float mouseY)
{
    std::vector<Element *> sortedChildren = getSortedChildren();

    for (auto &child : sortedChildren)
    {
        if (auto widget = dynamic_cast<Widget *>(child))
        {
            widget->assignToClickedElement(mouseX, mouseY);
        }
    }

    if (clickedElement)
    {
        std::cout << "From " + clickedElement->className << std::endl;
        if (auto clickedWidget = dynamic_cast<Widget *>(clickedElement))
        {
            clickedWidget->propagateClick();
        }
        clickedElement = nullptr;
    }
    else
    {
        std::cout << "No Widgets were clicked" << std::endl;
        if (onClick)
            onClick();
    }
}
