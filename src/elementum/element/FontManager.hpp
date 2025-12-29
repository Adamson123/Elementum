#pragma once
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include <iostream>

/**
 * @brief The FontManager class manages the loading, caching,
 * and cleanup of TTF_Font objects using file paths and sizes as keys,
 * providing methods to retrieve fonts and clear all loaded fonts.
 * It uses an unordered_map to store font pointers and ensures fonts are loaded only once per unique path and size.

 */
class FontManager
{
public:
    TTF_Font *get(const std::string &path, int size)
    {
        // Key to the font generated from font file path and size
        auto key = path + std::to_string(size);

        // If the font does not exist, create and cache it
        if (!fonts.count(key))
        {
            fonts[key] = TTF_OpenFont(path.c_str(), size);
            if (!fonts[key])
                std::cout << TTF_GetError() << std::endl;
        }

        // cout << "Fonts length :" + to_string(fonts.size()) << endl;

        return fonts[key];
    }

    /** Clears all loaded fonts and releases their resources */
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
