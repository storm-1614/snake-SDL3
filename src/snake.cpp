#include "../include/snake.h"
#include "../include/food.h"
#include "../include/game.h"
#include <SDL3/SDL_log.h>
#include <algorithm>

std::deque<point> snakeBody;
color snakeColor;
direction snakeDire;

void initSnake()
{
    snakeColor = color{0, 0, 255, SDL_ALPHA_OPAQUE};
    snakeDire = right;
    for (int i = 5; i >= 1; i--)
    {
        snakeBody.push_front(point{20 * i, 20});
    }
}

point nextPos()
{
    /*
     * 这一行代码我是真无语了
     * list 底层逻辑是双向链表,一大堆问题
     */
    point head = snakeBody.back();
    SDL_Log("head：x=%d, y=%d", head.x, head.y);
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
    if (head.x >= 800)
        head.x = 0;
    else if (head.x < 0)
        head.x = 800;
    if (head.y >= 600)
        head.y = 0;
    else if (head.y < 0)
        head.y = 600;

    return head;
}

void updateSnake()
{
    point next = nextPos();

    if (std::find(snakeBody.begin(), snakeBody.end(), next) != snakeBody.end())
    {
        SDL_Log("You Died");
        exit(0);
    }
    if (next.x == foodPos.x && next.y == foodPos.y)
    {
        snakeBody.push_back(next);
        foodPos = randomFood();
    }
    else
    {
        snakeBody.pop_front();
        snakeBody.push_back(next);
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
    for (auto iter : snakeBody)
    {
        drawRect(iter.x, iter.y, snakeColor);
    }
}
