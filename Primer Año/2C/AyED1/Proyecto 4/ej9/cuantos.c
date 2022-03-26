#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

struct comp_t {
    int menores;
    int iguales;
    int mayores;
};

struct comp_t compT;

struct comp_t cuantos(int a[], int tam, int elem) {
    for (int i = 0; i < tam; i++) {
        if (a[i] < elem) {
            compT.menores = compT.menores + 1;
        }
        else if (a[i] > elem) {
            compT.mayores = compT.mayores + 1;
        }
        else {
            compT.iguales = compT.iguales + 1;
        }
    }
    return compT;
}

int main(void) {
    int tam = input("tam = ");
    assert(tam>=0);
    int elem = input("elem = ");
    int arr[tam];
    pedirArreglo(arr, tam);
    cuantos(arr, tam, elem);
    printf("Mayores a %d = %d\n", elem, compT.mayores);
    printf("Menores a %d = %d\n", elem, compT.menores);
    printf("Iguales a %d = %d\n", elem, compT.iguales);
}