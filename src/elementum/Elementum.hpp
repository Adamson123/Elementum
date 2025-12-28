#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

using namespace std;

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

    unique_ptr<FontManager> fontManager;
    unique_ptr<Window> window;
    unique_ptr<StyleApplier> styleApplier;
    unique_ptr<Painter> painter;
    unique_ptr<StyleComputer> styleComputer;
    SDL_Renderer *renderer;
};
