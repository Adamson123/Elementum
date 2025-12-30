#include "../elementum/Elementum.hpp"
#include "../elementum/element/Element.hpp"
#include "../elementum/element/window/Window.hpp"
#include "../elementum/element/widget/Widget.hpp"

// Runs only once
void Elementum::Init()
{

    window->className = "Window";
    window->setBackgroundColor({31, 31, 31, 255});

    StyleDef Style1 = {
        {"color", "0,255,125,255"},
        {"backgroundColor", "20,20,20,255"},
        {"width", "70%"},
        {"height", "80%"},
        // {"x", "10%"},
    };

    auto element = window->createWidget();
    element->className = "element";
    // element->text = "Element says hello user";
    element->addStyle(Style1);

    Style1["backgroundColor"] = "31,31,31,255";
    Style1["color"] = "222,55,0,255";
    Style1["width"] = "150px";
    Style1["height"] = "150px";
    Style1["x"] = "20px";
    Style1["y"] = "10px";

    auto element2 = window->createWidget();
    element2->className = "element2";
    element2->text = element2->className;
    element2->addStyle(Style1);

    auto element3 = window->createWidget();
    element3->className = "element3";
    element3->text = element3->className;
    element3->addStyle(Style1);
    element3->setDisplay(Display::NONE);

    //    Style1["y"] = "20px";
    auto element4 = window->createWidget();
    element4->className = "element4";
    element4->text = element4->className;
    element4->addStyle(Style1);
    element4->setDisplay(Display::BLOCK);
    // element4->setWidth(200.f);
    //  element4->setStartX(StartPosition::PARENT);
    //  element4->setStartY(StartPosition::PREV_SIBLING);

    {
        element->addManyChild(std::move(element2), std::move(element3), std::move(element4));
        window->addManyChild(std::move(element));
    }
}