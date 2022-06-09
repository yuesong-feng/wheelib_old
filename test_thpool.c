#include <stdio.h>
#include <stdlib.h>

#include "thpool.h"

static int a = 0;
pthread_mutex_t mutex_a;

void fn1() { printf("fn1\n"); }

typedef struct fn2_args {
  int a;
  char b;
} fn2_args;
void fn2(fn2_args *args) { printf("fn2 %d, %c\n", args->a, args->b); }

void fn3(struct {int a;const char *str;} * args) { printf("fn2 %d, %s\n", args->a, args->str); }

void add() {
  pthread_mutex_lock(&mutex_a);
  a = a + 1;
  pthread_mutex_unlock(&mutex_a);
}

int main() {
  thpool *tp = thpool_init(8);

  thpool_add(tp, fn1, NULL);

  fn2_args args = {
      .a = 1,
      .b = 'A',
  };
  thpool_add(tp, fn2, &args);

  thpool_add(tp, fn3, &(struct {int a; const char* str;}){3, "hello world!"});

  pthread_mutex_init(&mutex_a, NULL);
  for (int i = 0; i < 1000; i++) {
    thpool_add(tp, add, NULL);
  }
  thpool_destroy(tp);
  
  pthread_mutex_destroy(&mutex_a);
  printf("a: %d\n", a);
  return 0;
}
