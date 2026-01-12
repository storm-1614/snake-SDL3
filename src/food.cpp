#include "../include/food.h"
#include "../include/game.h"
#include "../include/snake.h"
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cstdlib>
#include <SDL3_image/SDL_image.h>

color foodColor;
point foodPos;

SDL_IOStream *foodImage = NULL;
SDL_Surface *foodImageSurface = NULL;
SDL_Texture *foodImageTexture = NULL;
void initFood()
{
    foodColor = color{.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};
    foodPos = randomFood();
}
point randomFood()
{
    bool flag = false;
    point pos;
    while (!flag)
    {
        int x = rand() % (800/20);
        int y = rand() % (600/20);
        pos.x = x*20;
        pos.y = y*20;
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
    drawRect(foodPos.x, foodPos.y, foodColor);
}
