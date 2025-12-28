#include "../elementum/Elementum.hpp"
#include "../element/Element.hpp"
#include "../element/window/Window.hpp"
#include "../element/widget/Widget.hpp"

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
    element->text = "I am saying helloooo\n ggggggggg";

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