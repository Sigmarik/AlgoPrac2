#include "sorting.h"

#ifndef QSORT_HPP
#define QSORT_HPP

#include "quadratic_sorts.hpp"

#define PIVOT_FUNCTION(name) elem_t name(elem_t* begin, elem_t* end)

typedef PIVOT_FUNCTION(pivot_fn_t);

static const size_t CANDIDATE_COUNT = 3;

PIVOT_FUNCTION(mid3) {
    elem_t candidates[CANDIDATE_COUNT];

    for (size_t id = 0; id < CANDIDATE_COUNT; ++id)
        candidates[id] = *begin;

    for (size_t cand_id = 0; cand_id < CANDIDATE_COUNT && begin + cand_id < end; ++cand_id)
        candidates[cand_id] = begin[cand_id];

    insert_sort(candidates, candidates + CANDIDATE_COUNT);

    return candidates[CANDIDATE_COUNT >> 1];
}

PIVOT_FUNCTION(random_pivot) {
    return begin[rand() % (end - begin)];
}

static const size_t BATCH_SIZE = 5;

PIVOT_FUNCTION(mid_mid) {
    while (end > begin) {
        size_t batch_id = 0;

        for (batch_id = 0; begin + batch_id * BATCH_SIZE < end; batch_id++) {
            elem_t* batch_begin = begin + batch_id * BATCH_SIZE;
            elem_t* batch_end = min(batch_begin + BATCH_SIZE, end);

            insert_sort(batch_begin, batch_end);

            swap(begin + batch_id, batch_begin + (batch_end - batch_begin) / 2);
        }

        if (batch_id <= 1) {
            return *begin;
        }

        end = begin + batch_id; // batch_id is more like a batch_count here.
    }

    return *begin;
}

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
SORTING(qsort_rand) { quick_sort(begin, end, random_pivot); }
SORTING(qsort_mmid) { quick_sort(begin, end, mid_mid); }

#endif
