#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parallel_merge.h"
#include "merge.h"
#include "utils.h"

#define ARRAY_SIZE 600000
#define MIN_VAL 1
#define MAX_VAL 10000

int main()
{
    int* test_array = create_random_array(ARRAY_SIZE, MIN_VAL, MAX_VAL);
    int* test_array_copy = copy_array(test_array, ARRAY_SIZE);

    printf("Sorting using the sequential function...\n");
    clock_t start_merge;
    start_timer(&start_merge);

    merge_sort(test_array, ARRAY_SIZE);

    double elapsed_merge = end_timer(start_merge);
    printf("Time to sort using the sequential function: %.4f seconds\n", elapsed_merge);
    free(test_array);

    printf("\nSorting using the threaded function...\n");
    clock_t start_threaded_merge;
    start_timer(&start_threaded_merge);

    threaded_merge_sort(test_array_copy, ARRAY_SIZE);

    double elapsed_threaded_merge = end_timer(start_threaded_merge);
    printf("Time to sort using the threaded function: %.4f seconds\n", elapsed_threaded_merge);
    free(test_array_copy);

    return 0;
}

