#pragma once
#include <SDL.h>
#include "style/Style.hpp"
#include "style/ComputedStyle.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <utility>
#include <SDL_ttf.h>

enum class UIType
{
    ELEMENT,
    WINDOW,
    WIDGET,
};

class Window;
class FontManager;
class StyleApplier;
class Painter;
class StyleComputer;

class Element
{
public:
    Element(float x, float y, float width, float height);
    virtual ~Element() = default;

    // Flags
    bool layoutDirty = true;
    // TODO: Still useless
    // bool paintDirty = true;
    // bool textDirty = true;

    Element *parent = nullptr;
    Element *prevSibling = nullptr;
    // TTF_Font *font = nullptr;
    // FontManager *fontManager = nullptr;

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
    void setFontFamily(const std::string &family);
    void setStartX(StartPosition startX);
    void setStartY(StartPosition startY);

    // Computed size and position getters
    float getX() const { return computedStyle.x; }
    float getY() const { return computedStyle.y; }
    float getWidth() const { return computedStyle.width; }
    float getHeight() const { return computedStyle.height; }

    UIType getType() const { return type; }

private:
    UIType type = UIType::ELEMENT;
};
