#ifndef _DLIST_H_
#define _DLIST_H_

typedef struct dnode {
  void *val;
  struct dnode *next;
  struct dnode *prev;
} dnode;

typedef struct dlist {
  dnode *head;
} dlist;

dlist *dlist_init();
void dlist_destroy(dlist *dl);
int dlist_empty(dlist *dl);
void dlist_push_back(dlist *dl, void *val);
void dlist_push_front(dlist *dl, void *val);
void dlist_pop_back(dlist *dl);
void dlist_pop_front(dlist *dl);
void *dlist_back(dlist *dl);
void *dlist_front(dlist *dl);

#endif