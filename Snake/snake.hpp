#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <deque>

struct Body {
    int x,y;
    int color;
};

class Snake {
private:
    std::deque<struct Body> bodyQueue;

public:
    Snake(int posx, int posy, int length);

    void draw();
};

#endif