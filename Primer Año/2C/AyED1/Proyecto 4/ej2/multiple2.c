#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

int main(void) {
    int x, y, z, xaux, yaux;
    x = input("x=");
    y = input("y=");

    xaux = x;
    yaux = y;
    x = y;
    y = y + xaux + z;
    z = yaux + xaux;

    printf("x=%x, y=%d, z=%d", x, y, z);
}