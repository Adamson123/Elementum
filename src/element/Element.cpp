
#include <iostream>
#include "Element.hpp"
#include <memory>
#include "../Constants.h"
#include "./FontManager.hpp"
#include "./style/StyleApplier.hpp"

using namespace std;
using namespace Constants;

Element::Element(float x, float y, float width, float height) : x(x), y(y), width(width), height(height)
{
    initialX = x;
    initialY = y;
    initialWidth = width;
    initialHeight = height;
    relativeX = x;
    relativeY = y;
    relativeWidth = width;
    relativeHeight = height;
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

void Element::render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {relativeX, relativeY, relativeWidth, relativeHeight};
    SDL_SetRenderDrawColor(renderer, style.backgroundColor.r, style.backgroundColor.g, style.backgroundColor.b, style.backgroundColor.a);
    SDL_RenderFillRectF(renderer, &rect);

    renderText(renderer);

    if (children.size() > 0)
    {
        vector<Element *> sorted = getSortedChildren();

        for (auto &child : sorted)
        {
            child->render(renderer);
        }
    }
}

void Element::renderText(SDL_Renderer *renderer)
{
    if (text.empty())
        return;

    font = fontManager->get(style.fontFamily, style.fontSize);

    // 1️⃣ Render text to surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), style.color);
    if (!surface)
    {
        std::cout << "Surface error: " << TTF_GetError() << std::endl;
        return;
    }

    // 2️⃣ Convert surface to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        std::cout << "Texture error: " << SDL_GetError() << std::endl;
        return;
    }

    // 3️⃣ Query texture size
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);

    // 4️⃣ Copy texture to renderer
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    // 5️⃣ Cleanup texture
    SDL_DestroyTexture(texture);
}

void Element::updateLayout(float newWindowWidth, float newWindowHeight)
{
    if (parent)
    {
        relativeX = parent->relativeX + (x / 100) * parent->relativeWidth;
        relativeY = parent->relativeY + (y / 100) * parent->relativeHeight;

        relativeWidth = (width / 100) * parent->relativeWidth;
        relativeHeight = (height / 100) * parent->relativeHeight;
    }
    else
    {
        relativeX = y;
        relativeY = x;

        relativeWidth = (width / 100) * newWindowWidth;
        relativeHeight = (height / 100) * newWindowHeight;
    }

    for (auto &child : children)
    {
        child->updateLayout(newWindowWidth, newWindowHeight);
    }
    SDL_Log("W: %f x H: %f, %s, my H in 100: %f", relativeWidth, relativeHeight, className.c_str(), height);
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

    // float parentInitialWidth = parent ? parent->initialWidth : WINDOW_WIDTH;
    // float parentInitialHeight = parent ? parent->initialHeight : WINDOW_HEIGHT;

    // float percentageWidth = initialWidth / parentInitialWidth;
    // float percentageHeight = initialHeight / parentInitialHeight;

    // float parentWidth =

    // width = percentageWidth *

    // SDL_Log("%fx%f", percentageWidth, percentageHeight);

    updateLayout(newWindowWidth, newWindowHeight);

    // if (children.size())
    //     for (auto &child : children)
    //     {
    //         child->handleResize(newWidth, newHeight);
    //     }
}

bool Element::isInside(int mouseX, int mouseY)
{
    return (relativeX <= mouseX && relativeX + relativeWidth >= mouseX) && (relativeY <= mouseY && relativeY + relativeHeight >= mouseY);
}

bool Element::isInsideElement(int mouseX, int mouseY, Element *element)
{
    return (element->x <= mouseX && element->x + element->width >= mouseX) && (element->y <= mouseY && element->y + element->height >= mouseY);
}