// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdatomic.h>
// #include <assert.h>
// #include <unistd.h>
// #include <pthread.h>

// #define NTHREAD 64
// enum { T_FREE = 0, T_LIVE, T_DEAD, };
// struct thread {
//   int id, status;
//   pthread_t thread;
//   void (*entry)(void *);
//   void *args;
// };

// struct thread tpool[NTHREAD], *tptr = tpool;

// void *wrapper(void *arg) {
//   struct thread *thread = (struct thread *)arg;
//   thread->entry(thread->args);
//   return NULL;
// }

// void create(void *fn, void *args) {
//   assert(tptr - tpool < NTHREAD);
//   *tptr = (struct thread) {
//     .id = tptr - tpool + 1,
//     .status = T_LIVE,
//     .entry = fn,
//     .args = args
//   };
//   pthread_create(&(tptr->thread), NULL, wrapper, tptr);
//   ++tptr;
// }

// void join() {
//   for (int i = 0; i < NTHREAD; i++) {
//     struct thread *t = &tpool[i];
//     if (t->status == T_LIVE) {
//       pthread_join(t->thread, NULL);
//       t->status = T_DEAD;
//     }
//   }
// }

// __attribute__((destructor)) void cleanup() {
//   join();
// }

#include <pthread.h>
typedef struct task1 {
  pthread_t *thraed;
  void (*fn)(void *args);
  void *args;
} task1;

void *wrapper(void *arg) {
  task1 *t = (task1 *)arg;
  t->fn(t->args);
  return NULL;
}

void create(void *fn, void *args) {
  task1 *t = (task1 *)malloc(sizeof(task1));
  t->fn = fn;
  t->args = args;
  pthread_create(&(t->thraed), NULL, wrapper, t);
}