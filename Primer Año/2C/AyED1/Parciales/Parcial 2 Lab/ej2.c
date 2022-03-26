#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int input(char str[]) {
    int ta;
    printf("%s", str);
    scanf("%d", &ta);
    return ta;
}

struct organizar_t {
    int primero;
    int segundo;
};

struct organizar_t mOrganizar;

struct organizar_t organizar(bool b, int x, int y) {
    if (b) {
        mOrganizar.primero = x;
        mOrganizar.segundo = y;
    }
    else {
        mOrganizar.primero = y;
        mOrganizar.segundo = x;
    }
    return mOrganizar;
}

int main(void) {
    int x, y;
    bool b;
    
    x = input("x = ");
    y = input("y = ");
    b = input("true[1] or false[0] = ");

    organizar(b, x, y);

    printf("Primera posicion: %d\n", mOrganizar.primero);
    printf("Segunda posicion: %d\n", mOrganizar.segundo);
}