
#include <iostream>
#include "Element.hpp"
#include <memory>
#include "../Constants.h"
#include "./FontManager.hpp"
#include "./style/StyleApplier.hpp"
#include "./painter/Painter.hpp"
#include "./style/style-computer/StyleComputer.hpp"

using namespace std;
using namespace Constants;

Element::Element(float x, float y, float width, float height) : x(x), y(y), width(width), height(height)
{
    style.x = x;
    style.y = y;
    style.width = width;
    style.height = height;
};

vector<Element *> Element::getSortedChildren()
{
    vector<Element *> sorted;

    for (auto &child : children)
        sorted.push_back(child.get());

    stable_sort(
        sorted.begin(),
        sorted.end(),
        [](const Element *a, const Element *b)
        {
            return a->style.zIndex < b->style.zIndex;
        });

    return sorted;
}

void Element::render(float windowWidth, float windowHeight)
{

    // styleComputer->computePosition(this, windowWidth, windowHeight);
    // styleComputer->computeSize(this, windowWidth, windowHeight);
    painter->paint(this);

    if (children.size() > 0)
    {
        vector<Element *> sorted = getSortedChildren();

        for (auto &child : sorted)
        {
            child->render(windowWidth, windowHeight);
        }
    }
}

void Element::updateLayout(float newWindowWidth, float newWindowHeight)
{

    styleComputer->computePosition(this, newWindowWidth, newWindowHeight);
    styleComputer->computeSize(this, newWindowWidth, newWindowHeight);
    styleComputer->computeBorderWidth(this);

    for (auto &child : children)
    {
        child->updateLayout(newWindowWidth, newWindowHeight);
    }
}

void Element::addStyle(StyleDef &styleDef)
{
    if (styleApplier)
        styleApplier->apply(this, styleDef);
}

void Element::addChild(unique_ptr<Element> child)
{
    child->parent = this;
    children.push_back(std::move(child));
}

Element *Element::getChild(int index)
{
    if (index < 0 || index >= children.size())
        return nullptr;

    return children[index].get();
}

void Element::click(int mouseX, int mouseY)
{
    if (onClick)
        onClick();
}

void Element::handleResize(float newWindowWidth, float newWindowHeight)
{

    updateLayout(newWindowWidth, newWindowHeight);

    if (children.size())
        for (auto &child : children)
        {
            child->handleResize(newWindowWidth, newWindowHeight);
        }
}

bool Element::isInside(int mouseX, int mouseY)
{
    return (computedStyle.x <= mouseX && computedStyle.x + computedStyle.width >= mouseX) && (computedStyle.y <= mouseY && computedStyle.y + computedStyle.height >= mouseY);
}

bool Element::isInsideElement(int mouseX, int mouseY, Element *element)
{
    return (element->computedStyle.x <= mouseX && element->computedStyle.x + element->computedStyle.width >= mouseX) && (element->computedStyle.y <= mouseY && element->computedStyle.y + element->computedStyle.height >= mouseY);
}