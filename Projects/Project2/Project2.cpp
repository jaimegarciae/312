/* Project2.cpp
 * Jaime Eugenio Garcia
 * EE312, Spring 2017
 * Project 2, Matrix Multiplication
 */

#include <stdio.h>
#include <stdint.h>
#include "MatrixMultiply.h"
#include <stdlib.h>

/*
	multiplyMatrices: multiplies 2 matrices and stores result in already allocated memory
	inputs: pointer to matrix A (m x n), m, n, pointer to matrix B (n x k), k, pointer to matrix C (where results are stored)
	output: none 
*/
void multiplyMatrices(double a[], const uint32_t a_rows, const uint32_t a_cols, double b[], const uint32_t b_cols, double c[]) {
	/* 
	Implementation of 3 nested for loops iterates through the elements of A and B stored in
	row major order, makes individual multiplications according to the Matrix Multiplication
	rule, and stores the results in C (also in row major order). 
	*/

	// First for loop iterates through the rows of A
	for(int i = 0; i < a_rows; i++){
		// Second for loop iterates through the columns of B
		for(int j = 0; j < b_cols; j++){
			c[i*b_cols + j] = 0;
			// Third for loop iterates through the elements in the current row for A and current column for B
			for(int k = 0; k < a_cols; k++){
				c[i*b_cols + j]  += a[i*a_cols + k] * b[k*b_cols + j]; 
			}
		}
	}
	return;
}
/*
	multiplyMatricesPtr: multiplies 2 matrices with dynamic memory allocation 
	inputs: pointer to matrix A (m x n), m, n, pointer to matrix B (n x k), k
	output: pointer to new matrix A x B in row major order
*/
double** multiplyMatricesPtr(double** a, const uint32_t a_rows, const uint32_t a_cols, double** b, const uint32_t b_cols) {
    	int matrixSize = a_rows * b_cols;
	if(matrixSize != 0){
		// Dynamic memory allocation for array where result of multiplication will be stored
		double **resultMatrix = (double**)malloc(a_rows * sizeof(double*));
		if(resultMatrix != 0){
			for(int i = 0; i < a_rows; i++){
				resultMatrix[i] = (double*)malloc(b_cols * sizeof(double));
			}	
		} else{
    			return NULL;
		}
		// Multiplication of arrays received as argument, result stored in new array
	        // Similar implementation to multiplyMatrices with 3 nested for loops 
        	for(int i = 0; i < a_rows; i++){
                	for(int j = 0; j < b_cols; j++){
                        	resultMatrix[i][j] = 0;
                        	for(int k = 0; k < a_cols; k++){
                                	resultMatrix[i][j] += a[i][k] * b[k][j];
                        	}
                	}
		}
		return resultMatrix;
	} else{
		return NULL;
	}
}

/*
	transposeMatrix: creates the transpose of a matrix
	inputs: pointer to original matrix, # of rows in matrix, # of columns in matrix
	output: pointer to transpose matrix in row major order
*/
double** transposeMatrix(double** a, const uint32_t a_rows, const uint32_t a_cols) {
	int matrixSize = a_rows * a_cols;
	if(matrixSize != 0){
		//Dynamic memory allocation
		double** transpose = (double**)malloc(a_cols * sizeof(double*));
		if(transpose != 0){
			for(int i = 0; i < a_cols; i++){
				transpose[i] = (double*)malloc(a_rows * sizeof(double));
			}
		}else{
			return NULL;
		}
		// Values of original matrix are being stored in empty transpose matrix
		for(int i = 0; i < a_cols; i++){
			for(int j = 0; j < a_rows; j++){
				transpose[i][j] = a[j][i];	
			}
		}
		return transpose;
	} else{
		return NULL;
	}
}
