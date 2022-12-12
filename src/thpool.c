#include "thpool.h"

#include <stdlib.h>

static void *worker(void *arg) {
  thpool *tp = (thpool *)arg;
  while (1) {
    pthread_mutex_lock(&tp->jobs_mutex);
    while (!tp->stop && dlist_size(tp->jobs) == 0) {
      pthread_cond_wait(&tp->jobs_cond, &tp->jobs_mutex);
    }
    if (tp->stop && dlist_size(tp->jobs) == 0) {
      pthread_mutex_unlock(&tp->jobs_mutex);
      break;
    }
    job *j = (job *)dlist_front(tp->jobs);
    dlist_pop_front(tp->jobs);
    pthread_mutex_unlock(&tp->jobs_mutex);
    j->fn(j->arg);
    free(j);
  }
  return NULL;
}

thpool *thpool_init(int size) {
  thpool *tp = (thpool *)malloc(sizeof(thpool));
  if (tp == NULL) return NULL;
  tp->stop = 0;
  tp->jobs = dlist_init();
  if (tp->jobs == NULL) {
    free(tp);
    return NULL;
  }
  pthread_mutex_init(&tp->jobs_mutex, NULL);
  pthread_cond_init(&tp->jobs_cond, NULL);
  tp->size = size;
  tp->threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
  if (tp->threads == NULL) {
    free(tp->jobs);
    free(tp);
    return NULL;
  }
  for (int i = 0; i < size; ++i) {
    pthread_create(&tp->threads[i], NULL, &worker, tp);
  }
  return tp;
}

int thpool_add(thpool *tp, void *fn, void *arg) {
  job *j = (job *)malloc(sizeof(job));
  if (j == NULL) {
    return -1;
  }
  j->fn = fn;
  j->arg = arg;
  pthread_mutex_lock(&tp->jobs_mutex);
  dlist_push_back(tp->jobs, j);
  pthread_mutex_unlock(&tp->jobs_mutex);
  pthread_cond_signal(&tp->jobs_cond);
  return 0;
}

void thpool_destroy(thpool *tp) {
  tp->stop = 1;
  pthread_cond_broadcast(&tp->jobs_cond);
  for (int i = 0; i < tp->size; ++i) {
    pthread_join(tp->threads[i], NULL);
  }
  free(tp->threads);
  pthread_cond_destroy(&tp->jobs_cond);
  pthread_mutex_destroy(&tp->jobs_mutex);
  dlist_destroy(tp->jobs);
  free(tp);
}
