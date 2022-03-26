#include <stdio.h>
#include "../tools/entradas.h"

int suma_hasta(int N) {
    int gauss = ( N * (N + 1) ) / 2;
    return gauss;
}

int main(void) {
    int N = pedirEntero();
    if (N < 0)
    {
        printf("Error, el número ingresado debe ser positivo.\n");
    }
    else
    {
        printf("%d\n", suma_hasta(N));
    }
    return 0;
}