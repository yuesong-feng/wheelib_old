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
  LOG_INFO("stack used: %d", stack_size_used(&stk));

  double *in2 = NULL;
  in2 = stack_push(&stk, sizeof(double));
  *in2 = 2.34;
  LOG_INFO("stack used: %d", stack_size_used(&stk));
  char *in3 = NULL;
  in3 = stack_push(&stk, 5);
  memcpy(in3, "feng", 5);
  LOG_INFO("stack used: %d", stack_size_used(&stk));
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

  LOG_INFO("stack used: %d", stack_size_used(stk));
  char *out3 = stack_pop(stk, 8);
  LOG_INFO("%s", out3);
  LOG_INFO("stack used: %d", stack_size_used(stk));
  double *out2 = stack_pop(stk, sizeof(double));
  LOG_INFO("%lf", *out2);
  LOG_INFO("stack used: %d", stack_size_used(stk));
  int *out1 = stack_pop(stk, sizeof(int));
  LOG_INFO("%d", *out1);
  LOG_INFO("stack used: %d", stack_size_used(stk));

  stack_destroy(stk);
}

typedef struct person {
  int id;
  const char *name;
} person;

void test3() {
  stack *stk = stack_init(34);
  LOG_INFO("remain: %d", stack_size_remain(stk));
  person *p1 = stack_push(stk, sizeof(person));
  p1->id = 1;
  p1->name = "feng";
  LOG_INFO("remain: %d", stack_size_remain(stk));
  person *p2 = stack_push(stk, sizeof(person));
  p2->id = 2;
  p2->name = "yuesong";
  LOG_INFO("remain: %d", stack_size_remain(stk));

  person *out2 = stack_pop(stk, sizeof(person));
  LOG_INFO("%d, %s", out2->id, out2->name);
  LOG_INFO("remain: %d", stack_size_remain(stk));
  person *out1 = stack_pop(stk, sizeof(person));
  LOG_INFO("%d, %s", out1->id, out1->name);
  LOG_INFO("remain: %d", stack_size_remain(stk));

  stack_destroy(stk);
}

int main() {
  test1();
  test2();
  test3();
  return 0;
}