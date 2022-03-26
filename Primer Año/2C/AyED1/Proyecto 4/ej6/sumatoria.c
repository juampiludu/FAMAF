#include <stdio.h>
#include <assert.h>
#include "../tools/tools.c"

int sumatoria(int a[], int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        suma = suma + a[i];
    }
    return suma;
}

int main(void) {
    int tam = input("tam: ");
    assert(tam>=0);
    int arr[tam];
    pedirArreglo(arr, tam);
    imprimeArreglo(arr, tam);
    int sum = sumatoria(arr, tam);
    printf("La sumatoria es: %d\n", sum);
    return 0;
}