#include <stdio.h>

// Ejercicio 6

// a)

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

// b)

// Las ventajas son que se ve un codigo mas simplificado, limpio, y sin la necesidad de repetir código.
// En esa funcion se podria reemplazar el printf con la funcion imprimeEntero().
// Se puede usar en todos los ejercicios donde se pida al usuario ingresar valores.