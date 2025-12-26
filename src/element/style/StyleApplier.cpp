#include <iostream>
#include <sstream>
#include <vector>
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
    auto c = splitStringByComma(v);
    return {c[0], c[1], c[2], c[3]};
}

StyleApplier::StyleApplier()
{
    handlers = {

        {"color", [](Style &s, const string &v)
         { s.color = convertStringToColor(v); }},

        {"backgroundColor", [](Style &s, const string &v)
         { s.backgroundColor = convertStringToColor(v); }},

        {"borderColor", [](Style &s, const string &v)
         { s.borderColor = convertStringToColor(v); }}};
}

void StyleApplier::apply(Element *element, StyleDef &styles)
{
    for (const auto &[key, value] : styles)
    {
        auto it = handlers.find(key);
        if (it != handlers.end())
        {
            it->second(element->style, value);
        }
        else
        {
            cerr << "Unknown style: " << key << "\n";
        }
    }
}
