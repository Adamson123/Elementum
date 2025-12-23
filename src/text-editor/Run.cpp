#include <iostream>
#include "TextEditor.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../Constants.h"
#include <memory>
// #include <format>

using namespace std;
using namespace Constants;

Window window(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Runs only once
void TextEditor::Init()
{

    // window.className = "rt5";

    // auto element = window.createRectangle(0, 0, 200, WINDOW_HEIGHT);
    // element->style.color = {122, 66, 66, 255};

    // auto element2 = window.createRectangle(150, 190, 200, 200);
    // element2->style.color = {21, 166, 66, 255};

    // auto elementChild = window.createRectangle(150, 190, 300, 50);
    // elementChild->style.color = {0, 0, 0, 255};

    // element->style.zIndex = 1;

    // element->addChild(std::move(elementChild));

    // {
    //     window.addManyChild(std::move(element),
    //                         std::move(element2),
    //                         make_unique<Element>(280, 190, 200, 200));
    // }

    auto *element = window.createRectangle(0, 0, 200, WINDOW_HEIGHT);
    element->style.color = {122, 66, 66, 255};
    element->style.zIndex = 1;

    auto *element2 = window.createRectangle(150, 190, 200, 200);
    element2->style.color = {21, 166, 66, 255};

    // auto *elementChild = window.createRectangle(150, 190, 300, 50);
    // elementChild->style.color = {0, 0, 0, 255};

    // If you want elementChild to become a child of `element`, you must TRANSFER ownership.
    // With current API, elementChild is owned by `window`. So create the child under element instead:

    // remove the above elementChild creation and do:
    // auto* elementChild = element->emplaceChild<Rectangle>(150, 190, 300, 50);

    // Example (do this instead of window.createRectangle for the child):
    auto *elementChild2 = element->emplaceChild<Rectangle>(150, 190, 300, 50);
    elementChild2->window = &window;
    elementChild2->style.color = {0, 0, 0, 255};

    // If you want a plain Element:
    window.emplaceChild<Element>(280, 190, 200, 200);
}

void TextEditor::ListenToEvent(SDL_Event *event)
{
    // if (event->type == SDL_MOUSEBUTTONDOWN)
    // {
    //     float x = event->button.x;
    //     float y = event->button.y;

    //     element.listenToWindowClick(x, y);
    //     // cout << "was clicked" << endl;
    // }
}

// Runs every frame
void TextEditor::Run(SDL_Renderer *renderer)
{

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);

    // Elements
    window.style.color = {70, 66, 255, 255};
    window.render(renderer);

    Element *child3 = window.getChild(2);
    child3->x = 300;
    child3->style.color = {255, 28, 33, 255};
    child3->style.zIndex = 4;

    Element *child = window.getChild(0);

    // element.onClick = [&]()
    // {
    //     cout << "Element clicked\n";
    //     // put any logic you need here
    // };

    SDL_RenderPresent(renderer);
}