#include "queue.h"

#include <stdio.h>

int main() {
  queue *q = queue_init(4);
  int a = 1, b = 2, c = 3, d = 4;
  queue_push(q, &a);
  queue_push(q, &b);
  printf("front: %d\n", *(int *)queue_front(q));
  printf("back: %d\n", *(int *)queue_back(q));
  queue_pop(q);
  queue_push(q, &c);
  queue_push(q, &d);
  queue_pop(q);
  printf("front: %d\n", *(int *)queue_front(q));
  printf("back: %d\n", *(int *)queue_back(q));
  queue_destroy(q);
}