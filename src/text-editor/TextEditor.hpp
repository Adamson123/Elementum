#pragma once
#include <SDL.h>

class TextEditor
{
public:
    TextEditor(float windowWidth, float windowHeight);

    float windowWidth;
    float windowHeight;

    void Init();
    void Run(SDL_Renderer *renderer);
    void ListenToEvent(SDL_Event *event);
};
