#include "../include/win.h"
#include "../include/food.h"
#include "../include/snake.h"
#include "../include/game.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;
const int FRAME_RER_SECOND = 24;
const double STEP = 0.1;
double accumulator = 0.0;

Uint64 freq = SDL_GetPerformanceFrequency();
Uint64 last = SDL_GetPerformanceCounter();

void initWin()
{
    srand(time(NULL));
    initFood();
    initSnake();
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

    if (SDL_SetRenderVSync(renderer, 1) == false)
    // WARN: 这块代码没有用 本来是想弄帧率的
    {
        SDL_Log("错误: VSync 错误");
        exit(1);
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void runWin()
/*
 * 让窗口跑起来的 damo
 */
{
    initWin();
    SDL_Event event;

    bool running = true;
    while (running)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double delta = (double)(now - last) / freq;
        last = now;
        accumulator += delta;

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            running = false;
        }

        while (accumulator >= STEP)
        {
            DrawFood();
            accumulator -= STEP;
        }
        drawSnake();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
