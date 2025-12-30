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

/**The Element class represents a UI component with properties for layout, style, parent-child relationships,
 *  and event handling, supporting rendering, style management, and interaction within a graphical user interface system.
 *  It provides methods for manipulating its appearance, hierarchy, and responding to user actions such as clicks and window resizing.

 */
class Element
{
public:
    Element(float x, float y, float width, float height);
    virtual ~Element() = default;

    // Flags
    bool layoutDirty = true;
    // TODO: Useless for now
    // bool paintDirty = true;
    // bool textDirty = true;

    // Pointer to element's parent
    Element *parent = nullptr;
    // Pointer to element's prevSibling
    Element *prevSibling = nullptr;
    // TODO: Pointer to element's nextSibling
    Element *nextSibling = nullptr;

    // Pointer to element's styleApplier for modifying Element's style from unordered map
    StyleApplier *styleApplier = nullptr;
    // Pointer to element's painter for rendering the Element
    Painter *painter = nullptr;
    // Pointer to element's styleComputer for computing Element's style into computed style
    StyleComputer *styleComputer = nullptr;

    // Element's style
    Style style;
    // Computed element's style
    ComputedStyle computedStyle;
    /** Adds the specified StyleDef object to the Element, allowing the element to incorporate or update its styling properties based on the provided style definition. */
    void addStyle(StyleDef &styleDef);

    // For identifying element during elements query
    std::string id, className;
    // Element's text content
    std::string text;

    /** Calls computing and painting functions */
    void render(float windowWidth, float windowHeight);

    // void updateLayout(float newWindowWidth, float newWindowHeight);
    //  void setFontSize(int size);

    // Elements children
    std::vector<std::unique_ptr<Element>> children;
    /** Returns elements sorted by zIndex */
    std::vector<Element *> getSortedChildren();
    /** Adds a child element to this element's children */
    void addChild(std::unique_ptr<Element> child);
    /** Adds multiple child elements to this element's children */
    template <typename... Args>
    void addManyChild(Args &&...args)
    {
        (addChild(std::forward<Args>(args)), ...);
    }
    // TODO:
    Element *getChild(int index),
        *getChildByClassName(std::string className),
        *getChildByID(std::string id);

    // TODO:
    //  click event
    void click(int mouseX, int mouseY);
    std::function<void()> onClick = nullptr;

    // TODO:
    //  resize event
    void handleResize(float newWindowWidth, float newWindowHeight);

    /** Checks if the given coordinates are inside the element */
    bool isInside(int mouseX, int mouseY);
    /** Checks if the given coordinates are inside the specified element */
    bool isInsideElement(int mouseX, int mouseY, Element *element);

    // Style setters for element's style
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
    // void setStartX(StartPosition startX);
    // void setStartY(StartPosition startY);
    void setDisplay(Display display);

    // Computed size and position getters
    float getX() const { return computedStyle.x; }
    float getY() const { return computedStyle.y; }
    float getWidth() const { return computedStyle.width; }
    float getHeight() const { return computedStyle.height; }

    /** Returns the UIType value representing the type of the Element  */
    UIType getType() const { return type; }

private:
    UIType type = UIType::ELEMENT;
};
