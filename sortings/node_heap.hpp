#include "sorting.h"

#ifndef NODE_HEAP_HPP
#define NODE_HEAP_HPP

#define MAX_HEAP_POWER 1000

typedef struct {
    unsigned indices[MAX_HEAP_POWER + 1];
    unsigned dictionary[MAX_HEAP_POWER + 1];
    unsigned size;
} HelperHeap;

void helper_heap_init(HelperHeap *heap) {
    for (unsigned id = 0; id < MAX_HEAP_POWER; id++) heap->indices[id] = id;
    heap->size = 0;
}

void sift_down()

#endif