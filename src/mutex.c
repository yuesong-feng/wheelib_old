#include "mutex.h"

#include <assert.h>

void mutex_init(mutex *mtx) {
  assert(pthread_mutex_init(&mtx->mtx, NULL) == 0);
}
void mutex_destroy(mutex *mtx) {
  assert(pthread_mutex_destroy(&mtx->mtx) == 0);
}
void mutex_lock(mutex *mtx) {
  assert(pthread_mutex_lock(&mtx->mtx) == 0);
}
void mutex_unlock(mutex *mtx) {
  assert(pthread_mutex_unlock(&mtx->mtx) == 0);
}
int mutex_trylock(mutex *mtx) {
  return pthread_mutex_trylock(&mtx->mtx);
}
