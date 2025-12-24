
#include <iostream>
#include "Element.hpp"
#include <memory>

using namespace std;

Element::Element(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};

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

void Element::render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, style.color.r, style.color.g, style.color.b, style.color.a);
    SDL_RenderFillRectF(renderer, &rect);

    if (children.size() > 0)
    {
        vector<Element *> sorted = getSortedChildren();

        for (auto &child : sorted)
        {
            child->render(renderer);
        }
    }
}

void Element::addChild(unique_ptr<Element> child)
{
    child->parent = this;
    children.push_back(std::move(child));
}

// void Element::addManyChild(initializer_list<unique_ptr<Element>> manyChild)
// {
//     if (manyChild.size())
//         for (auto &child : manyChild)
//         {
//             child->parent = this;
//             children.push_back(std::move(child));
//         }
// }

// template <typename... Args>
// void Element::addManyChild(Args &&...args)
// {
//     (addChild(std::forward<Args>(args)), ...); // fold expression
// }

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

bool Element::isInside(int mouseX, int mouseY)
{
    return (x <= mouseX && x + width >= mouseX) && (y <= mouseY && y + height >= mouseY);
}

bool Element::isInsideElement(int mouseX, int mouseY, Element *element)
{
    return (element->x <= mouseX && element->x + element->width >= mouseX) && (element->y <= mouseY && element->y + element->height >= mouseY);
}