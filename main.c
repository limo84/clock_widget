#include "SDL_FontCache/SDL_FontCache.h"

#include <SDL2/SDL_render.h>

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
Uint8 running = 1;

int main()
{
    time_t t;
    struct tm tm;
    t = time(NULL);
    tm = *localtime(&t);
    // printf("Current Time: %d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Video init failed: %s", SDL_GetError());
    }

    // Uint32 flags = 0;
    Uint32 flags = SDL_WINDOW_BORDERLESS;

    window = SDL_CreateWindow("asd", SDL_WINDOWPOS_CENTERED, 100, 150, 30, flags);
    if (window < 0)
    {
        printf("Window init failed: %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FC_Font *font = FC_CreateFont();
    FC_LoadFont(font, renderer, "LiberationSans-Regular.ttf", 28, FC_MakeColor(255, 0, 0, 255), TTF_STYLE_NORMAL);

    while (running)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            running = 0;
        }

        

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

        // FC_Draw(font, renderer, 0, 0, "This is %s.\n It works.", "example text");
        t = time(NULL);
        tm = *localtime(&t);
        FC_Draw(font, renderer, 5, 2, "%.2d:%.2d:%.2d", tm.tm_hour, tm.tm_min, tm.tm_sec);

        SDL_RenderPresent(renderer);

        SDL_Delay(30);
    }

    FC_FreeFont(font);

    SDL_Quit();
    return 0;
}