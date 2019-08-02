#include <stdio.h>
#include <unistd.h>
#include "defines.h"
#include "snake.hpp"
#include "../common/keyboard/key.h"

#include "../common/view/print.h"

// game frame
void drawFrame() {
    // up
    for (int i = 0; i <= GAME_WIDTH; ++i) {
        show(i, 0, BLUE);
    }

    // left
    for (int i = 1; i <= GAME_HEIGHT - 1; ++i) {
        show(0, i, BLUE);
    }

    // right
    for (int i = 1; i <= GAME_HEIGHT - 1; ++i) {
        show(GAME_WIDTH, i, BLUE);
    }

    // bottom
    for (int i = 0; i <= GAME_WIDTH; ++i) {
        show(i, GAME_HEIGHT - 1, BLUE);
    }
}

int main(int argc, char **argv) {
    tty_set();

    // clear terminal
    clearAll();

    drawFrame();

    Snake snake(5,5,4);
    snake.changeDirection(RIGHT);
    snake.setV(1);
    snake.draw();

    bool isFinish = false;
    while (!isFinish) {
        snake.clearView();
        snake.move();

        if (kbhit()) {
            int key = getchar();
            switch (key) {
                case 'w':
                    snake.changeDirection(UP);
                    break;
                case 'a':
                    snake.changeDirection(LEFT);
                    break;
                case 'd':
                    snake.changeDirection(RIGHT);
                    break;
                case 's':
                    snake.changeDirection(DOWN);
                    break;
            }
        } else {
        }

        snake.draw();
        sleep(1);
    }

    return 1;
}