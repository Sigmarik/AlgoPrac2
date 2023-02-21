#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <inttypes.h>

#include "config.h"

#include "quadratic_sorts.hpp"
#include "qsort.hpp"

#define _AS_STR(something) #something
#define AS_STR(something) _AS_STR(something)

#define RESET_CLOCK __start_clock = clock()
#define MEASURE __current_clock = clock()
#define DELTA_TIME (__current_clock - __start_clock)
#define WRITE_RESULT fprintf(output_tbl, "%d," AS_STR(SUBJECT) ",%ld,%ld\n", (int)TestID, (long)TestSize, (long)TestTime)

#define _CONCAT(alpha, beta) alpha ## beta
#define CONCAT(alpha, beta) _CONCAT(alpha, beta)

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

    #define END_SIZE 10000
    #define SIZE_STEP 1000
    #define SUBJECT bobble_sort
    #include "case1.hpp"
    #undef SUBJECT
    #undef SIZE_STEP
    #undef END_SIZE

    #define END_SIZE 1000000
    #define SIZE_STEP 20000
    #define SUBJECT insert_sort
    #include "case1.hpp"
    #undef SUBJECT
    #undef SIZE_STEP
    #undef END_SIZE

    #define END_SIZE 10000
    #define SIZE_STEP 1000
    #define SUBJECT choice_sort  
    #include "case1.hpp"
    #undef SUBJECT
    #undef SIZE_STEP
    #undef END_SIZE

    #define END_SIZE 1000000
    #define SIZE_STEP 20000
    #define SUBJECT qsort_3mid 
    #include "case1.hpp"
    #undef SUBJECT
    #undef SIZE_STEP
    #undef END_SIZE

    fclose(output_tbl);
    printf("Testing is over in %lf seconds. Results were stored to the file \"" OUTPUT_TABLE "\".\nHave a good day.\n",
        (double)(clock() - __global_time) / 1e6);
}