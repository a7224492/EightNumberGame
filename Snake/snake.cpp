#include "../common/print.h"
#include "snake.hpp"

Snake::Snake(int posx, int posy, int length) {
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