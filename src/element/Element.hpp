#pragma once
#include <SDL.h>
#include "style/Style.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <utility>

class Element
{
public:
    Element(float x, float y, float width, float height);
    // virtual ~Element() = default;

    Element *parent = nullptr;

    float x = 0;
    float y = 0;

    float width = 0;
    float height = 0;

    Style style;
    string id;
    string className;
    string text;

    vector<unique_ptr<Element>> children;

    void render(SDL_Renderer *renderer);

    void addChild(unique_ptr<Element> child);
    // void addManyChild(initializer_list<unique_ptr<Element>> manyChild);
    template <typename... Args>
    void addManyChild(Args &&...args)
    {
        (addChild(std::forward<Args>(args)), ...);
    }
    Element *getChild(int index);
    Element *getChildByClassName(string className);
    Element *getChildByID(string id);
    vector<Element *> getSortedChildren();

    void listenToWindowClick(int mouseX, int mouseY);
    void click(int mouseX, int mouseY);
    function<void()> onClick;

    bool isInside(int mouseX, int mouseY);
    bool isInsideElement(int mouseX, int mouseY, Element *element);
    virtual void assignToClickedElement(int mouseX, int mouseY);
};
