#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0) {
        y = x;
    }
    else {
        y = -x;
    }
}

int main(void) {
    int a, res;

    res = 0;
    a = -98;

    absolute(a, res);

    printf("res=%d\n", res);
    // Se printea el valor res=0, que difiere al resultado del lenguaje del teórico

    res = 0;

    return EXIT_SUCCESS;
}