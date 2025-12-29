#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Element;
class FontManager;

/** Handles the rendering of elements using SDL */
class Painter
{
public:
    //~Painter();
    /** SDL renderer used for drawing elements */
    SDL_Renderer *renderer;
    /** Manages fonts for rendering text */
    FontManager *fontManager;

    /** Renders the given element */
    void paint(Element *element);

private:
    /** Renders the background of the given element */
    void paintBackground(Element *element);
    /** Renders the border of the given element */
    void paintBorder(Element *element);
    /** Renders the text of the given element */
    void paintText(Element *element);
};
