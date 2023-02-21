#include "sorting.h"

#ifndef QSORT_HPP
#define QSORT_HPP

#include "quadratic_sorts.hpp"

static const size_t CANDIDATE_COUNT = 3;

elem_t mid3(elem_t* begin, elem_t* end) {
    elem_t candidates[CANDIDATE_COUNT];

    for (size_t id = 0; id < CANDIDATE_COUNT; ++id)
        candidates[id] = *begin;

    for (size_t cand_id = 0; cand_id < CANDIDATE_COUNT && begin + cand_id < end; ++cand_id)
        candidates[cand_id] = begin[cand_id];

    insert_sort(candidates, candidates + CANDIDATE_COUNT);

    return candidates[CANDIDATE_COUNT >> 1];
}

typedef elem_t pivot_fn_t(elem_t* begin, elem_t* end);

void quick_sort(elem_t* begin, elem_t* end, pivot_fn_t* pivot_fn) {
    if (end <= begin + 1) return;

    elem_t pivot = pivot_fn(begin, end);

    elem_t* left = begin, *right = end - 1;

    while (left < right) {
        if (*left <= pivot && *right >= pivot) swap(left, right);
        if (*left >= pivot) ++left;
        if (*right <= pivot && left < right) --right;
    }

    elem_t* split = right;
    while (*split > pivot && split < end) ++split;

    quick_sort(begin, split, pivot_fn);
    quick_sort(split, end,   pivot_fn);
}

SORTING(qsort_3mid) { quick_sort(begin, end, mid3); }

#endif
