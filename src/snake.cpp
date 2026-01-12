#include "../include/snake.h"
#include "../include/game.h"

std::list<point> snakeBody;
color snakeColor;
void initSnake()
{
    snakeColor = color{255, 0, 0, 255};
    for (int i = 1; i <= 5; i++)
    {
        snakeBody.emplace_back(point{20 * i, 20});
    }
}

void drawSnake()
{
    for (auto iter : snakeBody)
    {
        drawRect(iter.x, iter.y, snakeColor);
    }
}
