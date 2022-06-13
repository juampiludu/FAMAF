#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    struct s_node *node = s->first;
    bool res = true;
    if (node != NULL) {
        while (node->next != NULL && res) {
            res = (node->priority >= node->next->priority);
            node = node->next;
        }
    }
    return res;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->first = NULL;
    s->size = 0u;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *current = s->first;
    struct s_node *past = NULL;
    if (!pstack_is_empty(s)) {
        if (new_node->priority >= current->priority) {
            new_node->next = current;
            s->first = new_node;
        }
        else {
            while (current != NULL && new_node->priority < current->priority) {
                past = current;
                current = current->next;
            }
            new_node->next = current;
            past->next = new_node;
        }
    }
    else {
        s->first = new_node;
    }
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t top = s->first->priority;
    return top;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    struct s_node *node = s->first->next;
    free(s->first);
    s->first = node;
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->first;
    while (node != NULL) {
        s->first = node->next;
        destroy_node(node);
        node = s->first;
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

