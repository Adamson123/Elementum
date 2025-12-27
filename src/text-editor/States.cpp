#include <iostream>
#include "TextEditor.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/StyleApplier.hpp"
#include "../element/painter/Painter.hpp"
#include "../element/style/style-computer/StyleComputer.hpp"
#include "../Constants.h"
#include <memory>

using namespace std;
using namespace Constants;

// Runs only once
void TextEditor::Init(SDL_Renderer *renderer)
{

    window = make_unique<Window>(0, 0, windowWidth, windowHeight);
    fontManager = make_unique<FontManager>();
    styleApplier = make_unique<StyleApplier>();
    painter = make_unique<Painter>();
    styleComputer = make_unique<StyleComputer>();

    painter->renderer = renderer;

    window->fontManager = fontManager.get();
    window->styleApplier = styleApplier.get();
    window->painter = painter.get();

    window->style.backgroundColor = {31, 31, 31, 255};

    // StyleDef tmp = {
    //     {"width", "100%"},
    //     {"height", "100%"}};
    // window->addStyle(tmp);

    window->className = "Window_";

    // PX by default
    auto element = window->createWidget(20, 0, 100, 50);
    element->style.backgroundColor = {24, 24, 24, 255};
    element->className = "brown";
    element->text = "I am saying helloooo";

    auto elementChild = window->createWidget(40, 0, 50, 100);
    elementChild->className = "black";

    auto elementChildChild = window->createWidget(50, 50, 20, 20);
    elementChildChild->style.backgroundColor = {23, 244, 255, 255};
    elementChildChild->className = "child_Child";

    StyleDef InputType = {
        {"color", "0,255,125,255"},
        {"backgroundColor", "0,25,125,255"},
        {"x", "0px"},
        {"width", "70%"},
        {"height", "80%"},
        {"borderWidth", "20%"}

    };

    StyleDef InputType2 = InputType;
    InputType2["backgroundColor"] = "120,0,25,255";
    InputType2["y"] = "10%";
    InputType2["x"] = "50px";
    InputType2["width"] = "100%";

    element->addStyle(InputType);
    elementChild->addStyle(InputType2);
    elementChildChild->addStyle(InputType);

    {
        elementChild->addChild(std::move(elementChildChild));
        element->addChild(std::move(elementChild));

        window->addManyChild(std::move(element)
                             // ,std::move(element2),
                             // std::move(element3)
        );
    }
    window->updateLayout(windowWidth, windowHeight);
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

        windowWidth = newWidth;
        windowHeight = newHeight;

        window->onWindowResize(newWidth, newHeight);
        window->handleResize(newWidth, newHeight);
    }
}

// Runs every frame
void TextEditor::Run(SDL_Renderer *renderer)
{

    // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);

    window->render(windowWidth, windowHeight);
    Element *child = window->getChild(0);

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

void TextEditor::End()
{
    fontManager->clearFonts();
}