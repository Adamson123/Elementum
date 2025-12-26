#pragma once
#include <string>
#include <unordered_map>

using namespace std;

using StyleDef = const unordered_map<string, string>;

class Style
{
public:
    SDL_Color backgroundColor = {0, 0, 0, 0},
              color = {255, 255, 255, 255},
              borderColor = {0, 0, 0, 0};

    string fontFamily = "fonts/arial.ttf";
    int fontSize = 25;
    int zIndex = 0;
};
