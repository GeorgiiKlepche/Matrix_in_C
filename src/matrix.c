#include "matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int return_flag = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return_flag = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = malloc(columns * sizeof(double));
    }
  }
  return return_flag;
}

void remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->columns = 0;
  A->rows = 0;
}

int matrix_not_exist(matrix_t *A) {
  int flag = 0;
  if (!A || A->rows <= 0 || A->columns <= 0 || !(A->matrix)) {
    flag = 1;
  }
  return flag;
}

int eq_rows_columns(matrix_t *A, matrix_t *B) {
  int flag = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    flag = 1;
  }
  return flag;
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (matrix_not_exist(A) || matrix_not_exist(B)) {
    flag = FAILURE;
  } else {
    if (eq_rows_columns(A, B)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
            flag = FAILURE;
          }
        }
      }
    } else {
      flag = FAILURE;
    }
  }
  return flag;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A) || matrix_not_exist(B)) {
    flag = 1;
  } else {
    if (eq_rows_columns(A, B)) {
      create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      flag = 2;
    }
  }
  return flag;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A) || matrix_not_exist(B)) {
    flag = 1;
  } else {
    if (eq_rows_columns(A, B)) {
      create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      flag = 2;
    }
  }
  return flag;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A)) {
    flag = 1;
  } else {
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return flag;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A) || matrix_not_exist(B)) {
    flag = 1;
  } else if (A->columns != B->rows) {
    flag = 2;
  } else {
    create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return flag;
}

int transpose(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A)) {
    flag = 1;
  } else {
    create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return flag;
}

matrix_t matrix_for_minor(matrix_t A, int row, int column) {
  matrix_t res;
  int i_res = 0, j_res = 0;
  create_matrix(A.rows - 1, A.columns - 1, &res);
  for (int i = 0; i < A.rows; i++) {
    if (i == row) {
      continue;
    }
    for (int j = 0; j < A.columns; j++) {
      if (j == column) {
        continue;
      } else {
        res.matrix[i_res][j_res] = A.matrix[i][j];
        j_res++;
      }
    }
    j_res = 0;
    i_res++;
  }
  return res;
}

int row_column_not_eq(matrix_t *A) { return A->rows != A->columns; }

int determinant(matrix_t *A, double *result) {
  int flag = 0;
  matrix_t tmp;
  double minor = 0, algeb_compl;
  if (!result || matrix_not_exist(A)) {
    flag = 1;
  } else if (row_column_not_eq(A)) {
    flag = 2;
  } else {
    if (A->rows == 1) {
      *result = **(A->matrix);
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0;
      for (int j = 0; j < A->columns; j++) {
        tmp = matrix_for_minor(*A, 0, j);
        determinant(&tmp, &minor);
        remove_matrix(&tmp);
        algeb_compl = pow(-1, 0 + j) * minor;
        *result += A->matrix[0][j] * algeb_compl;
      }
    }
  }
  return flag;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!result || matrix_not_exist(A)) {
    flag = 1;
  } else if (row_column_not_eq(A) || A->rows == 1) {
    flag = 2;
  } else {
    matrix_t tmp;
    double algeb_compl, minor = 0;
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp = matrix_for_minor(*A, i, j);
        determinant(&tmp, &minor);
        remove_matrix(&tmp);
        algeb_compl = pow(-1, i + j) * minor;
        result->matrix[i][j] = algeb_compl;
      }
    }
  }
  return flag;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  double _determinant = 0;
  matrix_t compl_res, transp_res;
  if (!result || matrix_not_exist(A)) {
    flag = 1;
  } else if (A->rows == 1 || row_column_not_eq(A)) {
    flag = 2;
  } else {
    determinant(A, &_determinant);
    if (fabs(_determinant) < 1E-10) {
      flag = 2;
    } else {
      calc_complements(A, &compl_res);
      transpose(&compl_res, &transp_res);
      mult_number(&transp_res, 1 / _determinant, result);
      remove_matrix(&compl_res);
      remove_matrix(&transp_res);
    }
  }
  return flag;
}

void fill_matrix(matrix_t *result, double num) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = num;
      num++;
    }
  }
}

void fill_matrix_minus(matrix_t *result, double num) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = num;
      num++;
    }
  }
}