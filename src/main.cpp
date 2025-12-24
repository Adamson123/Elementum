#include <SDL_ttf.h>
#include <iostream>
#include "text-editor/TextEditor.hpp"
#include "Constants.h"

using namespace Constants;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Text editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TextEditor textEditor(0, 0);
    textEditor.Init();

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            textEditor.ListenToEvent(&event);

            // std::cout << event.type << std::endl;
        }

        textEditor.Run(ren); // render/update every frame
        SDL_Delay(16);       // tiny sleep if not using vsync
    }

    textEditor.End();
    // TTF_CloseFont();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    TTF_Quit();
    return 0;
}