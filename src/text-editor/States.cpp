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

    window = make_unique<Window>(0, 0, 100, 100);
    fontManager = make_unique<FontManager>();
    styleApplier = make_unique<StyleApplier>();

    window->fontManager = fontManager.get();
    window->styleApplier = styleApplier.get();

    window->style.backgroundColor = {31, 31, 31, 255};
    window->className = "Window_";

    auto element = window->createWidget(0, 0, 100, 50);
    element->style.backgroundColor = {24, 24, 24, 255};
    element->className = "brown";
    element->text = "I am saying helloooo";
    // element->setFontSize(15);

    auto elementChild = window->createWidget(40, 0, 50, 100);
    // elementChild->style.backgroundColor = {0, 0, 0, 255};
    elementChild->className = "black";

    auto elementChildChild = window->createWidget(50, 50, 20, 20);
    elementChildChild->style.backgroundColor = {23, 244, 255, 255};
    elementChildChild->className = "child_Child";

    StyleDef InputType = {
        {"color", "0,255,125,255"}, {"backgroundColor", "255,23,110,0"}};

    element->addStyle(InputType);
    elementChildChild->addStyle(InputType);

    // elementChildChild->style.zIndex = 1;

    // Use transform to Widget function in the future
    // auto elementChildWidget = dynamic_cast<Widget *>(elementChildChild.get());
    // elementChildWidget->isPropagateClick = false;

    // element->style.zIndex = 1;

    {
        elementChild->addChild(std::move(elementChildChild));
        element->addChild(std::move(elementChild));

        window->addManyChild(std::move(element)
                             // ,std::move(element2),
                             // std::move(element3)
        );
    }
    window->updateLayout(WINDOW_WIDTH, WINDOW_HEIGHT);
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