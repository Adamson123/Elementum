#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include "../element/window/Window.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/StyleApplier.hpp"

using namespace std;

class TextEditor
{
public:
    TextEditor(float windowWidth, float windowHeight);

    float windowWidth;
    float windowHeight;

    void Init();
    void Run(SDL_Renderer *renderer);
    void End();
    void ListenToEvent(SDL_Event *event);

    unique_ptr<FontManager> fontManager;
    unique_ptr<Window> window;
    unique_ptr<StyleApplier> styleApplier;
};
