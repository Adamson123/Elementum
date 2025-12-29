#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "../../Element.hpp"
#include "../Style.hpp"

using StyleHandler = std::function<void(Element *element, const std::string &)>;

class Element;

class StyleApplier
{
private:
    std::unordered_map<std::string, StyleHandler> handlers;

public:
    StyleApplier();
    void apply(Element *element, StyleDef &styles);
    // unordered_map<string, StyleHandler> handlers;
};