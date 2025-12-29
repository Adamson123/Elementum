#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "./StyleApplier.hpp"

unsigned char toU8(int v)
{
    return static_cast<unsigned char>(std::clamp(v, 0, 255));
};

std::vector<unsigned char> splitStringByComma(const std::string &text)
{
    std::vector<unsigned char> result;
    std::string item;
    std::stringstream ss(text);

    while (std::getline(ss, item, ','))
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

SDL_Color convertStringToColor(const std::string &v)
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

ParsedValue parseValue(const std::string &v)
{
    static const std::regex pxPattern("^-?\\d+(\\.\\d+)?px$");
    static const std::regex percentPattern("^-?\\d+(\\.\\d+)?%$");
    static const std::regex noUnitPattern("^\\d+$");

    if (std::regex_match(v, pxPattern) || std::regex_match(v, noUnitPattern))
    {
        return {std::stof(v), Unit::PX};
    }

    if (std::regex_match(v, percentPattern))
    {
        return {std::stof(v), Unit::PERCENT};
    }

    throw std::runtime_error("Invalid value: " + v);
}

// With callback
void setStartPosition(const std::string &v, std::function<void(StartPosition)> setter)
{
    if (v == "parent")
        setter(StartPosition::PARENT);
    else if (v == "prevSibling")
        setter(StartPosition::PREV_SIBLING);
    else
        throw std::runtime_error("Invalid value for start position: " + v);
}

StyleApplier::StyleApplier()
{
    //
    handlers["color"] = [](Element *element, const std::string &v)
    {
        element->setColor(convertStringToColor(v));
    };

    //
    handlers["backgroundColor"] = [](Element *element, const std::string &v)
    {
        element->setBackgroundColor(convertStringToColor(v));
    };

    //
    handlers["borderColor"] = [](Element *element, const std::string &v)
    {
        element->setBorderColor(convertStringToColor(v));
    };

    //
    handlers["borderWidth"] = [](Element *element, const std::string &v)
    {
        auto parsed = parseValue(v);
        element->setBorderWidth(parsed.value, parsed.unit);
    };

    //
    handlers["width"] = [](Element *element, const std::string &v)
    {
        auto parsed = parseValue(v);
        element->setWidth(parsed.value, parsed.unit);
    };

    //
    handlers["height"] = [](Element *element, const std::string &v)
    {
        auto parsed = parseValue(v);
        element->setHeight(parsed.value, parsed.unit);
    };

    //
    handlers["x"] = [](Element *element, const std::string &v)
    {
        auto parsed = parseValue(v);
        element->setX(parsed.value, parsed.unit);
    };

    //
    handlers["y"] = [](Element *element, const std::string &v)
    {
        auto parsed = parseValue(v);
        element->setY(parsed.value, parsed.unit);
    };

    //
    handlers["fontSize"] = [](Element *element, const std::string &v)
    {
        element->setFontSize(stoi(v));
    };

    //
    handlers["fontFamily"] = [](Element *element, const std::string &v)
    {
        element->setFontFamily(v);
    };

    //
    handlers["startX"] = [](Element *element, const std::string &v)
    {
        setStartPosition(v, [&](StartPosition pos)
                         { element->setStartX(pos); });
    };

    //
    handlers["startY"] = [](Element *element, const std::string &v)
    {
        setStartPosition(v, [&](StartPosition pos)
                         { element->setStartY(pos); });
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
            std::cerr << "Unknown style: " << key << "\n";
        }
    }
}
