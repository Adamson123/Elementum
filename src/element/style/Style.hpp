#pragma once
#include <string>

using namespace std;

struct BackgroundColor
{
    int r;
    int g;
    int b;
    int a;

    BackgroundColor(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};
};

class Style
{
public:
    BackgroundColor backgroundColor = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    string fontFamily = "fonts/arial.ttf";
    int fontSize = 25;
    int zIndex = 0;
};