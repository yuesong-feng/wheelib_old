#ifndef _MUTEX_H_
#define _MUTEX_H_
#ifdef WIN32

#else
#include <pthread.h>
#endif

typedef struct mutex {
  pthread_mutex_t mtx;
} mutex;

void mutex_init(mutex *mtx);
void mutex_destroy(mutex *mtx);
void mutex_lock(mutex *mtx);
void mutex_unlock(mutex *mtx);
int mutex_trylock(mutex *mtx);

#endif
