# Matrix Library

This project provides a C implementation of various operations with matrices, such as creating, removing, adding, subtracting, multiplying, and comparing matrices.

## Build

To build the project, run the following command:
```
make
```

To clean the build artifacts, run the following command:
```
make clean
```

## Dependencies

This project requires make and a gcc compiler.

## Matrix operations

All operations (except matrix comparison) should return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

```c
int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
```

```c
#define SUCCESS 1
#define FAILURE 0

int eq_matrix(matrix_t *A, matrix_t *B);
```

```c
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int calc_complements(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int inverse_matrix(matrix_t *A, matrix_t *result);
```

## Usage Examples

Here's an example of how to use the library to create and add two matrices:

```c
#include <stdio.h>
#include "matrix.h"

int main() {
    matrix_t A, B, C;
    create_matrix(3, 3, &A);
    create_matrix(3, 3, &B);
    create_matrix(3, 3, &C);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = i * A.columns + j + 1;
            B.matrix[i][j] = i * A.columns + j + 1;
        }
    }

    sum_matrix(&A, &B, &C);

    for (int i = 0; i < C.rows; i++) {
        for (int j = 0; j < C.columns; j++) {
            printf("%lf ", C.matrix[i][j]);
        }
        printf("\n");
    }

    remove_matrix(&A);
    remove_matrix(&B);
    remove_matrix(&C);
    return 0;
}
```

## Development

To run the tests, run the following command:
```
make tests
```