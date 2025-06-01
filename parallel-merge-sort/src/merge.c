#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[], int size);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main()
{
    int arr[] = {5, 10, 9, 11, 6, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, n);

    merge_sort(arr, 0, n - 1);

    print_array(arr, n);
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge_sort(int arr[], int left, int right)
{
    if (left >= right) return;

    int mid = (left + right) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}








