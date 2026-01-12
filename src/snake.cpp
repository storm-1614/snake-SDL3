#include "../include/snake.h"
#include "../include/food.h"
#include "../include/game.h"
#include <SDL3/SDL_log.h>
#include <future>

std::list<point> snakeBody;
color snakeColor;
direction snakeDire;

void initSnake()
{
    snakeColor = color{0, 255, 0, 255};
    snakeDire = right;
    for (int i = 5; i >= 1; i--)
    {
        snakeBody.emplace_back(point{20 * i, 20});
    }
}

point nextPos()
{
    /*
     * 这一行代码我是真无语了
     * list 底层逻辑是双向链表,一大堆问题
     */
    point head = *(--snakeBody.end());
    switch (snakeDire)
    {
    case left:
        head.x -= 20;
        break;
    case right:
        head.x += 20;
        break;
    case up:
        head.y -= 20;
        break;
    case down:
        head.y += 20;
        break;
    default:
        break;
    }
    return head;
}
void updateSnake()
{
    point next = nextPos();

    if (next.x != foodPos.x && next.y != foodPos.y)
    {
        snakeBody.erase(snakeBody.begin());
        snakeBody.emplace_back(next);
    }
}

void debugSnakeData()
{
    SDL_Log("LOG：蛇身数据结构信息打印");
    for (auto iter : snakeBody)
    {
        SDL_Log("x=%d, y=%d", iter.x, iter.y);
    }
    SDL_Log("=========================");
}

void drawSnake()
{
    debugSnakeData();
    for (auto iter : snakeBody)
    {
        drawRect(iter.x, iter.y, snakeColor);
    }
}
