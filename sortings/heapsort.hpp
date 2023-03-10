#include "sorting.h"

#ifdef HEAP_OPTIMIZATION
    #define OPTI_FLAG opt
    #define ON_OPTI(...) __VA_ARGS__
    #define ON_DFLT(...)
#else
    #define OPTI_FLAG
    #define ON_OPTI(...)
    #define ON_DFLT(...) __VA_ARGS__
#endif

#define __HEAP_NAME(suffix)         _heap        ## suffix
#define __HEAP_SIFT_UP(suffix)      _sift_up     ## suffix
#define __HEAP_SIFT_DOWN(suffix)    _sift_down   ## suffix
#define __HEAP_PUSH(suffix)         _heap_push   ## suffix
#define __HEAP_POP(suffix)          _heap_pop    ## suffix
#define __HEAP_SORT(suffix)         heap_sort    ## suffix
#define __SUBHEAP_DOWN(suffix)      subheap_down ## suffix
#define __SUBHEAP_UP(suffix)        subheap_up   ## suffix

#define _HEAP_NAME(suffix)         __HEAP_NAME(suffix)
#define _HEAP_SIFT_UP(suffix)      __HEAP_SIFT_UP(suffix)
#define _HEAP_SIFT_DOWN(suffix)    __HEAP_SIFT_DOWN(suffix)
#define _HEAP_PUSH(suffix)         __HEAP_PUSH(suffix)
#define _HEAP_POP(suffix)          __HEAP_POP(suffix)
#define _HEAP_SORT(suffix)         __HEAP_SORT(suffix)
#define _SUBHEAP_DOWN(suffix)      __SUBHEAP_DOWN(suffix)
#define _SUBHEAP_UP(suffix)        __SUBHEAP_UP(suffix)

#define HEAP_NAME       _HEAP_NAME(CONCAT(HEAP_POWER, OPTI_FLAG))
#define HEAP_SIFT_UP    _HEAP_SIFT_UP(CONCAT(HEAP_POWER, OPTI_FLAG))
#define HEAP_SIFT_DOWN  _HEAP_SIFT_DOWN(CONCAT(HEAP_POWER, OPTI_FLAG))
#define HEAP_PUSH       _HEAP_PUSH(CONCAT(HEAP_POWER, OPTI_FLAG))
#define HEAP_POP        _HEAP_POP(CONCAT(HEAP_POWER, OPTI_FLAG))
#define HEAP_SORT       _HEAP_SORT(CONCAT(HEAP_POWER, OPTI_FLAG))
#define SUBHEAP_DOWN    _SUBHEAP_DOWN(CONCAT(HEAP_POWER, OPTI_FLAG))
#define SUBHEAP_UP      _SUBHEAP_UP(CONCAT(HEAP_POWER, OPTI_FLAG))

#ifndef HEAPSORT_HPP  // One-time initialization
    #define HEAPSORT_HPP
    typedef struct {unsigned value; unsigned index;} subheap_node_t;

    void swap_sh_nodes(subheap_node_t *alpha, subheap_node_t *beta, unsigned* dictionary) {
        subheap_node_t temp = *alpha;
        *beta = *alpha;
        *alpha = temp;

        unsigned temp_index = dictionary[alpha->index];
        dictionary[alpha->index] = dictionary[beta->index];
        dictionary[beta->index] = temp_index;
    }
#endif

typedef struct {
    elem_t buffer[MAX_ARRAY_LENGTH];
    size_t size;

    ON_OPTI(
        subheap_node_t subheap_indices[MAX_ARRAY_LENGTH];
        unsigned subheap_dicts[MAX_ARRAY_LENGTH];
    )
} HEAP_NAME;

ON_OPTI(
    void SUBHEAP_UP(HEAP_NAME* heap, size_t id) {
        size_t local_id = id % HEAP_POWER;
        size_t core_id = id - local_id;
        while (local_id > 0 && heap->buffer[heap->subheap_indices[core_id + (local_id - 1) / 2].value] < 
                               heap->buffer[heap->subheap_indices[core_id + local_id].value]) {
            swap_sh_nodes(&heap->subheap_indices[core_id + (local_id - 1) / 2],
                &heap->subheap_indices[core_id + local_id], heap->subheap_dicts + core_id);
            local_id /= 2;
        }
    }

    void SUBHEAP_DOWN(HEAP_NAME* heap, size_t id) {
        unsigned local_id = (unsigned)(id % HEAP_POWER);
        size_t core_id = id - local_id;
        while (heap->buffer[heap->subheap_indices[core_id + local_id * 2 + 1].value] >
               heap->buffer[heap->subheap_indices[core_id + local_id].value] ||
               heap->buffer[heap->subheap_indices[core_id + local_id * 2 + 2].value] >
               heap->buffer[heap->subheap_indices[core_id + local_id].value]) {
            unsigned swap_index = heap->buffer[heap->subheap_indices[core_id + local_id * 2 + 2].value] >
                                  heap->buffer[heap->subheap_indices[core_id + local_id * 2 + 1].value] ?
                                  local_id * 2 + 2 : local_id * 2 + 1;
            swap_sh_nodes(&heap->subheap_indices[core_id + local_id],
                &heap->subheap_indices[core_id + swap_index], heap->subheap_dicts + core_id);
            local_id = swap_index;
        }
    }
)

