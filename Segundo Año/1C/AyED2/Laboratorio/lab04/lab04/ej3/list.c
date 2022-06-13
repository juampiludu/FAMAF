#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

struct s_node_t
{
    elem el;
    struct s_node_t * next;
};

list empty(void) {
    return NULL;
}

list addl(elem e, list l) {
    struct s_node_t *p;
    p = malloc(sizeof(struct s_node_t));
    p->el = e;
    p->next = l;
    return p;
}

bool is_empty(list l) {
    return (l == NULL);
}

elem head(list l) {
    assert(!is_empty(l));
    return l->el;
}

list tail(list l) {
    assert(!is_empty(l));
    return l->next;
}

list addr(list l, elem e) {
    struct s_node_t *q;
    q = malloc(sizeof(struct s_node_t));
    q->el = e;
    q->next = NULL;
    if (!is_empty(l)) {
        while (l->next != NULL) {
            l = l->next;
        }
        l->next = q;
    }
    else {
        l = q;
    }
    return l;
}

unsigned int length(list l) {
    unsigned int n = 0;
    while (l != NULL) {
        n++;
        l = l->next;
    }
    return n;
}

list concat(list l, list l0) {
    struct s_node_t *p;
    p = malloc(sizeof(struct s_node_t));
    p = l0;
    while (p != NULL) {
        l = addr(l, p->el);
        p = p->next;
    }
    return l;
}

elem index(list l, unsigned int n) {
    assert(length(l) > n);
    list p = l;
    unsigned int i = 0u;
    while (i < n) {
        p = p->next;
        i++;
    }
    return p->el;
}

list take(list l, unsigned int n) {
    unsigned int i = 0u;
    while (i < n && l != NULL) {
        l = l->next;
        i++;
    }
    l->next = NULL;
    return l;
}

list drop(list l, unsigned int n) {
    struct s_node_t *p;
    unsigned int i = 0u;
    p = malloc(sizeof(struct s_node_t));
    while (i < n && l != NULL) {
        p = l;
        l = p->next;
        free(p);
        i++;
    }
    return l;
}

list copy_list(list l1) {
    list l2 = empty();
    while (l1 != NULL) {
        l2 = addr(l2, l1->el);
    }
    return l2;
}

list destroy(list l) {
  if (l != NULL) {
    list a, b;
    a = l;
    b = a->next;
    while(a != NULL) {
      free(a);
      a = b;
      if(a != NULL) {
        b = a->next;
      }
    }
    l = a;
  }
  return l;
}