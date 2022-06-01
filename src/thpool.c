#include "thpool.h"

#include <stdlib.h>
#include <string.h>

void *worker(void *arg) {
  thpool *tp = (thpool *)arg;
  while (1) {
    pthread_mutex_lock(&(tp->mutex));
    // while (tp->stop || queue_empty(tp->tasks)) {
    //   pthread_cond_wait(&(tp->cond), &(tp->mutex));
    // }
    if (tp->stop && queue_empty(tp->tasks)) {
      pthread_mutex_unlock(&(tp->mutex));
      return NULL;
    }
    if (queue_empty(tp->tasks)) {
      pthread_mutex_unlock(&(tp->mutex));
      continue;
    }
    task *t = (task *)queue_front(tp->tasks);
    queue_pop_front(tp->tasks);
    pthread_mutex_unlock(&(tp->mutex));
    t->fn(t->args);
    free(t);
  }
}

thpool *thpool_init(int size) {
  thpool *tp = (thpool *)malloc(sizeof(thpool));
  memset(tp, 0, sizeof(thpool));
  tp->size = size;
  tp->stop = 0;
  tp->tasks = queue_init();
  tp->threads = (pthread_t *)malloc(sizeof(pthread_t) * tp->size);
  memset(tp->threads, 0, sizeof(pthread_t) * tp->size);
  pthread_mutex_init(&(tp->mutex), NULL);
  pthread_cond_init(&(tp->cond), NULL);
  for (int i = 0; i < size; ++i) {
    pthread_create(&(tp->threads[i]), NULL, worker, tp);
  }
  return tp;
}

void thpool_add(thpool *tp, void *fn, void *args) {
  task *t = (task *)malloc(sizeof(task));
  memset(t, 0, sizeof(task));
  t->fn = fn;
  t->args = args;
  pthread_mutex_lock(&(tp->mutex));
  queue_push_back(tp->tasks, t);
  pthread_mutex_unlock(&(tp->mutex));
  // pthread_cond_signal(&(tp->cond));
}

void thpool_destroy(thpool *tp) {
  tp->stop = 1;
  for (int i = 0; i < tp->size; ++i) {
    pthread_join(tp->threads[i], NULL);
  }
  pthread_cond_destroy(&(tp->cond));
  pthread_mutex_destroy(&(tp->mutex));
  queue_destroy(tp->tasks);
  free(tp->threads);
  free(tp);
}