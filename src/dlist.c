#include "dlist.h"

#include <stdlib.h>

dlist *dlist_init() {
  dlist *dl = (dlist *)malloc(sizeof(dlist));
  dl->head = (dnode *)malloc(sizeof(dnode));
  dl->head->val = NULL;
  dl->head->next = dl->head;
  dl->head->prev = dl->head;
  return dl;
}

void dlist_destroy(dlist *dl) {
  dnode *dn = dl->head->next;
  while (dn != dl->head) {
    dn = dn->next;
    free(dn->prev);
  }
  free(dl->head);
  free(dl);
}

int dlist_empty(dlist *dl) { return dl->head->next == dl->head; }

void dlist_push_back(dlist *dl, void *val) {
  dnode *dn = (dnode *)malloc(sizeof(dnode));
  dn->val = val;
  dn->prev = dl->head->prev;
  dn->next = dl->head;
  dl->head->prev->next = dn;
  dl->head->prev = dn;
}

void dlist_push_front(dlist *dl, void *val) {
  dnode *dn = (dnode *)malloc(sizeof(dnode));
  dn->val = val;
  dn->prev = dl->head;
  dn->next = dl->head->next;
  dl->head->next = dn;
  dn->next->prev = dn;
}

void dlist_pop_back(dlist *dl) {
  dnode *back = dl->head->prev;
  back->prev->next = dl->head;
  dl->head->prev = back->prev;
  free(back);
}

void dlist_pop_front(dlist *dl) {
  dnode *front = dl->head->next;
  dl->head->next = front->next;
  front->next->prev = dl->head;
  free(front);
}

void *dlist_back(dlist *dl) {
  if (dlist_empty(dl)) {
    return NULL;
  } else {
    return dl->head->prev->val;
  }
}

void *dlist_front(dlist *dl) {
  if (dlist_empty(dl)) {
    return NULL;
  } else {
    return dl->head->next->val;
  }
}