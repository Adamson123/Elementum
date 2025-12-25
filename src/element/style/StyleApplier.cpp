#include <iostream>
#include <sstream>
#include <vector>
#include "./StyleApplier.hpp"

using namespace std;

void StyleApplier::apply(Element *element, StyleDef &styles)
{
    for (const auto &[key, value] : styles)
    {
        if (auto it = handlers.find(key); it != handlers.end())
        {
            it->second(element->style, value);
        }
        else
        {
            cerr << "Unknown style: " << key << "\n";
        }
    }
}

vector<int> splitStringByComma(const string &text)
{
    vector<int> result;
    string item;
    stringstream ss(text);

    char comma = ',';
    bool isError = false;

    while (getline(ss, item, comma) && isError == false)
    {
        try
        {
            result.push_back(stoi(item));
        }
        catch (...)
        {
            isError = true;
        }
    }

    if (isError)
    {
        result = {0, 0, 0, 0};
    }

    return result;
}

auto toU8 = [](int v) -> unsigned char
{
    return static_cast<unsigned char>(clamp(v, 0, 255));
};

SDL_Color convertStringToColor(const string &v)
{
    auto c = splitStringByComma(v);
    return {toU8(c[0]), toU8(c[1]), toU8(c[2]), toU8(c[3])};
}

unordered_map<string, StyleHandler> StyleApplier::handlers = {
    {"color", [](Style &s, const string &v)
     {
         s.color = convertStringToColor(v);
     }},
    {"backgroundColor", [](Style &s, const string &v)
     {
         s.backgroundColor = convertStringToColor(v);
     }}};
