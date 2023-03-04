#include "sorting.h"

#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "string.h"

SORTING(merge_sort) {
    if (end <= begin + 1) return;

    static elem_t buffer[MAX_ARRAY_LENGTH] = {};

    elem_t* mid = begin + (end - begin) / 2;

    merge_sort(begin, mid);
    merge_sort(mid,   end);

    for (size_t id = 0; begin + id < end; ++id) {
        buffer[id] = begin[id];
    }

    elem_t* buf_end = &buffer[end - begin], *buf_mid = &buffer[mid - begin];
    elem_t* left = buffer, *right = buf_mid;

    for (elem_t* id = begin; id < end; ++id) {
        if (right < buf_end && (left >= buf_mid || *right > *left)) {
            *id = *right;
            ++right;
        } else {
            *id = *left;
            ++left;
        }
    }
}

#endif
