#include "queue.h"

#include <stdlib.h>

queue *queue_init(size_t capacity) {
  if (capacity == 0) {
    return NULL;
  }
  queue *q = (queue *)malloc(sizeof(queue));
  if (q == NULL) {
    return NULL;
  }
  q->size = 0;
  q->capacity = capacity;
  q->start = 0;
  q->data = (void **)malloc(capacity * sizeof(void *));
  if (q->data == NULL) {
    free(q);
    return NULL;
  }
  for (size_t i = 0; i < capacity; ++i) {
    q->data[i] = NULL;
  }
  return q;
}

void queue_destroy(queue *q) {
  free(q->data);
  free(q);
}

int queue_push(queue *q, void *value) {
  if (q->size == q->capacity) {
    return -1;
  }
  int pos = q->start + q->size;
  if (pos >= q->capacity) {
    pos -= q->capacity;
  }
  q->data[pos] = value;
  q->size++;
  return 0;
}

int queue_pop(queue *q) {
  if (q->size == 0) {
    return -1;
  }
  q->data[q->start] = NULL;
  q->start++;
  q->size--;
  if (q->start >= q->capacity) {
    q->start -= q->capacity;
  }
  return 0;
}

void *queue_front(queue *q) {
  if (q->size == 0) return NULL;
  return q->data[q->start];
}

void *queue_back(queue *q) {
  if (q->size == 0) return NULL;
  int pos = q->start + q->size - 1;
  if (pos >= q->capacity) {
    pos -= q->capacity;
  }
  return q->data[pos];
}
