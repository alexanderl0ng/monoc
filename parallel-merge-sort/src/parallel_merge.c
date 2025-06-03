#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_DEPTH 2
#define THRESHOLD 2048

typedef struct {
    int *arr;
    int *temp;
    int left;
    int right;
    int depth;
} thread_data;

static void merge(int arr[], int temp[], int left, int mid, int right)
{
    memcpy(&temp[left], &arr[left], (right - left + 1) * sizeof(int));

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (temp[i] <= temp[j])
        {
            arr[k++] = temp[i++];
        }
        else
        {
            arr[k++] = temp[j++];
        }
    }

    while (i <= mid)
    {
        arr[k++] = temp[i++];
    }
    while (j <= right)
    {
        arr[k++] = temp[j++];
    }
}

static void merge_sort_helper(int arr[], int temp[], int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort_helper(arr, temp, left, mid);
    merge_sort_helper(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

static void* parallel_merge_sort_helper(void* arg)
{
    thread_data* data = (thread_data*)arg;

    if (data->left >= data->right) return NULL;

    if (data->right - data->left <= THRESHOLD || data->depth <= 0)
    {
        merge_sort_helper(data->arr, data->temp, data->left, data->right);
        return NULL;
    }

    int mid = data->left + (data->right - data->left) / 2;

    pthread_t left_thread, right_thread;
    thread_data left_data = {data->arr, data->temp, data->left, mid, data->depth - 1};
    thread_data right_data = {data->arr, data->temp, mid + 1, data->right, data->depth - 1};

    pthread_create( &left_thread, NULL, parallel_merge_sort_helper, &left_data);
    pthread_create( &right_thread, NULL, parallel_merge_sort_helper, &right_data);

    pthread_join(left_thread, NULL);
    pthread_join(right_thread, NULL);

    merge(data->arr, data->temp, data->left, mid, data->right);
    return NULL;
}

void threaded_merge_sort(int arr[], int size)
{
    if (size <= 1) return;

    int *temp = malloc(size * sizeof(int));
    if (temp == NULL)
    {
        printf("[ERROR] Memory allocation failed");
        exit(1);
    }

    thread_data data = {arr, temp, 0, size - 1, MAX_DEPTH};
    parallel_merge_sort_helper( &data);

    free(temp);
}

