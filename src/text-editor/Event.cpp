#include "../elementum/Elementum.hpp"
#include "../elementum/element/window/Window.hpp"

void Elementum::Event(SDL_Event *event)
{
    // Click event
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        float x = event->button.x;
        float y = event->button.y;

        window->handleClickWithIn(x, y);
    }

    // Resize event
    // event->type == SDL_WINDOWEVENT &&
    if (event->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        float currentWindowWidth = event->window.data1;
        float currentWindowHeight = event->window.data2;

        windowWidth = currentWindowWidth;
        windowHeight = currentWindowHeight;

        // TODO
        window->setWidth(currentWindowWidth);
        window->setHeight(currentWindowHeight);
    }
}
