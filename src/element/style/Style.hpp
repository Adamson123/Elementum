#pragma once
#include <string>
#include <unordered_map>
#include <SDL.h>

using namespace std;

using StyleDef = unordered_map<string, string>;

enum class Unit
{
    PX,
    PERCENT
};

struct Units
{
    Unit width = Unit::PX;
    Unit height = Unit::PX;
    Unit x = Unit::PX;
    Unit y = Unit::PX;
    Unit borderWidth = Unit::PX;
};

struct Style
{
private:
    SDL_Color backgroundColor = {0, 0, 0, 0},
              color = {255, 255, 255, 255},
              borderColor = {0, 255, 0, 0};

    string fontFamily = "fonts/arial.ttf";

    int zIndex = 0;

    float
        width,
        height,
        x,
        y,
        borderWidth,
        fontSize = 25;

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

    string getFontFamily() const { return fontFamily; }
    int getZIndex() const { return zIndex; }

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getBorderWidth() const { return borderWidth; }
    float getFontSize() const { return fontSize; }
};
