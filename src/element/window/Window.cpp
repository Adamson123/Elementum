#include <memory>
#include <iostream>
#include "Window.hpp"
#include "../Element.hpp"
#include "../widget/Widget.hpp"

using namespace std;

Window::Window(float x, float y, float width, float height) : Element(x, y, width, height) {}

unique_ptr<Widget> Window::createWidget(float x, float y, float width, float height)
{
    auto widget = make_unique<Widget>(x, y, width, height);

    widget->window = this;
    widget->fontManager = fontManager;
    widget->styleApplier = styleApplier;
    widget->painter = painter;
    widget->styleComputer = styleComputer;

    return std::move(widget);
}

void Window::handleClickWithIn(float mouseX, float mouseY)
{
    vector<Element *> sortedChildren = getSortedChildren();

    for (auto &child : sortedChildren)
    {
        if (auto widget = dynamic_cast<Widget *>(child))
        {
            widget->assignToClickedElement(mouseX, mouseY);
        }
    }

    if (clickedElement)
    {
        cout << "From " + clickedElement->className << endl;
        if (auto clickedWidget = dynamic_cast<Widget *>(clickedElement))
        {
            clickedWidget->propagateClick();
        }
        clickedElement = nullptr;
    }
    else
    {
        cout << "No Widgets were clicked" << endl;
        if (onClick)
            onClick();
    }
}
