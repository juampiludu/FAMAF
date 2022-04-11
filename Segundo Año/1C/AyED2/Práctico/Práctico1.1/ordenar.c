#include <stdio.h>

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0u; i < length; ++i) {
        if (i == length-1) {
            printf("%d", a[i]);
        }
        else {
            printf("%d, ", a[i]);
        }
    }
    printf("]\n");
}

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
        array_dump(a, length);
        aux = posMinDesde(a, length, pos);
        swap(a, pos, aux);
    }
}

int main(void) {
    int array[7] = {7,1,10,3,4,9,5};
    unsigned int length = 7u;
    ordenarSel(array, length);
    array_dump(array, length);
}