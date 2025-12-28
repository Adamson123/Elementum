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
    auto element = window->createWidget();
    element->className = "brown";
    element->text = "I am saying helloooo\n ggggggggg";

    auto elementChild = window->createWidget();
    elementChild->className = "black";

    auto elementChildChild = window->createWidget();
    elementChildChild->className = "child_Child";

    StyleDef InputType = {
        {"color", "0,255,125,255"},
        {"backgroundColor", "0,25,125,255"},
        {"x", "0px"},
        {"width", "70%"},
        {"height", "80%"},
        {"y", "10%"},
    };

    element->addStyle(InputType);

    StyleDef InputType2 = InputType;
    InputType2["backgroundColor"] = "120,0,25,255";
    InputType2["x"] = "50px";
    InputType2["width"] = "30%";

    elementChild->addStyle(InputType2);
    InputType["backgroundColor"] = "120,0,125,255";
    InputType["width"] = "20px";
    InputType["startX"] = "prevSibling";

    elementChildChild->addStyle(InputType);

    {
        element->addManyChild(std::move(elementChild), std::move(elementChildChild));
        window->addManyChild(std::move(element));
    }
}