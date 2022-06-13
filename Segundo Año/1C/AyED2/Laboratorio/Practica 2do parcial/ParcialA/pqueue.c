#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
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


static bool invrep(pqueue q) {
    struct s_node *node = q->first;
    bool res = true;
    if (!pqueue_is_empty(q)) {
        while (node->next != NULL && res) {
            res = (node->priority >= node->next->priority);
            node = node->next;
        }
    }
    return res;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->size = 0u;
    assert(q != NULL && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *current = q->first;
    struct s_node *past = NULL;
    if (pqueue_is_empty(q)) {
        q->first = new_node;
    }
    else {
        if (new_node->priority >= current->priority) {
            new_node->next = current;
            q->first = new_node;
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
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *node = q->first;
    q->first = q->first->next;
    node = destroy_node(node);    
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node = q->first;
    while (node != NULL) {
        struct s_node *destroy = node;
        node = node->next;
        destroy = destroy_node(destroy);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
