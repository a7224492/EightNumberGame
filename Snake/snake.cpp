#include "../common/view/print.h"
#include "snake.hpp"

Snake::Snake(int posx, int posy, int length) {
    currentFrame = 0;
    direction = 0;

    for (int i = 0; i < length; ++i) {
        bodyQueue.push_front({posx + i, posy, RED});
    }
}

void Snake::draw() {
    for (int i = 0; i < bodyQueue.size(); ++i) {
        struct Body body = bodyQueue.at(i);
        show(body.x, body.y, body.color);
    }
}

void Snake::clearView() {
    for (int i = 0; i < bodyQueue.size(); ++i) {
        struct Body body = bodyQueue.at(i);
        clear(body.x, body.y);
    }
}

void Snake::moveOneBody() {
    struct Body back = bodyQueue.back();
    struct Body front = bodyQueue.front();
    back = front;

    switch (direction) {
        case UP:
            back.y -= 1;
            break;
        case LEFT:
            back.x -= 1;
            break;
        case RIGHT:
            back.x += 1;
            break;
        case DOWN:
            back.y += 1;
            break;
    }

    bodyQueue.pop_back();
    bodyQueue.push_front(back);
}

void Snake::move() {
    ++currentFrame;
    if (currentFrame == v) {
        moveOneBody();
        currentFrame = 0;
    }
}

void Snake::changeDirection(int direction) {
    switch (this -> direction) {
        case UP:
        case DOWN:
            if (direction == LEFT || direction == RIGHT) {
                this->direction = direction;
            }
            break;
        case LEFT:
        case RIGHT:
            if (direction == UP || direction == DOWN) {
                this->direction = direction;
            }
            break;
        default:
            this->direction = direction;
            break;
    }
}