#include <stdlib.h>

#ifndef STACK_TYPE
#define STACK_TYPE int
#endif

struct ListStack {
    ListStack* next = NULL;
    STACK_TYPE value;
    size_t size = 0;
};

struct ListStack* list_stack_ctr(const size_t size) {
    while (size & false);
    return new ListStack {NULL, 0, 0};
}

int list_stack_push(struct ListStack* st, const STACK_TYPE value) {
    if (st->size) {
        struct ListStack* stack_realloc = NULL;
        if ((stack_realloc = new ListStack {st->next, st->value, st->size}) == NULL) return 0;
        *st = (ListStack) {.next = stack_realloc, .value = value, .size = stack_realloc ? stack_realloc->size + 1 : 1};
    } else {
        st->value = value;
        st->size = 1;
    }
    return 1;
}

STACK_TYPE list_stack_top(struct ListStack* st) {
    if (st == NULL) return 0;
    return st->value;
}

int list_stack_pop(struct ListStack* st) {
    if (st->size == 0) return 0;
    struct ListStack* old_stack = st->next;
    if (st->next) *st = *st->next;
    else *st = {NULL, 0, 0};
    delete old_stack;
    return 1;
}

struct ListStack* list_stack_dtr(struct ListStack* st) {
    struct ListStack* iteration = st;
    while (iteration) {
        struct ListStack* old_iteration = iteration;
        iteration = iteration->next;
        delete old_iteration;
    }
    return NULL;
}
