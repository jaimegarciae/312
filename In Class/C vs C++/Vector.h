#include <stdint.h>

typedef struct vector {
	int32_t *data;
	uint32_t len;
	uint32_t cap;
} Vector;

Vector create(uint32_t init_size_of_vector);
void destroy(Vector);
uint32_t get(Vector, uint32_t index);
void set(Vector, uint32_t index, uint32_t value);
uint32_t size(Vector);
void pop_back(Vector*);
void push_bach(Vector*, int32_t value);
void printVector(Vector);