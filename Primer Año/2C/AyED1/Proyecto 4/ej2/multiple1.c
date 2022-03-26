#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

int main(void) {
    int x, y, xaux;
    x = input("x=");
    y = input("y=");

    xaux = x;
    x = x + 1;
    y = xaux + y;

    printf("x=%x, y=%d", x, y);
}