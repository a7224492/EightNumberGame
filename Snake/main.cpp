#include <stdio.h>
#include "defines.h"
#include "snake.hpp"

#include "../common/print.h"

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
    // clear terminal
    clearAll();

    drawFrame();

    Snake snake(5,5,4);
    snake.draw();

    return 1;
}