#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c;
    c = malloc(sizeof(struct _counter));
    assert(counter_is_init(c));
    return c;
}

void counter_inc(counter c) {
    c->count = c->count + 1;
}

bool counter_is_init(counter c) {
    return c->count == 0;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count = c->count - 1;
}

counter counter_copy(counter c) {
    counter c1;
    c1 = malloc(sizeof(struct _counter));
    c1->count = c->count;
    return c1;
}

void counter_destroy(counter c) {
    free(c);
}
