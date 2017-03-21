#include "Vector.h"
#include <stdint.h>
#include <stdio.h>

#define MIN 8
Vector create (uint32_t size){
	Vector v;
	//no elements initially
	v.len = 0;
	v.cap = size;
	if(v.cap < MIN){
		v.cap = MIN;
	}
	v.data = (int32_t *) malloc(v.cap * sizeof(int32_t));
	return v;
}

void destroy(Vector v){
	free(v.data);
}

void checkBounds(Vector v, uint32_t index){
	if(index < 0 || index >= v.len){
		abort();
	}
}
uint32_t get(Vector v, uint32_t index){
	//TODO: check if index is in bounds
	return v.data[index];
}

void set(Vector v, uint32_t index, uint32_t value){
	//TODO: check if index is in bounds
	v.data[index] = value;
}

uint32_t size(Vector v){
	return v.len;
}

void pop_back(Vector *v){
	//TODO: check if len is already 0
	v->len--;
}

void push_bach(Vector* v, int32_t value){
	if(v->len == v->cap){
		int32_t *new_data = (int32_t *) malloc(v->cap * 2 * sizeof(int32_t));
		for(int i = 0; i < v->len; i++){
			new_data[i] = v->data[i];
		}
		free(v->data);
		v->data = new_data;
		v->cap = v->cap * 2;
	}
	v->data[v->len] = value;
	v->len++;
}

void printVector(Vector v){
	for(int i = 0; i < v.len; i++){
		printf("%d, ",v.data[i]);
	}
	printf("\n");
}