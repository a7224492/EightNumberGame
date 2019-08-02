#include <stdio.h>
#include "print.h"

void show(int x, int y, int color) {
    // x方向坐标是终端坐标的二分之一
    int realx = x * 2;
    printf("\033[%d;%dH\033[%d;37m  \n", y, realx, color);
}

void clear(int x, int y)
{
    int realx = x * 2;
    printf("\033[0m\033[%d;%dH  \n", y, realx);
}

// 清屏
void clearAll() {
    printf("\033[2J\n");
}