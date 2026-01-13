#include "../include/snake.h"
#include "../include/food.h"
#include "../include/game.h"
#include <SDL3/SDL_log.h>
#include <algorithm>

/*
 * 用双向队列存储蛇的位置，方便头尾插入删除，还能用 std::find
 */
std::deque<point> snakeBody;
color snakeColor;
direction snakeDire;

/*
 * 初始化蛇
 * 初始化蛇的颜色
 * 确定默认方向
 * 初始化长度为 5 的蛇身
 */
void initSnake()
{
    snakeColor = color{0, 0, 255, SDL_ALPHA_OPAQUE};
    snakeDire = right;
    for (int i = 5; i >= 1; i--)
    {
        snakeBody.push_front(point{20 * i, 20});
    }
}

/*
 * 获得下一步的位置
 */
point nextPos()
{
    /*
     * INFO: 这一行代码我是真无语了
     * list 底层逻辑是双向链表,一大堆问题
     * 然后我换成了 deque 双向链表 解决问题！！！
     * STL 和数据结构还是不太熟
     */
    // 获得头部信息
    point head = snakeBody.back();
    SDL_Log("LOG: head：x=%d, y=%d", head.x, head.y);
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
    // 穿墙逻辑
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

void debugSnakeData()
{
    SDL_Log("=========================");
    SDL_Log("LOG：蛇身数据结构信息打印");
    for (auto iter : snakeBody)
    {
        SDL_Log("x=%d, y=%d", iter.x, iter.y);
    }
    SDL_Log("=========================");
}

/*
 * 更新蛇
 * 获得下一步的位置
 * 进行吃到食物和吃到自己的判断
 */
void updateSnake()
{
    point next = nextPos();

    if (std::find(snakeBody.begin(), snakeBody.end(), next) != snakeBody.end())
    {
        SDL_Log("你死了");
        SDL_Log("分数: %d", score);
        exit(0);
    }
    else if (next.x == foodPos.x && next.y == foodPos.y)
    {
        score += 10;
        snakeBody.push_back(next);
        foodPos = randomFood();
    }
    else
    {
        snakeBody.pop_front();
        snakeBody.push_back(next);
    }
    debugSnakeData();
}

/*
* 蛇的绘制
*/
void drawSnake()
{
    for (auto iter : snakeBody)
    {
        drawRect(iter.x, iter.y, snakeColor);
    }
}
