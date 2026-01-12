#include "../include/food.h"
#include "../include/game.h"
#include "../include/snake.h"
#include "../include/win.h"
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <cstdlib>

color foodColor;
point foodPos;

SDL_IOStream *foodImage = NULL;
SDL_Surface *foodImageSurface = NULL;
SDL_Texture *foodImageTexture = NULL;

void initFood()
{
    foodColor = color{.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};
    foodPos = randomFood();
    if ((foodImage = SDL_IOFromFile("sources/apple.png", "r")) == NULL)
    {
        SDL_Log("错误：读取食物图片失败");
        exit(2);
    }
    if ((foodImageSurface = IMG_LoadPNG_IO(foodImage)) == NULL)
    {
        SDL_Log("错误：创建食物 surface 失败");
        exit(2);
    }
    if ((foodImageTexture = SDL_CreateTextureFromSurface(renderer, foodImageSurface)) == NULL)
    {
        SDL_Log("错误：创建食物 texture 失败");
        exit(2);
    }
    SDL_DestroySurface(foodImageSurface);
    foodImageSurface = NULL;
}
point randomFood()
{
    bool flag = false;
    point pos;
    while (!flag)
    {
        int x = rand() % (800 / 20);
        int y = rand() % (600 / 20);
        pos.x = x * 20;
        pos.y = y * 20;
        if (std::find(snakeBody.begin(), snakeBody.end(), pos) == snakeBody.end())
        {
            SDL_Log("Log: 生成一个食物");
            flag = true;
        }
    }
    return pos;
}

void drawFood()
{
    SDL_FRect rect{(float)foodPos.x, (float)foodPos.y, 20, 20};
    drawPic(foodImageTexture, rect);
}

void destoryFood()
{
    SDL_DestroyTexture(foodImageTexture);
}
