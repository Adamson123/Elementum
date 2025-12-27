#pragma once
#include <string>
#include <unordered_map>

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

    SDL_Color backgroundColor = {0, 0, 0, 0},
              color = {255, 255, 255, 255},
              borderColor = {0, 255, 0, 0};

    string fontFamily = "fonts/arial.ttf";

    int zIndex = 0;

    float width;
    float height;
    float x;
    float y;
    float borderWidth;

    int fontSize = 25;

    Units unit;
};
