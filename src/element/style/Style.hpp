#pragma once
#include <string>
#include <unordered_map>

using namespace std;

using StyleDef = const unordered_map<string, string>;

class Style
{
public:
    SDL_Color backgroundColor = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    string fontFamily = "fonts/arial.ttf";
    int fontSize = 25;
    int zIndex = 0;
};
