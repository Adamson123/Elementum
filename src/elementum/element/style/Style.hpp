#pragma once
#include <string>
#include <unordered_map>
#include <SDL.h>

/** Represents a collection of style properties as key-value pairs */
using StyleDef = std::unordered_map<std::string, std::string>;

/** Represents measurement units for style properties */
enum class Unit
{
    PX,
    PERCENT
};

/** Represents the starting position for layout calculations */
enum class StartPosition
{
    PARENT,
    PREV_SIBLING
};

/** Represents measurement units for different style properties */
struct Units
{
    Unit width = Unit::PX;
    Unit height = Unit::PX;
    Unit x = Unit::PX;
    Unit y = Unit::PX;
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

    float
        x,
        y,
        width,
        height,
        borderWidth,
        fontSize = 25;

    StartPosition startX = StartPosition::PREV_SIBLING, startY = StartPosition::PARENT;

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

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getBorderWidth() const { return borderWidth; }
    float getFontSize() const { return fontSize; }

    StartPosition getStartX() const { return startX; }
    StartPosition getStartY() const { return startY; }
};
