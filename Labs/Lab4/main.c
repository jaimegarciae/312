#include <stdio.h>
#include <stdlib.h>
#ifndef DEBUG
#define DEBUG (1)
#endif

void printarray (int a [], size_t size) {
    int i = 0;

    for (i = 0; i < size; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main() {
    int size = 10;
    int count = 0;
    int current_val = 0;
    int j;

    int* in_values = (int*)malloc(size*sizeof(int));

    // while (scanf("%d", current_val) != 999) {
    while (1) {
        if (DEBUG) printf("enter a number: ");
        scanf("%d", &current_val);

        if (current_val == 999) {
            break;
        }

        if (count == size) {
            size *= 2; // amortized doubling
            in_values = (int*)realloc(in_values, size);
        }
        in_values[count] = current_val;
        count++;
    }

    int* out_values = (int*)malloc(count*sizeof(int));
    if (DEBUG) { printarray(in_values, count); }

    for (j = 0; j < count; j++) {
        out_values[j] = in_values[count - 1 - j];
    }

    printarray(out_values, count);
    free(in_values);
    free(out_values);

    return 0;
}
