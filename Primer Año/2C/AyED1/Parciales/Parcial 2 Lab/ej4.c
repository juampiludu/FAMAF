#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int input(char str[]) {
    int ta;
    printf("%s", str);
    scanf("%d", &ta);
    return ta;
}

struct producto_t {
    int codigo;
    int precio;
    int cantidad;
};

bool hay_cantidad(int codigo, int cantidad_requerida, struct producto_t a[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (a[i].codigo == codigo) {
            if (cantidad_requerida <= a[i].cantidad) {
                return true;
            }
        }
    }
    return false;
}

void pedirArreglo(struct producto_t a[], int n_max) {
    for (int i = 0; i < n_max; i++) {
        printf("\nProducto %d\n", i+1);
        printf("Codigo = ");
        scanf("%d", &a[i].codigo);
        printf("Precio = ");
        scanf("%d", &a[i].cantidad);
        printf("Cantidad = ");
        scanf("%d", &a[i].precio);
    }
    printf("\n");
}

int main(void) {
    int tam = 3;
    
    struct producto_t arr[tam];
    
    pedirArreglo(arr, tam);
    
    int codigo = input("Codigo del producto = ");
    int cant = input("Cantidad requerida = ");

    printf(hay_cantidad(codigo, cant, arr, tam) ? "Hay productos disponibles.\n" : "No hay productos disponibles\n");
}