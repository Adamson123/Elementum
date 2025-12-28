#include "../elementum/Elementum.hpp"
#include "../element/window/Window.hpp"

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
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED)
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
