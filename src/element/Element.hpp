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
    virtual ~Element() = default;

    Element *parent = nullptr;

    float x, y, width, height;

    Style style;
    string id, className, text;

    void render(SDL_Renderer *renderer);

    void addChild(unique_ptr<Element> child);
    // void addManyChild(initializer_list<unique_ptr<Element>> manyChild);
    template <class T, class... Args>
    T *emplaceChild(Args &&...args)
    {
        static_assert(std::is_base_of_v<Element, T>, "T must derive from Element");
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        ptr->parent = this;
        T *raw = ptr.get();
        children.push_back(std::move(ptr));
        return raw;
    }
    Element *getChild(int index);
    // Element *getChildByClassName(string className);
    // Element *getChildByID(string id);
    vector<Element *> getSortedChildren();

    void listenToWindowClick(int mouseX, int mouseY);
    void click(int mouseX, int mouseY);
    function<void()> onClick;

    bool isInside(int mouseX, int mouseY);
    bool isInsideElement(int mouseX, int mouseY, Element *element);

protected:
    vector<unique_ptr<Element>> children;
};
