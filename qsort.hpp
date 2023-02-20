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

typedef elem_t midchoice_fn_t(elem_t* begin, elem_t* end);

void qsort(elem_t* begin, elem_t* end, midchoice_fn_t* choice_fn) {
    // TODO: Ended work here. Need to write QSORT core and differend pivot element choice functions.
}

SORTING(qsort_3mid) { qsort(begin, end, mid3); }

#endif
