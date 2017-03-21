#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "sort_functions.h"

void print_array(int* a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
}

void initialize_array_reverse(int* a, int size) {
    for (int i = size-1; i >= 0 ; i--) {
        a[i] = size - i - 1;
    }
}

void check_sorted(int* a, int size) {
    int is_sorted = 1;
    while (size-1) {
        assert(a[size-1] >= a[size-2]) ;
        size--;

    }
}
void initialize_array_sorted(int* a, int size) {
    for (int i = size-1; i >= 0 ; i--) {
        a[i] = i;
    }
}


int main() {

    int* a;
    int size;
    size = 10;
    clock_t ct1, ct2; // to hold the current clock time
    double duration;

    {
        int arr[] = {3, 4, 5};
        check_sorted(arr, 3);
    }

    {
        size = 10000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size); // initialize a reverse-sorted array
        ct1 = clock();
        insertion_sort(a, size); // your insertion sort is being called. You have to write insertion_sort.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 20000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size); // initialize a reverse-sorted array
        ct1 = clock();
        insertion_sort(a, size); // your insertion sort is being called. You have to write insertion_sort.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 30000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size); // initialize a reverse-sorted array
        ct1 = clock();
        insertion_sort(a, size); // your insertion sort is being called. You have to write insertion_sort.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 40000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size); // initialize a reverse-sorted array
        ct1 = clock();
        insertion_sort(a, size); // your insertion sort is being called. You have to write insertion_sort.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 10000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size);
        ct1 = clock();
        fun1(a, size); // the mystery sort function fun1 is being called here. fun1 is completed for you.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 20000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size);
        ct1 = clock();
        fun1(a, size); // the mystery sort function fun1 is being called here. fun1 is completed for you.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 30000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size);
        ct1 = clock();
        fun1(a, size); // the mystery sort function fun1 is being called here. fun1 is completed for you.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    {
        size = 40000;
        a = malloc(size * sizeof(int));
        initialize_array_reverse(a, size);
        ct1 = clock();
        fun1(a, size); // the mystery sort function fun1 is being called here. fun1 is completed for you.
        ct2 = clock();
        check_sorted(a, size);
        free(a);
        duration = ((double) (ct2 - ct1)) / CLOCKS_PER_SEC;
        printf("%g\n", duration);
    }

    return 0;
}