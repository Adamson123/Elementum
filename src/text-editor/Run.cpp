#include <iostream>
#include "../elementum/Elementum.hpp"
#include "../elementum/element/Element.hpp"
#include "../elementum/element/window/Window.hpp"
#include "../elementum/element/widget/Widget.hpp"

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
        std::cout << child->className + " widget function was executed" << std::endl;
    };

    window->onClick = [=]()
    {
        std::cout << window->className + " function was executed" << std::endl;
    };

    SDL_RenderPresent(renderer);
}
