/*
 * Set ADT
 * Project5.c 
 *
 * Jaime Eugenio Garcia
 * jeg3954
 * My Section Time
 * Spring 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */

/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
	int low_bound = 0;
	int high_bound = (self->len) - 1;
	int middle;
	while(low_bound <= high_bound){
		middle = (low_bound + high_bound)/2;
		if(self->elements[middle] == x){
			return true;
		} else if(self->elements[middle] < x){
			low_bound = middle + 1;
		} else if(self->elements[middle] > x){
			high_bound = middle - 1;
		}
	}
	return false;
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {	
	if(!isMemberSet(self, x)){
		if(self->len == 0){
			createSingletonSet(self, x);
		} else{
			self->len += 1;
			self->elements = (int *) realloc(self->elements, (self->len)*(sizeof(int)));
			int i = (self->len) - 1;
			while(i > 0){
				if((self->elements[i-1]) > x){
					self->elements[i] = self->elements[i-1];
				} else{
					self->elements[i] = x;
					break;
				}
				i--;
                if(i == 0){
                    self->elements[i] = x;
                }
			}
		}
	}
	return;
}

void shiftDown(Set* self, int index){
	//for(int i = 0; i < (self->len -1); i++){
	for(int i = index; i < (self->len -1); i++){
		self->elements[i] = self->elements[i+1];
	}
	self->len -= 1;
}

/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
	int low_bound = 0;
	int high_bound = (self->len) - 1;
	int middle;
	while(low_bound <= high_bound){
		middle = (low_bound + high_bound)/2;
		if(self->elements[middle] == x){
			shiftDown(self, middle);
			break;
		} else if(self->elements[middle] < x){
			low_bound = middle + 1;
		} else if(self->elements[middle] > x){
			high_bound = middle - 1;
		}
	}
	return;
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

bool compareSets(const Set* self, const Set* other){
	for(int i = 0; i < self->len; i++){
		if((self->elements[i]) != (other->elements[i])){
			return false;
		}
	}
	return true;
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if(self->len == other->len && self->len == 0 ) {
        return true;
    }else if(self->len == other->len){
		return compareSets(self, other);
	} else{
		return false;
	}
}

bool elementOf(const Set* self, const Set* other){
	int i = 0, j = 0;
	while(i < self->len){
		if(j == other->len){
			return false;
		} else if(self->elements[i] < other->elements[j]){
			return false;
		} else if(self->elements[i] == other->elements[j]){
			i++;
			j++;
		} else{
			j++;
		}
	}
	return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	if(self->len == 0){
		return true;
	}else if(self->len <= other->len){
		return elementOf(self, other);
	} else{
		return false;
	}
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

int copyRepeated(Set* self, const Set* other, int* temp){
	int i = 0, j = 0, k = 0;
	while(i < (self->len) && j < (other->len)){
		if(self->elements[i] == other->elements[j]){
			temp[k] = self->elements[i];
			k++;
			i++;
			j++;
		} else if(self->elements[i] < other->elements[j]){
			i++;
		} else{
			j++;
		}
	}
	return k;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	if(self->len == 0){
		return;
	//}else if(other->len == 0){

    }else {
		int *temp = (int*)malloc((self->len)*sizeof(int));
		int length = copyRepeated(self, other, temp);
		free(self->elements);
		self->elements = temp;
		self->len = length;
	}
	return;
}

int deleteRepeated(Set* self, const Set* other, int *temp){
	int i = 0, j = 0, k = 0;
	while(i < (self->len) && j < (other->len)){
		if(self->elements[i] == other->elements[j]){
			i++;
			j++;
		} else if(self->elements[i] < other->elements[j]){
			temp[k] = self->elements[i];
			i++;
			k++;
		} else{
			j++;
		}
	}
    while(i < self->len){
        temp[k] = self->elements[i];
        i++;
        k++;
    }
	return k;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	if(self->len == 0 || other->len == 0){
		return;
	} else{
		int *temp = (int*)malloc((self->len)*sizeof(int));
		int length = deleteRepeated(self, other, temp);
		free(self->elements);
		self->elements = temp;
		self->len = length;
	}	
	return;
}

int combineSets(Set *self, const Set* other, int *temp){
	int i = 0, j = 0, k = 0;
	while(i < (self->len) && j < (other->len)){
		if(self->elements[i] == other->elements[j]){
			temp[k] = self->elements[i];
			k++;
			i++;
			j++;
		} else if(self->elements[i] < other->elements[j]){
			temp[k] = self->elements[i];
			k++;
			i++;
		} else{
			temp[k] = other->elements[j];
			k++;
			j++;
		}
	}
	if(i == self->len){
		while(j < other->len){
			temp[k] = other->elements[j];
			k++;
			j++;
		}
	} else if(j == other->len){
		while(i < self->len){
			temp[k] = self->elements[i];
			k++;
			i++;
		}
	}
	return k;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	if(other->len == 0){
		return;
	} else{
		int temp_size = self->len + other->len;
		int *temp = (int*)malloc(temp_size*sizeof(int));
		int length = combineSets(self, other, temp);
		free(self->elements);
		self->elements = temp;
		self->len = length;
	}	
	return;
}
