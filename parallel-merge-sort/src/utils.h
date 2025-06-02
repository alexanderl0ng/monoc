#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void print_int_array(int arr[], int size);
void start_timer(clock_t *start_time);
double end_timer(clock_t start_time);
int* create_random_array(int size, int min_val, int max_val);
int* copy_array(const int* original, int size);

#endif
