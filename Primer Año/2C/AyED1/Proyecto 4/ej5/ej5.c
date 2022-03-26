#include <stdio.h>

void pedirArreglo(int a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("elem_%d = ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");
}

void imprimeArreglo(int a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

int main(void) {
    int n_max;
    printf("n_max = ");
    scanf("%d", &n_max);
    int array[n_max];
    pedirArreglo(array, n_max);
    imprimeArreglo(array, n_max);
    return 0;
}