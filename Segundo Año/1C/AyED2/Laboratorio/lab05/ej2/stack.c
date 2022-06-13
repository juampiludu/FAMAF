#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"


struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s) {
    bool res = s != NULL && s->size <= s->capacity;
    return res;
}

stack stack_empty() {
    stack s = (stack)malloc(sizeof(struct _s_stack));
    s->elems = NULL;
    s->size = 0;
    s->capacity = 0;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if (s->capacity == s->size) {
        unsigned int new_capacity = s->capacity == 0 ? 1 : 2 * s->capacity;
        s->elems = realloc(s->elems, sizeof(stack_elem)*new_capacity);
        s->capacity = new_capacity;
    }
    (s->elems)[s->size] = e;
    (s->size)++;
    assert(invrep(s));
    return s;
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->size == 0;
}

stack stack_pop(stack s) {
    assert(invrep(s));
    assert(!stack_is_empty(s));
    (s->size)--;
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(invrep(s));
    return (s->elems)[s->size-1];
}

stack_elem *stack_to_array(stack s) {
    assert(invrep(s));
    assert(!stack_is_empty(s));
    stack_elem tmp;
    unsigned int j = s->size-1;
    for (unsigned int i = 0u; i < j-i; i++) {
        tmp = (s->elems)[i];
        (s->elems)[i] = (s->elems)[j-i];
        (s->elems)[j-i] = tmp;
    }
    assert(invrep(s));
    return s->elems;
}

stack stack_destroy(stack s) {
    assert(invrep(s));
    free(s->elems);
    free(s);
    return s;
}