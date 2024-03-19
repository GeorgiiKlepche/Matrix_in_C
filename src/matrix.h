#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0
#define EPS 1E-7

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int calc_complements(matrix_t *A, matrix_t *result);
int inverse_matrix(matrix_t *A, matrix_t *result);
// help
void fill_matrix(matrix_t *result, double num);
void fill_matrix_minus(matrix_t *result, double num);

#endif  // MATRIX_H_