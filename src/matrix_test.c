#include "matrix.h"

#include <check.h>

matrix_t result, result_defolt, result_defolt_2, temp, temp2, temp3, test,
    test2, result_sum, result_sub, result_mult_num, result_mult, result_trans,
    result_calc, result_inv;
double deter_result = 0, num = 777.777, resul;
int res = 0, result_defol, result_status;
double matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
       sum_matrix[3][2] = {{2, 4}, {6, 8}, {10, 12}},
       sub_matrix[3][2] = {{0, 0}, {0, 0}, {0, 0}},
       mult_num_matrix[3][2] = {{2, 4}, {6, 8}, {10, 12}},
       trans_matrix[3][3] = {{1, 3, 5}, {2, 4, 6}},
       calc_matrix[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}},
       inv_matrix[2][2] = {{-2.25, 1.25}, {1.75, -0.75}};
START_TEST(create1) {
  res = create_matrix(0, 5, &test);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(create2) {
  res = create_matrix(-2, 5, &test);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(create3) {
  res = create_matrix(3, 3, NULL);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(create4) {
  res = create_matrix(3, 3, &test);
  ck_assert_int_eq(0, res);
  remove_matrix(&test);
}
END_TEST

START_TEST(create5) {
  create_matrix(3, 3, &test);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      test.matrix[i][j] = 0;
    }
  }
  remove_matrix(&test);
}
END_TEST

START_TEST(eq1) {
  res = eq_matrix(NULL, NULL);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(eq2) {
  create_matrix(3, 3, &test);
  create_matrix(3, 3, &test2);
  fill_matrix(&test, 0.5);
  fill_matrix(&test2, 0.5);
  test.matrix[0][1] = 2;
  ck_assert_int_eq(1, eq_matrix(&test, &test));
  ck_assert_int_eq(0, eq_matrix(&test, &test2));
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(eq3) {
  create_matrix(3, 2, &test);
  create_matrix(3, 4, &test2);
  fill_matrix(&test, 0.5);
  fill_matrix(&test2, 3);
  ck_assert_int_eq(eq_matrix(&test, &test2), 0);
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(eq4) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  create_matrix(3, 3, &temp3);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(eq_matrix(&temp, &temp2), SUCCESS);
  ck_assert_int_eq(eq_matrix(&temp, &temp3), FAILURE);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&temp3);
}
END_TEST

START_TEST(eq5) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  temp2.matrix[1][1] = 0;
  temp2.matrix[1][2] = 77;
  ck_assert_int_eq(eq_matrix(&temp, &temp2), FAILURE);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(eq6) {
  create_matrix(3, 3, &temp);
  create_matrix(2, 3, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(eq_matrix(&temp, &temp2), FAILURE);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(eq7) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 21, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(eq_matrix(&temp, &temp2), FAILURE);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(eq8) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  temp.matrix[0][1] = 4.67773;
  temp2.matrix[0][1] = 4.67774;
  ck_assert_int_eq(eq_matrix(&temp, &temp2), FAILURE);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(sum1) {
  create_matrix(3, 2, &test);
  ck_assert_int_eq(sum_matrix(NULL, &test, NULL), 1);
  remove_matrix(&test);
}
END_TEST

START_TEST(sum2) {
  create_matrix(3, 2, &test);
  create_matrix(3, 4, &test2);
  ck_assert_int_eq(sum_matrix(&test, &test2, &result_sum), 2);
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(sum3) {
  create_matrix(3, 2, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(sum_matrix(&test, &test, &result_sum), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(sum_matrix[i][j], result_sum.matrix[i][j],
                              0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_sum);
}
END_TEST

START_TEST(sum4) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  create_matrix(3, 3, &result_defolt);
  fill_matrix(&temp, 1);
  fill_matrix_minus(&temp2, 32);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] + temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(sum_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(sum5) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 1, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(sum_matrix(&temp, &temp2, &result), 2);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(sub1) {
  create_matrix(3, 2, &test);
  ck_assert_int_eq(sub_matrix(NULL, &test, NULL), 1);
  remove_matrix(&test);
}
END_TEST

START_TEST(sub2) {
  create_matrix(3, 2, &test);
  create_matrix(3, 4, &test2);
  ck_assert_int_eq(sub_matrix(&test, &test2, &result_sub), 2);
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(sub3) {
  create_matrix(3, 2, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(sub_matrix(&test, &test, &result_sub), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(sub_matrix[i][j], result_sub.matrix[i][j],
                              0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_sub);
}
END_TEST

START_TEST(sub4) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  create_matrix(3, 3, &result_defolt);
  fill_matrix(&temp, 1);
  fill_matrix_minus(&temp2, 32);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] - temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(sub_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(sub5) {
  create_matrix(3, 3, &temp);
  create_matrix(1, 3, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(sub_matrix(&temp, &temp2, &result), 2);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(mult_num1) {
  ck_assert_int_eq(mult_number(NULL, 0.25, &result_mult_num), 1);
}
END_TEST

START_TEST(mult_num2) {
  create_matrix(3, 2, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(mult_number(&test, 2, &result_mult_num), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(mult_num_matrix[i][j],
                              result_mult_num.matrix[i][j], 0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_mult_num);
}
END_TEST

START_TEST(mult_num3) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &temp2);
  create_matrix(3, 3, &result_defolt);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] * 777.777;
    }
  }
  ck_assert_int_eq(mult_number(&temp, num, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(mult1) {
  create_matrix(3, 2, &test);
  create_matrix(3, 4, &test2);
  ck_assert_int_eq(mult_matrix(&test, &test2, NULL), 1);
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(mult2) {
  create_matrix(3, 2, &test);
  create_matrix(3, 4, &test2);
  ck_assert_int_eq(mult_matrix(&test, &test2, &result_mult), 2);
  remove_matrix(&test);
  remove_matrix(&test2);
}
END_TEST

START_TEST(mult3) {
  create_matrix(2, 2, &test);
  create_matrix(2, 2, &test2);
  fill_matrix(&test, 1);
  fill_matrix(&test2, 1);
  ck_assert_int_eq(mult_matrix(&test, &test2, &result_mult), 0);
  remove_matrix(&test);
  remove_matrix(&test2);
  remove_matrix(&result_mult);
}
END_TEST

START_TEST(mult4) {
  create_matrix(3, 2, &temp);
  create_matrix(2, 3, &temp2);
  create_matrix(3, 3, &result_defolt);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  result_defolt.matrix[0][0] = 9;
  result_defolt.matrix[0][1] = 12;
  result_defolt.matrix[0][2] = 15;
  result_defolt.matrix[1][0] = 19;
  result_defolt.matrix[1][1] = 26;
  result_defolt.matrix[1][2] = 33;
  result_defolt.matrix[2][0] = 29;
  result_defolt.matrix[2][1] = 40;
  result_defolt.matrix[2][2] = 51;
  ck_assert_int_eq(mult_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(mult5) {
  create_matrix(2, 3, &temp);
  create_matrix(3, 2, &temp2);
  create_matrix(2, 2, &result_defolt);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  result_defolt.matrix[0][0] = 22;
  result_defolt.matrix[0][1] = 28;
  result_defolt.matrix[1][0] = 49;
  result_defolt.matrix[1][1] = 64;
  ck_assert_int_eq(mult_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&temp2);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(mult6) {
  create_matrix(3, 3, &temp);
  create_matrix(1, 1, &temp2);
  fill_matrix(&temp, 1);
  fill_matrix(&temp2, 1);
  ck_assert_int_eq(mult_matrix(&temp, &temp2, &result), 2);
  remove_matrix(&temp);
  remove_matrix(&temp2);
}
END_TEST

START_TEST(trans1) { ck_assert_int_eq(transpose(NULL, &result_trans), 1); }
END_TEST

START_TEST(trans2) {
  create_matrix(3, 2, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(transpose(&test, &result_trans), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(trans_matrix[i][j], result_trans.matrix[i][j],
                              0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_trans);
}
END_TEST

START_TEST(trans3) {
  create_matrix(3, 2, &temp);
  create_matrix(2, 3, &result_defolt);
  fill_matrix(&temp, 1);
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = 3;
  result_defolt.matrix[0][2] = 5;
  result_defolt.matrix[1][0] = 2;
  result_defolt.matrix[1][1] = 4;
  result_defolt.matrix[1][2] = 6;
  ck_assert_int_eq(transpose(&temp, &result), 0);
  ck_assert_int_eq(eq_matrix(&result_defolt, &result), SUCCESS);
  remove_matrix(&temp);
  remove_matrix(&result);
  remove_matrix(&result_defolt);
}
END_TEST

START_TEST(deter1) {
  ck_assert_int_eq(determinant(NULL, &deter_result), 1);
}
END_TEST

START_TEST(deter2) {
  create_matrix(3, 2, &test);
  ck_assert_int_eq(determinant(&test, &deter_result), 2);
  remove_matrix(&test);
}
END_TEST

START_TEST(deter3) {
  create_matrix(1, 1, &test);
  fill_matrix(&test, 1);
  determinant(&test, &deter_result);
  ck_assert_double_eq_tol(1, deter_result, 0.0000001);
  remove_matrix(&test);
}
END_TEST

START_TEST(deter4) {
  create_matrix(2, 2, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(determinant(&test, &deter_result), 0);
  ck_assert_double_eq_tol(-2, deter_result, 0.0000001);
  remove_matrix(&test);
}
END_TEST

START_TEST(deter5) {
  create_matrix(3, 3, &test);
  fill_matrix(&test, 3);
  determinant(&test, &deter_result);
  ck_assert_double_eq_tol(0, deter_result, 0.0000001);
  remove_matrix(&test);
}
END_TEST

START_TEST(deter6) {
  create_matrix(3, 2, &temp);
  fill_matrix(&temp, 1);
  result_defol = determinant(&temp, &resul);
  ck_assert_int_eq(result_defol, 2);
  remove_matrix(&temp);
}
END_TEST

START_TEST(deter7) {
  create_matrix(3, 3, &temp);
  fill_matrix(&temp, 1);
  result_defol = determinant(&temp, &resul);
  ck_assert_int_eq(result_defol, 0);
  ck_assert_uint_eq(resul, 0);
  remove_matrix(&temp);
}
END_TEST

START_TEST(deter8) {
  create_matrix(3, 3, &temp);
  temp.matrix[0][0] = 0;
  temp.matrix[0][1] = 9;
  temp.matrix[0][2] = 5;
  temp.matrix[1][0] = 4;
  temp.matrix[1][1] = 3;
  temp.matrix[1][2] = -5;
  temp.matrix[2][0] = -1;
  temp.matrix[2][1] = 6;
  temp.matrix[2][2] = -4;
  result_defol = determinant(&temp, &resul);
  ck_assert_int_eq(result_defol, 0);
  ck_assert_uint_eq(resul, 324);
  remove_matrix(&temp);
}
END_TEST

START_TEST(calc1) {
  ck_assert_int_eq(calc_complements(NULL, &result_calc), 1);
}
END_TEST

START_TEST(calc2) {
  create_matrix(1, 1, &test);
  ck_assert_int_eq(calc_complements(&test, &result_calc), 2);
  remove_matrix(&test);
}
END_TEST

START_TEST(calc3) {
  create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  ck_assert_int_eq(calc_complements(&test, &result_calc), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(calc_matrix[i][j], result_calc.matrix[i][j],
                              0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_calc);
}
END_TEST

START_TEST(calc4) {
  create_matrix(3, 2, &test);
  fill_matrix(&test, 1);
  result_status = calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 2);
  remove_matrix(&test);
}
END_TEST

START_TEST(calc5) {
  create_matrix(3, 3, &test);
  fill_matrix(&test, 1);
  result_status = calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 0);
  remove_matrix(&test);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc6) {
  create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  calc_complements(&test, &result);
  create_matrix(3, 3, &test2);
  test2.matrix[0][0] = 0;
  test2.matrix[0][1] = 10;
  test2.matrix[0][2] = -20;
  test2.matrix[1][0] = 4;
  test2.matrix[1][1] = -14;
  test2.matrix[1][2] = 8;
  test2.matrix[2][0] = -8;
  test2.matrix[2][1] = -2;
  test2.matrix[2][2] = 4;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_uint_eq(result.matrix[i][j], test2.matrix[i][j]);
    }
  }
  remove_matrix(&test);
  remove_matrix(&test2);
  remove_matrix(&result);
}
END_TEST

START_TEST(inv1) { ck_assert_int_eq(inverse_matrix(NULL, &result_inv), 1); }
END_TEST

START_TEST(inv2) {
  create_matrix(1, 2, &test);
  ck_assert_int_eq(inverse_matrix(&test, &result_inv), 2);
  remove_matrix(&test);
}
END_TEST

START_TEST(inv3) {
  create_matrix(2, 2, &test);
  fill_matrix(&test, 1.5);
  ck_assert_int_eq(inverse_matrix(&test, &result_inv), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(inv_matrix[i][j], result_inv.matrix[i][j],
                              0.0000001);
    }
  }
  remove_matrix(&test);
  remove_matrix(&result_inv);
}
END_TEST

START_TEST(inv4) {
  create_matrix(3, 3, &test);
  fill_matrix(&test, 1);
  ck_assert_int_eq(inverse_matrix(&test, &result_inv), 2);
  remove_matrix(&test);
}
END_TEST

START_TEST(inv5) {
  create_matrix(3, 3, &temp);
  create_matrix(3, 3, &result_defolt);
  temp.matrix[0][0] = 2;
  temp.matrix[0][1] = 5;
  temp.matrix[0][2] = 7;
  temp.matrix[1][0] = 6;
  temp.matrix[1][1] = 3;
  temp.matrix[1][2] = 4;
  temp.matrix[2][0] = 5;
  temp.matrix[2][1] = -2;
  temp.matrix[2][2] = -3;
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = -1;
  result_defolt.matrix[0][2] = 1;
  result_defolt.matrix[1][0] = -38;
  result_defolt.matrix[1][1] = 41;
  result_defolt.matrix[1][2] = -34;
  result_defolt.matrix[2][0] = 27;
  result_defolt.matrix[2][1] = -29;
  result_defolt.matrix[2][2] = 24;
  inverse_matrix(&temp, &result_defolt_2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_uint_eq(result_defolt.matrix[i][j],
                        result_defolt_2.matrix[i][j]);
    }
  }
  remove_matrix(&temp);
  remove_matrix(&result_defolt);
  remove_matrix(&result_defolt_2);
}
END_TEST

START_TEST(inv6) {
  create_matrix(3, 3, &temp);
  fill_matrix(&temp, 1);
  result_status = inverse_matrix(&temp, &result);
  ck_assert_int_eq(result_status, 2);
  remove_matrix(&temp);
}
END_TEST

START_TEST(inv7) {
  create_matrix(1, 1, &temp);
  fill_matrix(&temp, 1);
  inverse_matrix(&temp, &result);
  result_status = inverse_matrix(&temp, &result);
  ck_assert_int_eq(result_status, 2);
  remove_matrix(&temp);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, create1);
  tcase_add_test(tc1_1, create2);
  tcase_add_test(tc1_1, create3);
  tcase_add_test(tc1_1, create4);
  tcase_add_test(tc1_1, create5);
  tcase_add_test(tc1_1, eq1);
  tcase_add_test(tc1_1, eq2);
  tcase_add_test(tc1_1, eq3);
  tcase_add_test(tc1_1, eq4);
  tcase_add_test(tc1_1, eq5);
  tcase_add_test(tc1_1, eq6);
  tcase_add_test(tc1_1, eq7);
  tcase_add_test(tc1_1, eq8);
  tcase_add_test(tc1_1, sum1);
  tcase_add_test(tc1_1, sum2);
  tcase_add_test(tc1_1, sum3);
  tcase_add_test(tc1_1, sum4);
  tcase_add_test(tc1_1, sum5);
  tcase_add_test(tc1_1, sub1);
  tcase_add_test(tc1_1, sub2);
  tcase_add_test(tc1_1, sub3);
  tcase_add_test(tc1_1, sub4);
  tcase_add_test(tc1_1, sub5);
  tcase_add_test(tc1_1, mult_num1);
  tcase_add_test(tc1_1, mult_num2);
  tcase_add_test(tc1_1, mult_num3);
  tcase_add_test(tc1_1, mult1);
  tcase_add_test(tc1_1, mult2);
  tcase_add_test(tc1_1, mult3);
  tcase_add_test(tc1_1, mult4);
  tcase_add_test(tc1_1, mult5);
  tcase_add_test(tc1_1, mult6);
  tcase_add_test(tc1_1, trans1);
  tcase_add_test(tc1_1, trans2);
  tcase_add_test(tc1_1, trans3);
  tcase_add_test(tc1_1, deter1);
  tcase_add_test(tc1_1, deter2);
  tcase_add_test(tc1_1, deter3);
  tcase_add_test(tc1_1, deter4);
  tcase_add_test(tc1_1, deter5);
  tcase_add_test(tc1_1, deter6);
  tcase_add_test(tc1_1, deter7);
  tcase_add_test(tc1_1, deter8);
  tcase_add_test(tc1_1, calc1);
  tcase_add_test(tc1_1, calc2);
  tcase_add_test(tc1_1, calc3);
  tcase_add_test(tc1_1, calc4);
  tcase_add_test(tc1_1, calc5);
  tcase_add_test(tc1_1, calc6);
  tcase_add_test(tc1_1, inv1);
  tcase_add_test(tc1_1, inv2);
  tcase_add_test(tc1_1, inv3);
  tcase_add_test(tc1_1, inv4);
  tcase_add_test(tc1_1, inv5);
  tcase_add_test(tc1_1, inv6);
  tcase_add_test(tc1_1, inv7);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
