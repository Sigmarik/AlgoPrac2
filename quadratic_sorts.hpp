#include "sorting.h"

#ifndef QUADRATIC_SORT_HPP
#define QUADRATIC_SORT_HPP

SORTING(bobble_sort) {
    while (end > begin) {
        for (elem_t* current = begin; current + 1 < end; ++current) {
            if (*current < *(current + 1)) {
                swap(current, current + 1);
            }
        }
        --end;
    }
}

SORTING(insert_sort) {
    for (elem_t* pointer = begin; pointer < end; ++pointer) {
        elem_t* current = pointer;
        while (current > begin && *(current - 1) < *current) {
            swap(current, current - 1);
            --current;
        }
    }
}

SORTING(choice_sort) {
    for (elem_t* pointer = begin; pointer < end; ++pointer) {
        elem_t* max_id = pointer;
        for (elem_t* current = pointer; current < end; ++current)
            max_id = (*current > *max_id) ? current : max_id;
        swap(max_id, pointer);
    }
}

#endif
