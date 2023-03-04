#include "sorting.h"

#ifndef LSD_SORT_HPP
#define LSD_SORT_HPP

#include <climits>

static inline unsigned char get_char(elem_t number, unsigned char char_id) {
    return (unsigned char)(number >> (8 * char_id));
} 

static void LSD_pass(elem_t* const array, const size_t size, const unsigned char byte_id) {
    static elem_t copy_buffer[MAX_ARRAY_LENGTH];

    static size_t counts[UCHAR_MAX + 1];
    for (size_t id = 0; id < ARR_SIZE(counts); id++) counts[id] = 0;

    //*          v-- It's the final countdown! Tododo dooo, tododototooooo...
    static size_t final_counts[UCHAR_MAX + 1];
    for (size_t id = 0; id < ARR_SIZE(final_counts); id++) final_counts[id] = 0;

    memcpy(copy_buffer, array, size * sizeof(*array));

    for (size_t id = 0; id < size; id++)
        ++counts[UCHAR_MAX - get_char(copy_buffer[id], byte_id)];
    
    for (size_t id = ARR_SIZE(counts) - 1; id > 0; id--) counts[id] = counts[id - 1];
    counts[0] = 0;
    for (size_t id = 1; id < ARR_SIZE(counts); id++) counts[id] += counts[id - 1];

    for (size_t id = 0; id < size; id++) {
        unsigned char char_id = UCHAR_MAX - get_char(copy_buffer[id], byte_id);
        array[counts[char_id] + final_counts[char_id]] = copy_buffer[id];
        ++final_counts[char_id];
    }
}

SORTING(lsd_sort) {
    for (unsigned char id = 0; id < sizeof(*begin); id++) {
        LSD_pass(begin, PTR_DIFFERENCE(end, begin), id);
    }
}

#endif
