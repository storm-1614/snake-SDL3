#include "../include/game.h"
#include "../include/food.h"
#include "../include/snake.h"
#include "../include/win.h"
#include "../include/font.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

const int h = 20;
const int w = 20;
int score = 0;

/*
 * 绘制像素块
 * 输入坐标和颜色结构体
 */
void drawRect(int x, int y, color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    point dot{x, y};
    SDL_FRect rect{(float)dot.x, (float)dot.y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

/*
 * 通过包含图片的纹理在 rect 结构下进行贴图函数
 * 输入：纹理、矩形（包含坐标与大小）
 */
void drawPic(SDL_Texture *texture, SDL_FRect rect)
{
    // TODO: 解释
    SDL_Vertex verts[4] = {{{rect.x, rect.y}, {255, 255, 255, 255}, {0.0f, 0.0f}},
                           {{rect.x + rect.w, rect.y}, {255, 255, 255, 255}, {1.0f, 0.0f}},
                           {{rect.x + rect.w, rect.y + rect.h}, {255, 255, 255, 255}, {1.0f, 1.0f}},
                           {{rect.x, rect.y + rect.h}, {255, 255, 255, 255}, {0.0f, 1.0f}}};
    int indices[6] = {0, 1, 2, 2, 3, 0};
    SDL_RenderGeometry(renderer, texture, verts, 4, indices, 6); // 绘制
}

/*
 * 事件函数
 */
bool eventHandle()
{
    SDL_Event event;
    bool running = true;

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
    return running;
}

/*
 * 重绘函数
 */
void redraw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, bgTexture, NULL, NULL);
    drawSnake();
    drawFood();
    drawFont();
    SDL_RenderPresent(renderer);
}

/*
 * 销毁一些生成的堆变量函数
 */
void quit()
{
    destoryFood();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(bgTexture);
    destoryFont();
    SDL_Quit();
}
