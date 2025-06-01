#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int arr[], int size);
void merge_sort(int arr[], int size);
void merge_sort_helper(int arr[], int temp[], int left, int right);
void merge(int arr[], int temp[], int left, int mid, int right);

int main()
{
    int arr[] = {5, 10, 9, 11, 6, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, n);

    merge_sort(arr, n);

    print_array(arr, n);
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
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

void merge_sort_helper(int arr[], int temp[], int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort_helper(arr, temp, left, mid);
    merge_sort_helper(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

void merge(int arr[], int temp[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i = 0, j = 0, k = left;

    memcpy(temp, &arr[left], n1 * sizeof(int));
    memcpy(&temp[n1], &arr[mid + 1], n2 * sizeof(int));

    while (i < n1 && j < n2)
    {
        if (temp[i] <= temp[n1 + j])
        {
            arr[k] = temp[i];
            i ++;
        }
        else
        {
            arr[k] = temp[n1 + j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = temp[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = temp[n1 + j];
        j++;
        k++;
    }
}








