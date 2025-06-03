#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void print_int_array(int arr[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void start_timer(clock_t *start_time)
{
    *start_time = clock();
}

static double get_time_diff(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double end_timer(clock_t start_time)
{
    clock_t end_time = clock();
    return get_time_diff(start_time, end_time);
}

static void fill_random_array(int arr[], int size, int min_val, int max_val)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand(time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < size; i++)
    {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
}

int* create_random_array(int size, int min_val, int max_val)
{
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("[ERROR] Memory allocation failed");
        exit(1);
    }

    fill_random_array(arr, size, min_val, max_val);
    return arr;
}

int* copy_array(const int* original, int size)
{
    int* copy = (int*)malloc(size * sizeof(int));
    if (copy == NULL)
    {
        printf("[ERROR] Memory allocation failed");
        exit(1);
    }
    memcpy(copy, original, size * sizeof(int));
    return copy;
}

int is_sorted(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}

