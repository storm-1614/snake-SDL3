#include "../include/food.h"
#include "../include/game.h"
#include "../include/snake.h"
#include <SDL3/SDL_log.h>
#include <algorithm>
#include <cstdlib>

color foodColor;
point foodPos;
void initFood()
{
    foodColor = color{.r = 255, .g = 0, .b = 0, .a = 255};
    foodPos = randomFood();
}
point randomFood()
{
    bool flag = false;
    point foodPos;
    while (!flag)
    {

        int x = rand() % 800 + 1;
        int y = rand() % 600 + 1;
        foodPos.x = x;
        foodPos.y = y;
        if (std::find(snakeBody.begin(), snakeBody.end(), foodPos) == snakeBody.end())
        {
            SDL_Log("Log: 生成一个食物");
            flag = true;
        }
    }
    return foodPos;
}

void drawFood()
{
    drawRect(foodPos.x, foodPos.y, foodColor);
}
