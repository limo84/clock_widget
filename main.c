#include "SDL_FontCache/SDL_FontCache.h"

#include <SDL2/SDL_render.h>

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

SDL_Window *window;
SDL_Renderer *renderer;
Uint8 running = 1;

int main()
{
    time_t t;
    struct tm tm;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Video init failed: %s", SDL_GetError());
    }

    Uint32 flags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP;

    window = SDL_CreateWindow("clock_widget", SDL_WINDOWPOS_CENTERED, 30, 168, 36, flags);
    if (window < 0)
    {
        printf("Window init failed: %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FC_Font *font = FC_CreateFont();
    FC_LoadFont(font, renderer, "LiberationSans-Regular.ttf", 40, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    int runtime = 0;
    while (runtime < 3000)
    {
        t = time(NULL);
        tm = *localtime(&t);

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        FC_Draw(font, renderer, 5, 2, "%.2d:%.2d:%.2d", tm.tm_hour, tm.tm_min, tm.tm_sec);
        SDL_RenderPresent(renderer);

        runtime = SDL_GetTicks();
        SDL_Delay(500);
    }

    FC_FreeFont(font);
    SDL_Quit();
    return 0;
}