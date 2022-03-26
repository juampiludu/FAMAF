#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

bool existe_positivo(int a[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (a[i] >= 0) {
            return true;
        }
    }
    return false;
}

bool todos_positivos(int a[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (a[i] < 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int tam = input("tam = ");
    assert(tam>=0);
    int arr[tam];
    pedirArreglo(arr, tam);
    imprimeArreglo(arr, tam);
    int choice;
    printf("\nTodos positivos [0] o existe positivo [1]: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 0:
        printf(todos_positivos(arr, tam) ? "true\n" : "false\n");
        break;
    
    default:
        printf(existe_positivo(arr, tam) ? "true\n" : "false\n");
        break;
    }
    return 0;
}