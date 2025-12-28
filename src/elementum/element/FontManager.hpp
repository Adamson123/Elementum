#pragma once
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

class FontManager
{
public:
    TTF_Font *get(const string &path, int size)
    {
        auto key = path + to_string(size);

        if (!fonts.count(key))
        {
            fonts[key] = TTF_OpenFont(path.c_str(), size);
            if (!fonts[key])
                cout << TTF_GetError() << endl;
        }

        // cout << "Fonts length :" + to_string(fonts.size()) << endl;

        return fonts[key];
    }

    void clearFonts()
    {
        {
            for (auto &[_, font] : fonts)
                TTF_CloseFont(font);
        }
    }

    // ~FontManager()
    // {
    //     for (auto &[_, font] : fonts)
    //         TTF_CloseFont(font);
    // }

private:
    unordered_map<string, TTF_Font *> fonts;
};
