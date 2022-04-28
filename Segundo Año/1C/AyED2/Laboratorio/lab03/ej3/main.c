/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

    // Creando pointer para ints
    int *p = NULL;
    
    // asignando x al pointer y cambiando su valor
    p = &x;
    (*p) = (*p) + 8;
    
    // Creando pointer para person_t
    person_t *personPtr = NULL;
    
    // asignando m y cambiando los valores del struct
    personPtr = &m;
    personPtr->age = personPtr->age+10;
    personPtr->name_initial = personPtr->name_initial-7;
    
    // Cambio el valor de p para ahora darle a[1]
    p = &a[1];
    
    // Cambio el valor de a[1] por el valor solicitado
    (*p) = 42;

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);
}
