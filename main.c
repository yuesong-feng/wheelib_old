#include <stdio.h>
#include <stdlib.h>

#include "thpool.h"

static int a = 0;
void fn() { printf("fn\n"); }
struct fn2_args {
  int a;
  char b;
};
void fn2(struct fn2_args *args) { printf("fn2 %d, %c\n", args->a, args->b); }

void add() { a = a + 1; }

int main() {
  thpool *tp = thpool_init(3);

  thpool_add(tp, fn, NULL);
  thpool_add(tp, fn2, &(struct fn2_args){1, 'a'});
  thpool_add(tp, fn2, &(struct fn2_args){2, 'b'});
  thpool_add(tp, fn2, &(struct fn2_args){3, 'c'});
  for(int i = 0; i < 1000; i++){
    thpool_add(tp, add, NULL);
  }
  thpool_destroy(tp);
  printf("%d\n", a);
  return 0;
}