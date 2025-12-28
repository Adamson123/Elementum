#pragma once
#include <SDL.h>
#include "style/Style.hpp"
#include "style/ComputedStyle.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <utility>
#include <SDL_ttf.h>

class Window;
class Rectangle;
class FontManager;
class StyleApplier;
class Painter;
class StyleComputer;

class Element
{
public:
    Element(float x, float y, float width, float height);
    virtual ~Element() = default;

    float x = 0, y = 0, width = 0, height = 0;

    // Flags
    bool styleDirty = true;
    bool layoutDirty = true;
    bool paintDirty = true;

    Element *parent = nullptr;
    TTF_Font *font = nullptr;

    FontManager *fontManager = nullptr;
    StyleApplier *styleApplier = nullptr;
    Painter *painter = nullptr;
    StyleComputer *styleComputer = nullptr;

    Style style;
    ComputedStyle computedStyle;

    string id, className, text;

    vector<unique_ptr<Element>> children;
    vector<Element *> getSortedChildren();

    void render(float windowWidth, float windowHeight);

    void addStyle(StyleDef &styleDef);

    // void updateLayout(float newWindowWidth, float newWindowHeight);
    //  void setFontSize(int size);

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
    void handleResize(float newWindowWidth, float newWindowHeight);

    bool isInside(int mouseX, int mouseY);
    bool isInsideElement(int mouseX, int mouseY, Element *element);

    // Style Setters
    void setWidth(float value, Unit unit = Unit::PX);
    void setHeight(float value, Unit unit = Unit::PX);
    void setX(float value, Unit unit = Unit::PX);
    void setY(float value, Unit unit = Unit::PX);
    void setBackgroundColor(SDL_Color color);
    void setBorderColor(SDL_Color color);
    void setColor(SDL_Color color);
    void setBorderWidth(float value, Unit unit = Unit::PX);
    void setFontSize(int size);

private:
    string type = "element";
};
