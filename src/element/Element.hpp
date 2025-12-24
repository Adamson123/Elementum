#pragma once
#include <SDL.h>
#include "style/Style.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <utility>
#include <SDL_ttf.h>
#include "./FontManager.hpp"

class Window;
class Rectangle;

class Element
{
public:
    Element(float x, float y, float width, float height);
    virtual ~Element() = default;

    float initialX, initialY, initialWidth, initialHeight;
    float x = 0, y = 0, width = 0, height = 0;
    // float relativeX, relativeY;

    Element *parent = nullptr;
    TTF_Font *font;
    FontManager *fontManager;

    Style style;
    string id, className, text;

    vector<unique_ptr<Element>> children;
    vector<Element *> getSortedChildren();

    void render(SDL_Renderer *renderer);
    void renderText(SDL_Renderer *renderer);
    // void setFontSize(int size);

    void addChild(unique_ptr<Element> child);
    template <typename... Args>
    void addManyChild(Args &&...args)
    {
        (addChild(std::forward<Args>(args)), ...);
    }
    Element *getChild(int index),
        *getChildByClassName(string className),
        *getChildByID(string id);

    // click event
    void click(int mouseX, int mouseY);
    function<void()> onClick = nullptr;

    // resize event
    void handleResize(float newWidth, float newHeight);

    bool isInside(int mouseX, int mouseY);
    bool isInsideElement(int mouseX, int mouseY, Element *element);
};
