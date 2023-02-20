#include "sorting.h"

#ifndef START_SIZE
#define START_SIZE 1000
#endif

#ifndef END_SIZE
#define END_SIZE ((size_t)1e6)
#endif

#ifndef SIZE_STEP
#define SIZE_STEP ((size_t)1e4)
#endif

#ifndef TEST_COUNT
#define TEST_COUNT 5
#endif

{

printf(AS_STR(SUBJECT) ":\t");
clock_t start_time = clock();
size_t test_counter = 0;
unsigned progress = 0;
const size_t TRUE_END = START_SIZE + (END_SIZE - START_SIZE) / SIZE_STEP * SIZE_STEP;

for (size_t array_size = START_SIZE; 
     array_size <= END_SIZE; 
     array_size += SIZE_STEP, ++TestID, test_counter++) {

    while ((array_size - START_SIZE) * PROGRESS_BAR_LENGTH / (TRUE_END - START_SIZE) >= progress) {
        ++progress; putc('#', stdout);
        fflush(stdout);
    }

    //printf("Testing size %d...\n", (int) array_size);
    unsigned long long TestTime = 0;
    for (size_t micro_id = 0; micro_id < TEST_COUNT; ++micro_id) {
        RESET_CLOCK;

        srand(0);
        for (size_t elem_id = 0; elem_id < array_size; ++elem_id) {
            Array[elem_id] = (elem_t)rand();
        }

        SUBJECT(Array, Array + array_size);
        MEASURE;

        for (size_t elem_id = 1; elem_id + 1 < array_size; ++elem_id) {
            if (Array[elem_id] >= Array[elem_id + 1]) continue;
            printf("\nIncorrect sorting result at index %ld.\n", elem_id);
            for (size_t id = elem_id >DEBUG_BATCH_SIZE ? elem_id - DEBUG_BATCH_SIZE : 0;
                 id < elem_id + DEBUG_BATCH_SIZE && id < array_size; ++id)
                printf("[%ld] = %d, ", id, Array[id]);
            putc('\n', stdout);
            return 1;
        }

        TestTime += (long long unsigned int)DELTA_TIME / TEST_COUNT;
    }

    size_t TestSize = array_size;
    WRITE_RESULT;
}

printf("  [%6lf s] [fin. at %6lf s] [%4ld tests]\n", 
    time_from(start_time), time_from(__global_time), (long int)test_counter);
}