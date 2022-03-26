#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

struct datos_t {
    float maximo;
    float minimo;
    float promedio;
};

struct datos_t datosT;

struct datos_t stats(float a[], int tam) {
    float sumatoria = sumatoriaFloat(a, tam);
    float minimo = a[0];
    float maximo = a[0];
    float promedio = sumatoria/tam;
    for (int i = 0; i < tam; i++) {
        if (a[i] < minimo) {
            minimo = a[i];
        }
        if (a[i] > maximo) {
            maximo = a[i];
        }
    }
    datosT.minimo = minimo;
    datosT.maximo = maximo;
    datosT.promedio = promedio;
    return datosT;
}

int main(void) {
    int tam = input("tam = ");
    assert(tam>=0);
    float arr[tam];
    pedirArregloFloat(arr, tam);
    imprimeArregloFloat(arr, tam);
    stats(arr, tam);
    printf("\nMinimo: %f\n", datosT.minimo);
    printf("Maximo: %f\n", datosT.maximo);
    printf("Promedio: %f\n", datosT.promedio);
}