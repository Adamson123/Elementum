#pragma once
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <optional>

/** Represents a collection of style properties as key-value pairs */
using StyleDef = std::unordered_map<std::string, std::string>;

/** Represents measurement units for style properties */
enum class Unit
{
    PX,
    PERCENT
};

/** Represents the starting position for layout calculations */
// enum class StartPosition
// {
//     PARENT,
//     PREV_SIBLING
// };

enum class Display
{
    INLINE_BLOCK,
    BLOCK,
    FLEX, // future
    NONE
};

/** Represents measurement units for different style properties */
struct Units
{
    Unit width = Unit::PX;
    Unit height = Unit::PX;
    // Unit x = Unit::PX;
    // Unit y = Unit::PX;
    Unit margin = Unit::PX;
    Unit marginLeft = Unit::PX;
    Unit marginRight = Unit::PX;
    Unit marginTop = Unit::PX;
    Unit marginBottom = Unit::PX;
    Unit borderWidth = Unit::PX;
};

/** Represents a collection of style properties and their values */
class Style
{
private:
    SDL_Color backgroundColor = {0, 0, 0, 0},
              color = {255, 255, 255, 255},
              borderColor = {0, 255, 0, 0};

    std::string
        fontFamily = "fonts/arial.ttf";

    int zIndex = 0;

    std::optional<float>
        margin,
        marginLeft,
        marginRight,
        marginTop,
        marginBottom,
        width,
        height,
        borderWidth = NULL;

    int fontSize = 25;

    // StartPosition startX = StartPosition::PREV_SIBLING, startY = StartPosition::PARENT;
    Display display = Display::INLINE_BLOCK;

    Units unit;

    friend class Element;
    friend class StyleApplier;
    friend class Painter;
    friend class StyleComputer;
    friend class Window;
    friend class Widget;

public:
    SDL_Color getColor() const { return color; }
    SDL_Color getBackgroundColor() const { return backgroundColor; }
    SDL_Color getBorderColor() const { return borderColor; }

    std::string getFontFamily() const { return fontFamily; }
    int getZIndex() const { return zIndex; }

    std::optional<float> getWidth() const { return width; }
    std::optional<float> getHeight() const { return height; }

    std::optional<float> getMargin() const { return margin; }
    std::optional<float> getMarginLeft() const { return marginLeft; }
    std::optional<float> getMarginRight() const { return marginRight; }
    std::optional<float> getMarginTop() const { return marginTop; }
    std::optional<float> getMarginBottom() const { return marginBottom; }

    std::optional<float> getBorderWidth() const { return borderWidth; }
    int getFontSize() const { return fontSize; }

    Display getDisplay() const { return display; }
    // StartPosition getStartX() const { return startX; }
    // StartPosition getStartY() const { return startY; }
};
