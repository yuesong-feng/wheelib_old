#include "dlist.h"

#include <stdlib.h>

dlist *dlist_init() {
  dlist *dl = (dlist *)malloc(sizeof(dlist));
  if (dl == NULL) return NULL;
  dl->size = 0;
  dl->head = (dnode *)malloc(sizeof(dnode));
  if (dl->head == NULL) {
    free(dl);
    return NULL;
  }
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

int dlist_push_back(dlist *dl, void *val) {
  dnode *dn = (dnode *)malloc(sizeof(dnode));
  if (dn == NULL) {
    return -1;
  }
  dn->val = val;
  dn->prev = dl->head->prev;
  dn->next = dl->head;
  dl->head->prev->next = dn;
  dl->head->prev = dn;
  dl->size++;
  return 0;
}

int dlist_push_front(dlist *dl, void *val) {
  dnode *dn = (dnode *)malloc(sizeof(dnode));
  if (dn == NULL) {
    return -1;
  }
  dn->val = val;
  dn->prev = dl->head;
  dn->next = dl->head->next;
  dl->head->next = dn;
  dn->next->prev = dn;
  dl->size++;
  return 0;
}

void dlist_pop_back(dlist *dl) {
  if (dl->size == 0) return;
  dnode *back = dl->head->prev;
  back->prev->next = dl->head;
  dl->head->prev = back->prev;
  dl->size--;
  free(back);
}

void dlist_pop_front(dlist *dl) {
  if (dl->size == 0) return;
  dnode *front = dl->head->next;
  dl->head->next = front->next;
  front->next->prev = dl->head;
  dl->size--;
  free(front);
}

void *dlist_back(dlist *dl) {
  if (dl->size == 0) {
    return NULL;
  } else {
    return dl->head->prev->val;
  }
}

void *dlist_front(dlist *dl) {
  if (dl->size == 0) {
    return NULL;
  } else {
    return dl->head->next->val;
  }
}

size_t dlist_size(dlist *dl) { return dl->size; }
