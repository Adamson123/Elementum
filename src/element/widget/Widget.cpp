#include <iostream>
#include "./Widget.hpp"

void Widget::assignToClickedElement(float mouseX, float mouseY)
{

    if (isInside(mouseX, mouseY))
    {
        if (window)
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
    // cout << "propagateClick called on: " << className
    //      << " (ptr: " << this << ")" << endl;
    // cout << "onClick is: " << (onClick ? "SET" : "NULL") << endl;

    if (onClick)
    {
        // cout << "Calling onClick..." << endl;
        onClick(); // ← Crash happens here
                   //  cout << "onClick completed" << endl;
    }

    if (parent && isPropagateClick)
    {

        // If parent is Widget, continue propagation
        if (auto widget = dynamic_cast<Widget *>(parent))
        {
            // cout << "PRoppagating\n";
            widget->propagateClick();
        }
        else if (parent->onClick)
        {
            // cout << "PRoppagating SECCCCC\n";
            parent->onClick();
        }
    }
}