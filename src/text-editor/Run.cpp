#include <iostream>
#include "TextEditor.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"
#include "../Constants.h"
#include <memory>

using namespace std;
using namespace Constants;

Window window(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Runs only once
void TextEditor::Init()
{

    window.className = "Window____";

    auto element = window.createWidget(0, 0, 200, WINDOW_HEIGHT);
    element->style.color = {122, 66, 66, 255};
    element->className = "brown";

    auto element2 = window.createWidget(150, 190, 200, 200);
    element2->style.color = {21, 166, 66, 255};
    element2->className = "green";

    auto element3 = window.createWidget(280, 190, 200, 200);

    auto elementChild = window.createWidget(150, 190, 300, 350);
    elementChild->style.color = {0, 0, 0, 255};
    elementChild->className = "black";

    auto elementChildChild = window.createWidget(150, 250, 200, 200);
    elementChildChild->style.color = {23, 244, 255, 255};
    elementChildChild->className = "Child child";
    elementChildChild->style.zIndex = 10;

    // Use transform to Widget function in the future
    auto elementChildWidget = dynamic_cast<Widget *>(elementChildChild.get());
    elementChildWidget->isPropagateClick = false;

    element->style.zIndex = 3;

    {
        elementChild->addChild(std::move(elementChildChild));
        element->addChild(std::move(elementChild));

        window.addManyChild(std::move(element),
                            std::move(element2),
                            std::move(element3));
    }
}

void TextEditor::ListenToEvent(SDL_Event *event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        float x = event->button.x;
        float y = event->button.y;

        window.handleClickWithIn(x, y);
    }
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
    child3->style.zIndex = 2;
    child3->className = "red";

    Element *child = window.getChild(0);
    child->onClick = [=]()
    {
        cout << child->className + " widget function was executed" << endl;
    };

    window.onClick = [=]()
    {
        cout << window.className + " function was executed" << endl;
    };
    //  Element *child = window.getChild(0);

    // element.onClick = [&]()
    // {
    //     cout << "Element clicked\n";
    //     // put any logic you need here
    // };

    SDL_RenderPresent(renderer);
}