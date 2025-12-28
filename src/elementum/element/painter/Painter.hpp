#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Element;
class FontManager;

class Painter
{
public:
    //~Painter();
    SDL_Renderer *renderer;
    FontManager *fontManager;

    void paint(Element *element);

private:
    void paintBackground(Element *element);
    void paintBorder(Element *element);
    void paintText(Element *element);
};
