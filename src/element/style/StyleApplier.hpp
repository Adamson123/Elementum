#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "../Element.hpp"
#include "./Style.hpp"

using namespace std;

using StyleHandler = function<void(Style &s, const string &)>;

class Element;

class StyleApplier
{
private:
    static unordered_map<string, StyleHandler> handlers;

public:
    static void apply(Element *element, StyleDef &styles);
    // unordered_map<string, StyleHandler> handlers;
};