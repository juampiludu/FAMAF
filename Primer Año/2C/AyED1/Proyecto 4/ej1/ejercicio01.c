#include <stdio.h>
#include <assert.h>
#include "../tools/entradas.h"

void holaHasta(int n) {
    int i = 0;
    while (i < n)
    {
        printf("hola\n");
        i = i+1;
    }
    
}

int main(void) {
    int x = pedirEntero();
    assert(x>0);
    holaHasta(x);
    return 0;
}