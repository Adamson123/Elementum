#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

using namespace std;

class FontManager;
class Window;
class StyleApplier;

class TextEditor
{
public:
    TextEditor(float windowWidth, float windowHeight);
    ~TextEditor();

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
