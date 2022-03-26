#include <assert.h>
#include <stdio.h>
#include "entradas.h"

// Ejercicio 1

void ej1(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    int z = pedirEntero();
    printf("x + y + 1 = %d\n", x + y + 1);
    printf("z * z + y * 45 - 15 * x = %d\n", z * z + y * 45 - 15 * x);
    y = ((x * 3 + 1) % 5) - 2;
    printf("y - 2 == (x * 3 + 1) %% 5 = %d\n", y);
    printf("y / 2 * x = %d\n", y / 2 * x);
    printf("y < x * z = %d\n", y < x * z);
}

// |         Expresión          |  (x->7, y->3, z->5)  |  (x->1, y->10, z->8)  |
// | -------------------------  | -------------------  | --------------------  |
// |  x + y + 1                 |          11          |          12           |
// |  z * z + y * 45 - 15 * x   |          55          |          499          |
// |  y - 2 == (x * 3 + 1) % 5  |          0           |          2            |
// |  y / 2 * x                 |          0           |          1            |
// |  y < x * z                 |          1           |          1            |

// La ultima expresion es de tipo Bool, pero en C estan representados de otra manera, siendo 0 => False y 1 => True.


// Ejercicio 2

void ej2(void) {
    int x = -4;
    int y = 4;
    int z = -8;
    int b = 1;
    int w = 1;
    printf("x %% 4 == 0 = %d\n", x % 4 == 0);
    printf("x + y == 0 && y - x == (-1) * z = %d\n", x + y == 0 && y - x == (-1) * z);
    printf("not b && w = %d\n", !(b && w));
}

// Ejercicio 3

// a)

// 1.a

void ej3a1a(void) {
    int x = pedirEntero();
    assert(x != '\0');
    x = 5;
    printf("x -> %d\n", x);
}

// 1.b

void ej3a1b(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    assert(x != '\0');
    assert(y != '\0');
    x = x + y;
    printf("x -> %d, y -> %d\n", x, y);
    y = y + y;
    printf("x -> %d, y -> %d\n", x, y);
}

// 1.c

void ej3a1c(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    assert(x != '\0');
    assert(y != '\0');
    y = y + y;
    printf("x -> %d, y -> %d\n", x, y);
    x = x + y;
    printf("x -> %d, y -> %d\n", x, y);
}

// | programa        | usuario ingresa un σ0 | produce una salida σ |
// | --------------- | --------------------- | -------------------- |
// | 1.a ejecución 1 | x -> 1                | 5                    |
// | 1.a ejecución 2 | x -> 6                | 5                    |
// | 1.a ejecución 3 | x -> 75               | 5                    |
// | 1.b ejecución 1 | x -> 2, y -> 5        | 7, 10                |
// | 1.b ejecución 2 | x -> 35, y -> -86     | -51, -172            |
// | 1.b ejecución 3 | x -> 15, y -> 7       | 22, 14               |
// | 1.c ejecución 1 | x -> 5, y -> 5        | 10, 15               |
// | 1.c ejecución 2 | x -> -1, y -> 6       | 12, 11               |
// | 1.c ejecución 3 | x -> -5, y -> 3       | 6, 1                 |


// Ejercicio 4

// a)

// 1.e

void ej4a1eyf(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    if (x >= y) {
        printf("x -> %d, y -> %d\n", x, y);
        x = 0;
        printf("x -> %d, y -> %d\n", x, y);
    }
    else if (x <= y) {
        printf("x -> %d, y -> %d\n", x, y);
        x = 2;
        printf("x -> %d, y -> %d\n", x, y);
    }
    printf("x -> %d, y -> %d\n", x, y);
}

// b)

void ej4b(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    int z = pedirEntero();
    int m = pedirEntero();
    if (x < y) {
        m = x;
    }
    else if (x >= y) {
        m = y;
    }
    printf("x -> %d, y -> %d, z -> %d, m -> %d\n", x, y, z, m);
    if (m < z) {
    }
    else if (m >= z) {
        m = z;
    }
    printf("x -> %d, y -> %d, z -> %d, m -> %d\n", x, y, z, m);
}

// El valor final de la variable m es 4.


// Ejercicio 5

// a)

// 1.h

void ej5a1h(void) {
    int i = pedirEntero();
    while (i != 0) {
        printf("i -> %d\n", i);
        i = i - 1;
        printf("i -> %d\n", i);
    }
    printf("i -> %d\n", i);
}

// 1.i

void ej5a1i(void) {
    int i = pedirEntero();
    while (i != 0) {
        printf("i -> %d\n", i);
        i = 0;
        printf("i -> %d\n", i);
    }
    printf("i -> %d\n", i);
}

// b)

// b1

void ej5b1(void) {
    int x = pedirEntero();
    int y = pedirEntero();
    int i = pedirEntero();
    i = 0;
    while (x >= y)
    {
        x = x - y;
        i = i + 1;
        printf("x -> %d, y -> %d, i -> %d\n", x, y, i);
    }
}

// It 1: x -> 10, y -> 3, i -> 1
// It 2: x -> 7, y -> 3, i -> 2
// It 3: x -> 4, y -> 3, i -> 3
// It 4: x -> 1, y -> 3, i -> 4

// b2

void ej5b2(void) {
    int x = pedirEntero();
    int i = pedirEntero();
    int res = pedirEntero();
    assert(res >= 0 && res < 2);
    i = 2;
    res = 1;
    while (i < x && res) {
        res = res && (x % i) != 0;
        i = i + 1;
        printf("x -> %d, i -> %d, res -> %d\n", x, i, res);
    }
}

// It 1: x -> 5, i -> 3, res -> 1
// It 2: x -> 5, i -> 4, res -> 1
// It 3: x -> 5, i -> 5, res -> 1

// b3

// El ejercicio b1 reproduce lo que sería una resta de enteros o la suma del opuesto de un entero.
// El ejercicio b2 dice si un numero es primo.


///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
    int e;
    printf("Seleccione ejercicio: 1 - 2 - 3a1a - 3a1b - 3a1c - 4a1eyf - 4b - 5a1h - 5a1i - 5b1 - 5b2\n");
    printf("                     [1] [2]  [3]    [4]    [5]     [6]    [7]   [8]    [9]    [10]  [11]\n");
    scanf("%d", &e);
    switch (e)
    {
    case 1:
        ej1();
        break;
    case 2:
        ej2();
        break;
    case 3:
        ej3a1a();
        break;
    case 4:
        ej3a1b();
        break;
    case 5:
        ej3a1c();
        break;
    case 6:
        ej4a1eyf();
        break;
    case 7:
        ej4b();
        break;
    case 8:
        ej5a1h();
        break;
    case 9:
        ej5a1i();
        break;
    case 10:
        ej5b1();
        break;
    case 11:
        ej5b2();
        break;
    default:
        printf("Opcion inexistente.\n");
    }
}