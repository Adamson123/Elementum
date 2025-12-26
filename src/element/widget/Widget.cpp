#include <iostream>
#include "./Widget.hpp"

void Widget::assignToClickedElement(float mouseX, float mouseY)
{

    if (isInside(mouseX, mouseY) && window)
    {
        window->clickedElement = this;
    }

    auto sortedChildren = getSortedChildren();

    if (sortedChildren.size())
    {
        for (auto &child : sortedChildren)
        {
            if (auto widget = dynamic_cast<Widget *>(child))
            {
                widget->assignToClickedElement(mouseX, mouseY);
            }
        }
    }
}

void Widget::propagateClick()
{
    if (onClick)
        onClick();

    if (parent && isPropagateClick)
    {

        // If parent is Widget, continue propagation
        if (auto widget = dynamic_cast<Widget *>(parent))
        {
            widget->propagateClick();
        }
        else if (parent->onClick)
        {
            parent->onClick();
        }
    }
}