#pragma once
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <iostream>

class FontManager
{
public:
    TTF_Font *get(const std::string &path, int size)
    {
        auto key = path + std::to_string(size);

        if (!fonts.count(key))
        {
            fonts[key] = TTF_OpenFont(path.c_str(), size);
            if (!fonts[key])
                std::cout << TTF_GetError() << std::endl;
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
    std::unordered_map<std::string, TTF_Font *> fonts;
};
