#include "list.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct job job;
struct job {
  int id;
  const char *name;
  LIST_NODE(job) link;
  LIST_NODE(job) link2;
};

typedef struct scheduler scheduler;
struct scheduler {
  const char *owner;
  LIST(job) jobs;
  LIST(job) jobs2;
};

void test1() {
  scheduler s = {"yuesong", LIST_INIT_STATIC};

  job j1 = {1, "feng", LIST_NODE_INIT_STATIC};

  job j2;
  j2.id = 2;
  j2.name = "yuesong";
  LIST_NODE_INIT(j2.link);

  LIST_ADD_TAIL(s.jobs, &j1, link);
  LIST_ADD_TAIL(s.jobs, &j2, link);

  job *p = NULL;
  LIST_FOR_EACH(p, link, s.jobs) { LOG_INFO("%d, %s", p->id, p->name); }
}

void test2() {
  scheduler *s = (scheduler *)malloc(sizeof(scheduler));
  s->owner = "fengyuesong";
  LIST_INIT(s->jobs);

  job *j1 = (job *)malloc(sizeof(job));
  j1->id = 1;
  j1->name = "feng";
  LIST_NODE_INIT(j1->link);

  job *j2 = (job *)malloc(sizeof(job));
  j2->id = 2;
  j2->name = "yuesong";
  LIST_NODE_INIT(j2->link);

  LIST_ADD_HEAD(s->jobs, j1, link);
  LIST_ADD_HEAD(s->jobs, j2, link);

  job *p = NULL;
  LIST_FOR_EACH(p, link, s->jobs) { LOG_WARN("%d, %s", p->id, p->name); }
}

void test3() {
  printf("test 3: \n");
  scheduler *s = (scheduler *)malloc(sizeof(scheduler));
  s->owner = "fengyuesong";
  LIST_INIT(s->jobs);
  LIST_INIT(s->jobs2);

  job *j1 = (job *)malloc(sizeof(job));
  j1->id = 1;
  j1->name = "feng";
  LIST_NODE_INIT(j1->link);
  LIST_NODE_INIT(j1->link2);

  job *j2 = (job *)malloc(sizeof(job));
  j2->id = 2;
  j2->name = "yuesong";
  LIST_NODE_INIT(j2->link);
  LIST_NODE_INIT(j2->link2);

  LIST_ADD_TAIL(s->jobs, j1, link);
  LIST_ADD_TAIL(s->jobs, j2, link);

  LIST_ADD_HEAD(s->jobs2, j1, link2);
  LIST_ADD_HEAD(s->jobs2, j2, link2);

  job *p = NULL;
  LIST_FOR_EACH(p, link, s->jobs) { LOG_INFO("%d, %s", p->id, p->name); }
  LIST_FOR_EACH(p, link2, s->jobs2) { LOG_ERROR("%d, %s", p->id, p->name); }
}

int main() {
  test1();
  test2();
  test3();

  return 0;
}