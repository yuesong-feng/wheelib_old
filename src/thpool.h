#ifndef THPOOL_H
#define THPOOL_H
#include <pthread.h>

#include "dlist.h"

typedef struct job {
  void (*fn)(void *);
  void *arg;
} job;

typedef struct thpool {
  dlist *jobs;
  pthread_mutex_t jobs_mutex;
  pthread_cond_t jobs_cond;
  int size;
  pthread_t *threads;
  char stop;
} thpool;

thpool *thpool_init(int size);
int thpool_add(thpool *tp, void *fn, void *arg);
void thpool_destroy(thpool *tp);

#endif
