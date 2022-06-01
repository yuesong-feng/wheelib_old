#ifndef _THPOOL_H_
#define _THPOOL_H_
#include "queue.h"
#include "pthread.h"

typedef struct task {
    void (*fn)(void *);
    void *args;
} task;

typedef struct thpool {
    int size;
    int stop;
    pthread_t *threads;
    queue *tasks;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} thpool;

void *worker(void *arg);
thpool *thpool_init(int size);
void thpool_add(thpool *tp, void *fn, void *args);
void thpool_destroy(thpool *tp);

#endif