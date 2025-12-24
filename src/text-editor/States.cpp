#include <iostream>
#include "TextEditor.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"
#include "../element/FontManager.hpp"
#include "../Constants.h"
#include <memory>

using namespace std;
using namespace Constants;

// unique_ptr<FontManager> fontManager = make_unique<FontManager>();
// Window window(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Runs only once
void TextEditor::Init()
{

    fontManager = std::make_unique<FontManager>();
    window = std::make_unique<Window>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    window->style.backgroundColor = {31, 31, 31, 255};

    window->fontManager = fontManager.get();

    window->className = "Window_";

    auto element = window->createWidget(0, 100, WINDOW_WIDTH, 50);
    element->style.backgroundColor = {24, 24, 24, 255};
    element->className = "brown";
    element->text = "I am saying helloooo";
    // element->setFontSize(15);

    auto element2 = window->createWidget(150, 190, 200, 200);
    element2->style.backgroundColor = {21, 166, 66, 255};
    element2->className = "green";

    auto element3 = window->createWidget(280, 190, 200, 200);
    element3->style.backgroundColor = {255, 28, 33, 255};
    element3->style.color = {0, 255, 0, 255};
    element3->style.zIndex = 2;
    element3->text = "I am red";
    element3->style.fontSize = 15;

    auto elementChild = window->createWidget(150, 10, 300, 50);
    elementChild->style.backgroundColor = {0, 0, 0, 255};
    elementChild->className = "black";

    // auto elementChildChild = window->createWidget(150, 250, 200, 200);
    // elementChildChild->style.backgroundColor = {23, 244, 255, 255};
    // elementChildChild->className = "child_Child";
    // elementChildChild->style.zIndex = 1;

    // Use transform to Widget function in the future
    // auto elementChildWidget = dynamic_cast<Widget *>(elementChildChild.get());
    // elementChildWidget->isPropagateClick = false;

    // element->style.zIndex = 1;

    {
        // elementChild->addChild(std::move(elementChildChild));
        element->addChild(std::move(elementChild));

        window->addManyChild(std::move(element)
                             // ,std::move(element2),
                             // std::move(element3)
        );
    }
}

void TextEditor::ListenToEvent(SDL_Event *event)
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
        float newWidth = event->window.data1;
        float newHeight = event->window.data2;
        // SDL_Log("New size: %fx%f", newWidth, newHeight);
        window->handleResize(newWidth, newHeight);
    }
}

// Runs every frame
void TextEditor::Run(SDL_Renderer *renderer)
{

    // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);

    // Elements
    window->render(renderer);

    // Element *child3 = window->getChild(2);
    // child3->x = 300;
    // child3->style.backgroundColor = {255, 28, 33, 255};
    // child3->style.zIndex = 2;
    // child3->className = "red";

    Element *child = window->getChild(0);
    child->onClick = [=]()
    {
        cout << child->className + " widget function was executed" << endl;
    };

    window->onClick = [=]()
    {
        cout << window->className + " function was executed" << endl;
    };
    //  Element *child = window.getChild(0);

    // element.onClick = [&]()
    // {
    //     cout << "Element clicked\n";
    //     // put any logic you need here
    // };

    SDL_RenderPresent(renderer);
}

void TextEditor::End()
{
    fontManager->clearFonts();
}