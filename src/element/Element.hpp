#pragma once
#include <SDL.h>
#include "style/Style.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <utility>

class Window;
class Rectangle;

class Element
{
public:
    Element(float x, float y, float width, float height);
    virtual ~Element() = default;

    Element *parent = nullptr;

    float x = 0, y = 0, width = 0, height = 0;

    Style style;
    string id, className, text;

    vector<unique_ptr<Element>> children;
    vector<Element *> getSortedChildren();

    void render(SDL_Renderer *renderer);

    void addChild(unique_ptr<Element> child);
    template <typename... Args>
    void addManyChild(Args &&...args)
    {
        (addChild(std::forward<Args>(args)), ...);
    }
    Element *getChild(int index),
        *getChildByClassName(string className),
        *getChildByID(string id);

    void click(int mouseX, int mouseY);
    function<void()> onClick = nullptr;

    bool isInside(int mouseX, int mouseY);
    bool isInsideElement(int mouseX, int mouseY, Element *element);
};
