#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

typedef struct _persona {
    char *nombre;
    int edad;
    float altura;
    float peso;
} persona_t;

float peso_promedio(persona_t arr[], unsigned int longitud) {
    float tot;
    for (unsigned int i = 0; i < longitud; i++) {
        tot = tot + arr[i].peso;
    }
    float promedio = tot / longitud;
    return promedio;
}

persona_t persona_de_mayor_edad(persona_t arr[], unsigned int longitud) {
    persona_t persona;
    int mayor = arr[0].edad;
    for (unsigned int i = 0; i < longitud; i++) {
        if (arr[i].edad > mayor) {
            mayor = arr[i].edad;
            persona = arr[i];
        }
    }
    return persona;
}
persona_t persona_de_menor_altura(persona_t arr[], unsigned int longitud) {
    persona_t persona;
    float menor = arr[0].altura;
    for (unsigned int i = 0; i < longitud; i++) {
        if (arr[i].altura < menor) {
            menor = arr[i].altura;
            persona = arr[i];
        }
    }
    return persona;
}

int main(void) {
    persona_t p1 = {"Paola", 21, 1.85, 75};
    persona_t p2 = {"Luis", 54, 1.75, 69};
    persona_t p3 = {"Julio", 40, 1.70, 80};
    unsigned int longitud = 3;
    persona_t arr[] = {p1, p2, p3};
    printf("El peso promedio es %f\n", peso_promedio(arr, longitud));
    persona_t p = persona_de_mayor_edad(arr, longitud);
    printf("El nombre de la persona con mayor edad es %s\n", p.nombre);
    p = persona_de_menor_altura(arr, longitud);
    printf("El nombre de la persona con menor altura es %s\n", p.nombre);
    return 0;
}