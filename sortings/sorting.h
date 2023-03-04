#include <stdlib.h>
#include <inttypes.h>

#ifndef SORTING_H
#define SORTING_H

typedef u_int32_t elem_t;

#define ARR_SIZE(array) (sizeof(array) / sizeof(*array))
#define PTR_DIFFERENCE(ptr_a, ptr_b) (((uintptr_t)(ptr_a) - (uintptr_t)(ptr_b)) / sizeof(*ptr_a))

#define SORTING(name) void name(elem_t* begin, elem_t* end)

#define min(alpha, beta) ((alpha) < (beta) ? (alpha) : (beta))
#define max(alpha, beta) ((alpha) > (beta) ? (alpha) : (beta))

static inline void swap(elem_t* alpha, elem_t* beta) {
    elem_t buffer = *alpha;
    *alpha = *beta;
    *beta = buffer;
}

#endif
