#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class FontManager;
class Window;
class StyleApplier;
class Painter;
class StyleComputer;

class Elementum
{
public:
    Elementum(float windowWidth, float windowHeight, SDL_Renderer *renderer);
    ~Elementum();

    float windowWidth;
    float windowHeight;

    void Init();
    void Run();
    void End();
    void Event(SDL_Event *event);

    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<Window> window;
    std::unique_ptr<StyleApplier> styleApplier;
    std::unique_ptr<Painter> painter;
    std::unique_ptr<StyleComputer> styleComputer;
    SDL_Renderer *renderer;
};
