#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>

typedef struct queue {
  size_t size;
  size_t capacity;
	size_t start;
  void **data;
} queue;

queue *queue_init(size_t capacity);

void queue_destroy(queue *q);

int queue_push(queue *q, void *value);

int queue_pop(queue *q);

void *queue_front(queue *q);

void *queue_back(queue *q);

#endif
