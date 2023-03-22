#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

void test1() {
  stack stk;
  stack_init_static(&stk, 17);

  int *in1 = NULL;
  in1 = stack_push(&stk, sizeof(int));
  *in1 = 123;

  double *in2 = NULL;
  in2 = stack_push(&stk, sizeof(double));
  *in2 = 2.34;

  char *in3 = NULL;
  in3 = stack_push(&stk, 5);
  memcpy(in3, "feng", 5);

  char *out3 = stack_pop(&stk, 5);
  LOG_INFO("%s", out3);
  double *out2 = stack_pop(&stk, sizeof(double));
  LOG_INFO("%lf", *out2);
  int *out1 = stack_pop(&stk, sizeof(int));
  LOG_INFO("%d", *out1);

  stack_destroy_static(&stk);
}

void test2() {
  stack *stk = stack_init(1024);

  int *in1 = NULL;
  in1 = stack_push(stk, sizeof(int));
  *in1 = 123;

  double *in2 = NULL;
  in2 = stack_push(stk, sizeof(double));
  *in2 = 2.34;

  char *in3 = NULL;
  in3 = stack_push(stk, 8);
  memcpy(in3, "yuesong", 8);

  char *out3 = stack_pop(stk, 8);
  LOG_INFO("%s", out3);
  double *out2 = stack_pop(stk, sizeof(double));
  LOG_INFO("%lf", *out2);
  int *out1 = stack_pop(stk, sizeof(int));
  LOG_INFO("%d", *out1);

  stack_destroy(stk);
}

int main() {
  test1();
  test2();
  return 0;
}