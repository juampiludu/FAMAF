#include <stdio.h>

void swap(int a[], int p1, int p2) {
    int tmp;
    tmp = a[p1];
    a[p1] = a[p2];
    a[p2] = tmp;
}

int posMinDesde(int a[], unsigned int length, int pizq) {
    int pm;
    pm = pizq;
    for (unsigned int p = pizq+1; p < length; p++) {
        if (a[p] < a[pm]) {
            pm = p;
        }
    }
    return pm;
}

void ordenarSel(int a[], unsigned int length) {
    int aux;
    for (unsigned int pos = 0u; pos < length-1; pos++) {
        aux = posMinDesde(a, length, pos);
        swap(a, pos, aux);
    }
}

int main(void) {
    int array[5] = {5,8,2,9,-1};
    ordenarSel(array, 5);
    printf("a[0]: %d\n", array[0]);
    printf("a[1]: %d\n", array[1]);
    printf("a[2]: %d\n", array[2]);
    printf("a[3]: %d\n", array[3]);
    printf("a[4]: %d\n", array[4]);
}