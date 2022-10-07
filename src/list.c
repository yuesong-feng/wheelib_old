#include "list.h"

#include <stdlib.h>

list *list_init() {
  list *l = (list *)malloc(sizeof(list));
  l->size = 0;
  l->head = (listnode *)malloc(sizeof(listnode));
  l->head->val = NULL;
  l->head->next = l->head;
  l->head->prev = l->head;
  return l;
}

void list_destroy(list *l) {
  listnode *node = l->head->next;
  while (node != l->head) {
    listnode *tmp = node->next;
    free(node);
    node = tmp;
  }
  free(l->head);
  free(l);
}

int list_empty(list *l) { return l->head->next == l->head; }

void list_push_back(list *l, void *val) {
  listnode *node = (listnode *)malloc(sizeof(listnode));
  node->val = val;
  node->prev = l->head->prev;
  node->next = l->head;
  l->head->prev->next = node;
  l->head->prev = node;
  l->size++;
}

void list_push_front(list *l, void *val) {
  listnode *node = (listnode *)malloc(sizeof(listnode));
  node->val = val;
  node->prev = l->head;
  node->next = l->head->next;
  l->head->next = node;
  node->next->prev = node;
  l->size++;
}

void list_pop_back(list *l) {
  listnode *back = l->head->prev;
  back->prev->next = l->head;
  l->head->prev = back->prev;
  l->size--;
  free(back);
}

void list_pop_front(list *l) {
  listnode *front = l->head->next;
  l->head->next = front->next;
  front->next->prev = l->head;
  l->size--;
  free(front);
}

void *list_back(list *l) {
  if (list_empty(l)) {
    return NULL;
  } else {
    return l->head->prev->val;
  }
}

void *list_front(list *l) {
  if (list_empty(l)) {
    return NULL;
  } else {
    return l->head->next->val;
  }
}

int list_size(list *l) { return l->size; }