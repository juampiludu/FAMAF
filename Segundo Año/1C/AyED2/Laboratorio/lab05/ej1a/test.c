#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

void stack_dump(stack s) {
    while (!stack_is_empty(s)) {
        printf("%d -> ", s->elem);
        s = s->next;
    }
    printf("NULL\n");
}

void array_dump(stack_elem arr[], unsigned int length) {
    printf("[%d", arr[0]);
    for (unsigned int i = 1u; i < length; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n");
}

int main(void) {
    stack s = stack_empty();
    unsigned int stlen;
    stack_elem *my_arr;

    printf("\nInicializa el stack:\n");
    stlen = stack_size(s);
    my_arr = stack_to_array(s);
    stack_dump(s);
    array_dump(my_arr, stlen);

    printf("\nSe agrega un elemento al stack:\n");
    s = stack_push(s, 1);
    stlen = stack_size(s);
    my_arr = stack_to_array(s);
    stack_dump(s);
    array_dump(my_arr, stlen);

    printf("\nSe borra un elemento del stack:\n");
    s = stack_pop(s);
    stlen = stack_size(s);
    my_arr = stack_to_array(s);
    stack_dump(s);
    array_dump(my_arr, stlen);
    
    printf("\nSe agregan varios elementos al stack:\n");
    s = stack_push(s, 1);
    s = stack_push(s, 6);
    s = stack_push(s, 7);
    s = stack_push(s, 8);
    stlen = stack_size(s);
    my_arr = stack_to_array(s);
    stack_dump(s);
    array_dump(my_arr, stlen);

    s = stack_destroy(s);
}