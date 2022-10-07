#ifndef _THPOOL_H_
#define _THPOOL_H_
#include <pthread.h>
#include "ds/queue.h"

typedef struct task {
  void (*fn)(void *);
  void *args;
} task;

typedef struct thpool {
  int size;
  int stop;
  pthread_t *threads;
  queue *tasks;
  pthread_mutex_t mutex;  // tasks queue lock
  pthread_cond_t cond;    // condition: wait if not stop and tasks empty
} thpool;

thpool *thpool_init(int size);
void thpool_add(thpool *tp, void *fn, void *args);
void thpool_destroy(thpool *tp);

#endif
