#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "../../Element.hpp"
#include "../Style.hpp"

using StyleHandler = std::function<void(Element *element, const std::string &)>;

class Element;

/** Applies style properties to elements based on defined style rules */
class StyleApplier
{
private:
    /** Maps style property names to their corresponding handler functions */
    std::unordered_map<std::string, StyleHandler> handlers;

public:
    StyleApplier();
    /** Applies the given styles to the specified element */
    void apply(Element *element, StyleDef &styles);
    // unordered_map<string, StyleHandler> handlers;
};