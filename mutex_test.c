#include "mutex.h"

#include "log.h"

int main() {
  mutex mtx;
  mutex_init(&mtx);
  mutex_lock(&mtx);
  mutex_unlock(&mtx);
  mutex_destroy(&mtx);
  return 0;
}
