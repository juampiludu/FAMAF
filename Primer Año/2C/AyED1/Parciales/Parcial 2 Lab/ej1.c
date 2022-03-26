#include <stdio.h>
#include <assert.h>

int input(char str[]) {
    int ta;
    printf("%s", str);
    scanf("%d", &ta);
    return ta;
}

int main(void) {
    int x, y, z, xaux, yaux;

    x = input("x = ");
    y = input("y = ");
    z = input("z = ");

    assert(z-y!=0 && x-y!=0);

    xaux = x;
    yaux = y;
    x = (z - y) / (x - y);
    y = z % xaux;

    assert(x==((z - yaux) / (xaux - yaux)) && y==z%xaux);

    printf("x = %d, y = %d, z = %d\n", x, y, z);
}