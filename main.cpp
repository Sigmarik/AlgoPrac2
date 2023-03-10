#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <inttypes.h>

#include "config.h"

// TODO: Separate compilation would be better in this case... 
// TODO: But who needs better compilation techniques, project structure or good code practices?
#include "quadratic_sorts.hpp"
#include "qsort.hpp"
#include "mergesort.hpp"
#include "LSD.hpp"

#define _AS_STR(something) #something
#define AS_STR(something) _AS_STR(something)

#define RESET_CLOCK __start_clock = clock()
#define MEASURE __current_clock = clock()
#define DELTA_TIME (__current_clock - __start_clock)
#define WRITE_RESULT fprintf(output_tbl, "%d," AS_STR(SUBJECT) ",%ld,%ld\n", (int)TestID, (long)TestSize, (long)TestTime)

#define EMPTY

#define _CONCAT(alpha, beta) alpha ## beta
#define CONCAT(alpha, beta) _CONCAT(alpha, beta)

#define CONCAT_MACRO_STRING(macro, string) _CONCAT(macro, EMPTY) ## string
#define CONCAT_STRING_MACRO(string, macro) string ## _CONCAT(macro, EMPTY)

#include "heap_org/heaps.hpp"

#define RECREATE do {                   \
    array_stack_dtr(array_stack);       \
    list_stack_dtr(list_stack);         \
    list_stack   = list_stack_ctr(1);   \
    array_stack = array_stack_ctr(1);   \
} while (0)

static inline double time_from(clock_t time) { return (double)(clock() - time) / 1e6; }

int main() {
    clock_t __start_clock   = 0;
    clock_t __current_clock = 0;

    clock_t __global_time = clock();
    
    // These variables are somewhat global for test cases.
    static elem_t Array[MAX_ARRAY_LENGTH] = {};
    size_t TestID = 0;

    FILE* output_tbl = fopen(OUTPUT_TABLE, "w");
    assert(output_tbl);

    printf("Testing has started.\n");

    fprintf(output_tbl, "TestID,Subject,Size,Time\n");

    #ifdef _DEBUG
        #define END_SIZE 3000
        #define SIZE_STEP 200
    #else
        #define END_SIZE 30000
        #define SIZE_STEP 2000
    #endif

        #define SUBJECT bobble_sort
        #include "case1.hpp"
        #undef SUBJECT

    #undef SIZE_STEP
    #undef END_SIZE

    #ifdef _DEBUG
        #define END_SIZE 3000
        #define SIZE_STEP 200
    #else
        #define END_SIZE 100000
        #define SIZE_STEP 2000
    #endif

        #define SUBJECT choice_sort  
        #include "case1.hpp"
        #undef SUBJECT

        #define SUBJECT insert_sort
        #include "case1.hpp"
        #undef SUBJECT

    #undef SIZE_STEP
    #undef END_SIZE


    #ifdef _DEBUG
        #define END_SIZE 100000
        #define SIZE_STEP 10000
    #else
        #define END_SIZE 10000000
        #define SIZE_STEP 100000
    #endif

        #define SUBJECT qsort_3mid 
        #include "case1.hpp"
        #undef SUBJECT

        #define SUBJECT qsort_rand
        #include "case1.hpp"
        #undef SUBJECT

        #define SUBJECT qsort_mmid
        #include "case1.hpp"
        #undef SUBJECT

        #define SUBJECT merge_sort
        #include "case1.hpp"
        #undef SUBJECT

        #define SUBJECT lsd_sort
        #include "case1.hpp"
        #undef SUBJECT

        #include "heap_org/heap_calls_basic.hpp"
        // #include "heap_org/heap_calls_opti.hpp"

    #undef SIZE_STEP
    #undef END_SIZE

    fclose(output_tbl);
    printf("Testing is over in %lf seconds. Results were stored to the file \"" OUTPUT_TABLE "\".\nHave a good day.\n",
        (double)(clock() - __global_time) / 1e6);
}