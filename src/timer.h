#ifndef _TIMER_H_
#define _TIMER_H_
#include <time.h>
#include <stdio.h>

static clock_t ct = 0;

#define TIMER                                             \
  if (ct == 0) {                                          \
    ct = clock();                                         \
  } else {                                                \
    clock_t now = clock();                                \
    printf("timing from last point: %lu ms\n", now - ct); \
    ct = now;                                             \
  }

#endif