void HEAP_SIFT_UP(HEAP_NAME* heap, size_t id) {
    while (id > HEAP_POWER && heap->buffer[id / HEAP_POWER] < heap->buffer[id]) {
        swap(&heap->buffer[id], &heap->buffer[id / HEAP_POWER]);
        
        ON_OPTI(
            SUBHEAP_UP(heap, id / HEAP_POWER);
            SUBHEAP_DOWN(heap, id);
        )

        id /= HEAP_POWER;
    }
}

void HEAP_SIFT_DOWN(HEAP_NAME* heap, size_t id) {
    while (id <= heap->size) {
        size_t max_id = id;

        ON_OPTI(
            if (id < heap->size) {
                max_id = id + heap->subheap_indices[id + 1].index;
            }
        )
        ON_DFLT(
            for (size_t cur_id = id * HEAP_POWER; cur_id < (id + 1) * HEAP_POWER; ++cur_id) {
                if (heap->size >= cur_id && heap->buffer[cur_id] > heap->buffer[max_id]) max_id = cur_id;
            }
        )

        if (max_id == id) break;
        swap(&heap->buffer[id], &heap->buffer[max_id]);

        ON_OPTI(
            SUBHEAP_UP(heap, id);
            SUBHEAP_DOWN(heap, max_id);
        )

        id = max_id;
    }
}

void HEAP_PUSH(HEAP_NAME* heap, elem_t value) {
    heap->buffer[++heap->size] = value;
    HEAP_SIFT_UP(heap, heap->size);
    ON_OPTI(
        heap->subheap_dicts[heap->size] = (unsigned)(heap->size % HEAP_POWER);
        heap->subheap_indices[heap->size] = (subheap_node_t){.value = value, .index = (unsigned)(heap->size % HEAP_POWER)};
    )
}

elem_t HEAP_POP(HEAP_NAME* heap) {
    if (heap->size == 0) return POISON;

    size_t pop_index = 1;
    for (size_t cur_id = 1; cur_id < HEAP_POWER && cur_id <= heap->size; ++cur_id) {
        if (heap->buffer[cur_id] > heap->buffer[pop_index]) pop_index = cur_id;
    }

    elem_t value = heap->buffer[pop_index];

    if (heap->size > 0) HEAP_SIFT_DOWN(heap, pop_index);

    return value;
}

SORTING(HEAP_SORT) {
    static HEAP_NAME heap = (HEAP_NAME) {.buffer = {}, .size = 0};

    heap.size = 0;
    
    for (elem_t* id = begin; id < end; ++id) {
        HEAP_PUSH(&heap, *id);
    }

    for (elem_t* id = begin; id < end; ++id) {
        *id = HEAP_POP(&heap);
    }
}

#undef HEAP_NAME
#undef HEAP_SIFT_UP
#undef HEAP_SIFT_DOWN
#undef HEAP_PUSH
#undef HEAP_POP
#undef HEAP_SORT
#undef SUBHEAP_DOWN
#undef SUBHEAP_UP

#undef _HEAP_NAME
#undef _HEAP_SIFT_UP
#undef _HEAP_SIFT_DOWN
#undef _HEAP_PUSH
#undef _HEAP_POP
#undef _HEAP_SORT
#undef _SUBHEAP_DOWN
#undef _SUBHEAP_UP

#undef __HEAP_NAME
#undef __HEAP_SIFT_UP
#undef __HEAP_SIFT_DOWN
#undef __HEAP_PUSH
#undef __HEAP_POP
#undef __HEAP_SORT
#undef __SUBHEAP_DOWN
#undef __SUBHEAP_UP

#undef OPTI_FLAG
#undef ON_OPTI
#undef ON_DFLT
