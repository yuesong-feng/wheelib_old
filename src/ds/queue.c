#include "src/ds/queue.h"

#include <stdlib.h>

queue *queue_init() {
  queue *q = (queue *)malloc(sizeof(queue));
  q->dl = dlist_init();
  return q;
}
void queue_destroy(queue *q) {
  dlist_destroy(q->dl);
  free(q);
}
int queue_empty(queue *q) { return dlist_empty(q->dl); }
void queue_push_back(queue *q, void *val) { dlist_push_back(q->dl, val); }
void queue_pop_front(queue *q) { dlist_pop_front(q->dl); }
void *queue_back(queue *q) { return dlist_back(q->dl); }
void *queue_front(queue *q) { return dlist_front(q->dl); }