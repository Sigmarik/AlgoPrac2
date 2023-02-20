#include <stdlib.h>
#include <inttypes.h>

#ifndef SORTING_H
#define SORTING_H

typedef u_int32_t elem_t;

#define SORTING(name) void name(elem_t* begin, elem_t* end)

static inline void swap(elem_t* alpha, elem_t* beta) {
    register elem_t buffer = *alpha;
    *beta = *alpha;
    *alpha = buffer;
}

#endif