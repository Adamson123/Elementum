#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "./StyleApplier.hpp"

using namespace std;

unsigned char toU8(int v)
{
    return static_cast<unsigned char>(clamp(v, 0, 255));
};

vector<unsigned char> splitStringByComma(const string &text)
{
    vector<unsigned char> result;
    string item;
    stringstream ss(text);

    while (getline(ss, item, ','))
    {
        try
        {
            result.push_back(toU8(stoi(item)));
        }
        catch (const std::exception &)
        {
            return {0, 0, 0, 0};
        }
    }

    if (result.size() != 4)
        return {0, 0, 0, 0};

    return result;
}

SDL_Color convertStringToColor(const string &v)
{
    if (v == "red")
    {
        return {255, 0, 0, 255};
    }
    auto c = splitStringByComma(v);
    return {c[0], c[1], c[2], c[3]};
}

struct ParsedValue
{
    float value;
    Unit unit;
};

ParsedValue parseValue(const string &v)
{
    static const regex pxPattern("^-?\\d+(\\.\\d+)?px$");
    static const regex percentPattern("^-?\\d+(\\.\\d+)?%$");
    static const regex noUnitPattern("^\\d+$");

    if (regex_match(v, pxPattern) || regex_match(v, noUnitPattern))
    {
        return {stof(v), Unit::PX};
    }

    if (regex_match(v, percentPattern))
    {
        return {stof(v), Unit::PERCENT};
    }

    throw runtime_error("Invalid value: " + v);
}

StyleApplier::StyleApplier()
{
    handlers["color"] = [](Element *element, const string &v)
    {
        element->setColor(convertStringToColor(v));
    };

    handlers["backgroundColor"] = [](Element *element, const string &v)
    {
        element->setBackgroundColor(convertStringToColor(v));
    };

    handlers["borderColor"] = [](Element *element, const string &v)
    {
        element->setBorderColor(convertStringToColor(v));
    };

    handlers["borderWidth"] = [](Element *element, const string &v)
    {
        auto parsed = parseValue(v);
        element->setBorderWidth(parsed.value, parsed.unit);
    };

    handlers["width"] = [](Element *element, const string &v)
    {
        auto parsed = parseValue(v);
        element->setWidth(parsed.value, parsed.unit);
    };

    handlers["height"] = [](Element *element, const string &v)
    {
        auto parsed = parseValue(v);
        element->setHeight(parsed.value, parsed.unit);
    };

    handlers["x"] = [](Element *element, const string &v)
    {
        auto parsed = parseValue(v);
        element->setX(parsed.value, parsed.unit);
    };

    handlers["y"] = [](Element *element, const string &v)
    {
        auto parsed = parseValue(v);
        element->setY(parsed.value, parsed.unit);
    };
}

void StyleApplier::apply(Element *element, StyleDef &styles)
{
    for (const auto &[key, value] : styles)
    {
        auto it = handlers.find(key);
        if (it != handlers.end())
        {
            it->second(element, value);
        }
        else
        {
            cerr << "Unknown style: " << key << "\n";
        }
    }
}
