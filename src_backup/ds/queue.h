#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "ds/dlist.h"

typedef struct queue{
    dlist *dl;
} queue;

queue *queue_init();
void queue_destroy(queue *q);
int queue_empty(queue *q);
void queue_push_back(queue *q, void *val);
void queue_pop_front(queue *q);
void *queue_back(queue *q);
void *queue_front(queue *q);

#endif