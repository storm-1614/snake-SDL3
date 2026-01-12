#include "../include/win.h"
#include "../include/game.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int WINDOW_HEIGHT = 640;
const int WINDOW_WIDTH = 480;

void initWin()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("错误: SDL 初始化失败");
        exit(1);
    }
    if (!SDL_CreateWindowAndRenderer("Game", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
    {
        SDL_Log("错误: 窗口创建失败");
        exit(1);
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    SDL_SetRenderDrawColor(renderer, 16, 0, 16, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void runWin()
{
    initWin();
    SDL_Event event;

    bool running = true;
    while (running)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
