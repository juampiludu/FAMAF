#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

void intercambiar(int a[], int tam, int i, int j) {
    assert(i < tam && j < tam);
    int x = a[i];
    int y = a[j];
    a[i] = y;
    a[j] = x;
}

int main(void) {
    int tam = input("tam = ");
    int i = input("Valor i = ");
    int j = input("Valor j = ");
    int arr[tam];
    pedirArreglo(arr, tam);
    imprimeArreglo(arr, tam);
    intercambiar(arr, tam, i, j);
    printf("\n");
    imprimeArreglo(arr, tam);
    return 0;
}