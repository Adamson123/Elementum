#include <iostream>
#include "../elementum/Elementum.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/style-applier/StyleApplier.hpp"
#include "../element/painter/Painter.hpp"
#include "../element/style/style-computer/StyleComputer.hpp"
#include "./Constants.h"
#include <memory>

using namespace std;
using namespace Constants;

// Runs only once
void Elementum::Init()
{

    StyleDef tmp = {
        {"backgroundColor", "31,31,31,255"}};
    window->addStyle(tmp);

    window->className = "Window_";

    // PX by default
    auto element = window->createWidget(20, 0, 100, 50);
    element->className = "brown";
    element->text = "I am saying helloooo";

    auto elementChild = window->createWidget(40, 0, 50, 100);
    elementChild->className = "black";

    auto elementChildChild = window->createWidget(50, 50, 20, 20);
    // auto Child = window->createWidget();
    elementChildChild->className = "child_Child";

    StyleDef InputType = {
        {"color", "0,255,125,255"},
        {"backgroundColor", "0,25,125,255"},
        {"x", "0px"},
        {"width", "70%"},
        {"height", "80%"},
        //  {"borderWidth", "50%"}

    };

    StyleDef InputType2 = InputType;
    InputType2["backgroundColor"] = "120,0,25,255";
    InputType2["y"] = "10%";
    InputType2["x"] = "50px";
    InputType2["width"] = "100%";

    element->addStyle(InputType);
    elementChild->addStyle(InputType2);
    InputType["backgroundColor"] = "120,0,125,255";
    elementChildChild->addStyle(InputType);

    {
        elementChild->addChild(std::move(elementChildChild));
        element->addChild(std::move(elementChild));

        window->addManyChild(std::move(element)
                             // ,std::move(element2),
                             // std::move(element3)
        );
    }
    // window->updateLayout(windowWidth, windowHeight);
}

void Elementum::ListenToEvent(SDL_Event *event)
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

void Elementum::End()
{
    fontManager->clearFonts();
}