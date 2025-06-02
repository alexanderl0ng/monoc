#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void merge_sort(int arr[], int size)
{
    if (size <= 1) return;

    int *temp = malloc(size * sizeof(int));
    if (temp == NULL)
    {
        printf("[ERROR] Memory allocation failed");
        exit(1);
    }

    merge_sort_helper(arr, temp, 0, size - 1);

    free(temp);
}
