#include <stdio.h>
#include <assert.h>

int input(char str[]) {
    int ta;
    printf("%s", str);
    scanf("%d", &ta);
    return ta;
}

void pedirArreglo(int a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("elem_%d = ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");
}

int cantidad(int array[], int tam, int elem) {
    int cont = 0;
    for (int i = 0; i < tam; i++) {
        if (array[i] == elem) {
            cont++;
        }
    }
    return cont;
}

int main(void) {
    int tam = input("tamaño = ");
    assert(tam>=0);
    int N = input("Elemento a comparar = ");
    int array[tam];

    pedirArreglo(array, tam);

    int res = cantidad(array, tam, N);

    printf("La cantidad de '%d' presentes en el array es: %d\n", N, res);
}