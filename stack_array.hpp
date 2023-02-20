#include <stdlib.h>

#ifndef STACK_TYPE
#define STACK_TYPE int
#endif

struct ArrayStack {
    STACK_TYPE* buffer = NULL;
    size_t size = 0;
    size_t capacity = 0;
};

struct ArrayStack* array_stack_ctr(const size_t size) {
    return new ArrayStack {
        .buffer = (STACK_TYPE*)calloc(size, sizeof(STACK_TYPE)),
        .size = 0,
        .capacity = size,
    };
}

int array_stack_push(struct ArrayStack* st, const STACK_TYPE value) {
    if (st->capacity < st->size + 1) {
        st->capacity *= 2;
        STACK_TYPE* new_buffer = (STACK_TYPE*)calloc(st->capacity, sizeof(STACK_TYPE));
        if (!new_buffer) {
            st->capacity /= 2;
            return 0;
        }
        memcpy(new_buffer, st->buffer, st->size);
        free(st->buffer);
        st->buffer = new_buffer;
    }
    st->buffer[st->size++] = value;
    return 1;
}

STACK_TYPE array_stack_top(struct ArrayStack* st) {
    if (st->size == 0) return 0;
    return st->buffer[st->size - 1];
}

int array_stack_pop(struct ArrayStack* st) {
    if (st->size == 0) return 0;
    --st->size;
    return 1;
}

struct ArrayStack* array_stack_dtr(struct ArrayStack* st) {
    free(st->buffer);
    st->buffer = NULL;
    st->size = 0;
    st->capacity = 0;
    delete st;
    return NULL;
}
