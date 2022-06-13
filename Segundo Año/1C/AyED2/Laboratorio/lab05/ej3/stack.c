#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;
};

stack stack_empty() {
    return NULL;
}

struct _s_stack *new_node(stack_elem n) {
    struct _s_stack *node = malloc(sizeof(struct _s_stack));
    node->elem = n;
    node->next = NULL;
    return node;
}

stack stack_push(stack s, stack_elem e) {
    struct _s_stack *node = new_node(e);
    node->next = s;
    node->size = s == NULL ? 0 : node->size+1;
    return node;
}

stack stack_pop(stack s) {
    struct _s_stack *tmp = s;
    s = s->next;
    free(tmp);
    return s;
}

bool stack_is_empty(stack s) {
    return s == NULL;
}

// unsigned int stack_size(stack s) {
//     return s->size+1;
// }
unsigned int stack_size(stack s) {
    unsigned int size = 0u;
    while (!stack_is_empty(s)) {
        s = s->next;
        size++;
    }
    return size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elem;
}

stack_elem *stack_to_array(stack s) {
    unsigned int length = stack_size(s);
    stack_elem *arr = malloc(sizeof(stack_elem) * length);
    unsigned int i = length - 1;
    while (!stack_is_empty(s)) {
        arr[i] = s->elem;
        s = s->next;
        i--;
    }
    return arr;
}

stack stack_destroy(stack s) {
    while (!stack_is_empty(s)) {
        s = stack_pop(s);
    }
    return s;
}