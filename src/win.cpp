#include "../include/win.h"
#include "../include/food.h"
#include "../include/snake.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *bgSurface = NULL;
SDL_Texture *bgTexture = NULL;

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
    // 加载图片
    SDL_IOStream *bgFile = SDL_IOFromFile("sources/background.png", "rw");
    if (bgFile == NULL)
    {
        SDL_Log("错误：读取背景图片失败!");
        exit(2);
    }
    bgSurface = IMG_LoadPNG_IO(bgFile);
    if (bgSurface == NULL)
    {
        SDL_Log("错误: 创建 surface 失败");
        exit(2);
    }
    bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    if (bgTexture == NULL)
    {
        SDL_Log("错误:创建 texture 失败");
        exit(2);
    }
    SDL_DestroySurface(bgSurface);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    // 禁用 alpha 混合以避免半透明效果
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
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

        //        SDL_PollEvent(&event);
        //        switch (event.type)
        //        {
        //        case SDL_EVENT_QUIT:
        //            running = false;
        //        case SDL_EVENT_KEY_DOWN:
        //
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                switch (event.key.key)
                {
                case SDLK_W:
                    if (snakeDire != down)
                        snakeDire = up;
                    break;
                case SDLK_A:
                    if (snakeDire != right)
                        snakeDire = left;
                    break;
                case SDLK_S:
                    if (snakeDire != up)
                        snakeDire = down;
                    break;
                case SDLK_D:
                    if (snakeDire != left)
                        snakeDire = right;
                    break;
                }
            }
        }

        while (accumulator >= STEP)
        /*
         * 更新的内容放这里
         */
        {
            updateSnake();
            accumulator -= STEP;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, bgTexture, NULL, NULL);
        drawSnake();
        drawFood();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(bgTexture);
    SDL_Quit();
}
