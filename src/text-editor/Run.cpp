#include <iostream>
#include "../elementum/Elementum.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"

// Runs every frame
void Elementum::Run()
{

    // To clear screen with window background color
    SDL_Color windowBgColor = window->style.getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, windowBgColor.r, windowBgColor.g, windowBgColor.b, windowBgColor.a);
    SDL_RenderClear(renderer);

    window->render(windowWidth, windowHeight);
    Element *child = window->getChild(0);
    child->setWidth(100, Unit::PERCENT);

    child->onClick = [=]()
    {
        cout << child->className + " widget function was executed" << endl;
    };

    window->onClick = [=]()
    {
        cout << window->className + " function was executed" << endl;
    };

    SDL_RenderPresent(renderer);
}
