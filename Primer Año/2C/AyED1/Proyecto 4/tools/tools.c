#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int pedirEntero(void)
{
    int x;
    printf("Ingrese un número: ");
    scanf("%d", &x);
    return x;
}

void imprimeEntero(int x)
{
    printf("%d\n", x);
}

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

void imprimeArreglo(int a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
}

void pedirArregloFloat(float a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("elem_%d = ", i);
        scanf("%f", &a[i]);
    }
    printf("\n");
}

void imprimeArregloFloat(float a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("a[%d] = %f\n", i, a[i]);
    }
}

int sumatoria(int a[], int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        suma = suma + a[i];
    }
    return suma;
}

float sumatoriaFloat(float a[], int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        suma = suma + a[i];
    }
    return suma;
}

bool primo(int x) {
    int i = 2;
    while ((x%i!=0) && (x>1)) {
        i++;
    }
    return (i==x);
}