//
// Created by Vallath Nandakumar on 3/16/17.
//

#include "sort_functions.h"
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* a, int size) {
    // 312 STUDENTS COMPLETE THIS METHOD
    for(int i = 1; i < size; i++){
        int j = i;
        while(j > 0 && a[j-1] > a[j]){
            int temp = a[j];
            a[j] = a[j-1];
            a[j-1] = temp;
            j--;
        }
    }
}

void fun(int *a, int i3, int i1, int i2, int* food) {
    int i = i3; int j = i1;
    for (int k = i3; k < i2; k++) {
        if (i < i1 && (j >= i2 ||  a[i] < a[j])) {
            food[k] = a[i];
            i++;
        }
        else {
            food[k] = a[j];
            j++;
        }
    }
}

void fun3(int *src, int i1, int i2, int *pInt) {
    for (int i = i1; i < i2; i++) {
        pInt[i] = src[i];
    }
}

void fun2(int *a, int i3, int i2, int *pInt) {
    if (i2 - i3 < 2) {
        return;
    }
    int i21 = (i3 + i2) / 2;
    fun2(a, i3, i21, pInt);
    fun2(a, i21, i2, pInt);
    fun(a, i3, i21, i2, pInt);
    fun3(pInt, i3, i2, a);
}

void fun1(int *a, int size) {
    int* food = (int*)calloc(size, sizeof(int));
    fun2(a, 0, size, food);
    free(food);
    food = 0;
}
