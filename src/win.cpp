#include "../include/win.h"
#include "../include/font.h"
#include "../include/food.h"
#include "../include/game.h"
#include "../include/snake.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

// 主窗口
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
// 背景的 surface 和 texture
SDL_Surface *bgSurface = NULL;
SDL_Texture *bgTexture = NULL;

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

// 实现非阻塞变量
const double STEP = 0.1;
double accumulator = 0.0;

/*
 * 各项初始化函数
 * 初始化随机种子
 * 初始化 SDL
 * 初始化窗口和渲染器
 * 初始化背景图片
 */
void initWin()
{
    srand(time(NULL));
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

    // 加载背景图片
    SDL_IOStream *bgFile = SDL_IOFromFile("sources/background.png", "r");
    if (bgFile == NULL)
    {
        SDL_Log("错误：读取背景图片失败!");
        exit(2);
    }

    if ((bgSurface = IMG_LoadPNG_IO(bgFile)) == NULL)
    {
        SDL_Log("错误: 创建背景 surface 失败");
        exit(2);
    }

    if ((bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface)) == NULL)
    {
        SDL_Log("错误:创建 texture 失败");
        exit(2);
    }
    SDL_DestroySurface(bgSurface);
    bgSurface = NULL;

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // 禁用 alpha 混合以避免半透明效果
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    initFont();
    initFood();
    initSnake();
}

// 入口
void runWin()
/*
 * 让窗口跑起来的 damo（划掉）
 * 原本当 damo 的，但是没想到最后成了事实上的游戏入口
 * 大致分为了三部分：
 * 初始化
 * 主循环
 * 游戏结束资源释放
 * 这里主循环还分了：事件管理-更新数据-渲染窗口
 */
{
    Uint64 freq = SDL_GetPerformanceFrequency(); // 获取高精度计时器的频率
    Uint64 last = SDL_GetPerformanceCounter();   // 获取最初计时器的值

    initWin();

    bool running = true;
    while (running)
    /*
     * 主循环
     */
    {
        Uint64 now = SDL_GetPerformanceCounter(); // 获取现在计时器的值
        double delta = (double)(now - last) / freq;  // 计算差值
        last = now;
        accumulator += delta;

        std::string scoreStr = "分数: ";
        scoreStr += std::to_string(score);

        loadFont(white, scoreStr.c_str()); // 字体后台加载
        running = eventHandle();           // 事件处理

        while (accumulator >= STEP)
        {
            /*
             * 更新的内容放这里
             */
            updateSnake();

            accumulator -= STEP;
        }
        redraw(); // 绘制
    }

    quit();
}
