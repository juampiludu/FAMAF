#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

#include <stdio.h>

struct s_pstack {
    struct s_node ** elems;
    priority_t max_priority;
    priority_t top_priority;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    bool res = s != NULL && s->top_priority <= s->max_priority;
    return res;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->max_priority = max_priority;
    s->top_priority = 0u;
    s->size = 0u;
    s->elems = malloc(sizeof(struct s_node *) * max_priority);
    for (unsigned int i = 0u; i < max_priority; i++) {
        s->elems[i] = NULL;
    }
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e);
    if (s->elems[priority] == NULL) {
        s->elems[priority] = new_node;
    }
    else {
        struct s_node *curr = s->elems[priority];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    s->size++;
    if (priority > s->top_priority) {
        s->top_priority = priority;
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->elems[pstack_top_priority(s)]->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->top_priority;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *tmp = s->elems[pstack_top_priority(s)];
    s->elems[pstack_top_priority(s)] = s->elems[pstack_top_priority(s)]->next;
    destroy_node(tmp);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node;
    for (unsigned int i = 0u; i <= s->top_priority; i++) {
        while (s->elems[i] != NULL) {
            node = s->elems[i];
            s->elems[i] = s->elems[i]->next;
            destroy_node(node);
        }
    }
    free(s->elems);
    free(s);
    s = NULL;
    return s;
}
