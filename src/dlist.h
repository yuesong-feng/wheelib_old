#ifndef DLIST_H
#define DLIST_H
#include <stddef.h>

typedef struct dnode {
  void *val;
  struct dnode *next;
  struct dnode *prev;
} dnode;

typedef struct dlist {
  dnode *head;
  size_t size;
} dlist;

dlist *dlist_init();
void dlist_destroy(dlist *dl);
size_t dlist_size(dlist *dl);
int dlist_push_back(dlist *dl, void *val);
int dlist_push_front(dlist *dl, void *val);
void dlist_pop_back(dlist *dl);
void dlist_pop_front(dlist *dl);
void *dlist_back(dlist *dl);
void *dlist_front(dlist *dl);

#endif
