#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <deque>

#define UP    1
#define LEFT  2
#define RIGHT 3
#define DOWN  4

struct Body {
    int x,y;
    int color;
};

class Snake {
private:
    std::deque<struct Body> bodyQueue;

    int currentFrame;
    int v;
    int direction;

    void moveOneBody();
public:
    Snake(int posx, int posy, int length);

    void setV(int v){this->v = v;}
    void changeDirection(int direction);

    void move();
    void draw();
    void clearView();
};

#endif