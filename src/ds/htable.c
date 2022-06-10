#include "htable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

hnode *hnode_init() {
  hnode *hn = (hnode *)malloc(sizeof(hnode));
  return hn;
}

void hnode_destroy(hnode *hn) { free(hn); }

htable *htable_init() {
  htable *ht = (htable *)malloc(sizeof(htable));
  ht->size = 8;
  ht->table = (hnode **)malloc(sizeof(hnode *) * ht->size);
  for (int i = 0; i < ht->size; ++i) {
    ht->table[i] = NULL;
  }
  return ht;
}

void htable_destroy(htable *ht) {
  for (int i = 0; i < ht->size; ++i) {
    hnode *hn = ht->table[i];
    while (hn != NULL) {
      hnode *next = hn->next;
      free(hn);
      hn = hn->next;
    }
  }
  free(ht->table);
  free(ht);
}

int hash(htable *ht, int key) { return key % ht->size; }

void htable_insert(htable *ht, int key, void *val) {
  int loc = hash(ht, key);
  if (ht->table[loc] == NULL) {
    ht->table[loc] = hnode_init();
    ht->table[loc]->key = key;
    ht->table[loc]->val = val;
  } else {
    hnode *hn = ht->table[loc];
    hnode *last = NULL;
    while (hn != NULL) {
      if (hn->key == key) {
        printf("key %d already exist!\n", key);
        return;
      }
      last = hn;
      hn = hn->next;
    }
    last->next = hnode_init();
    last->next->key = key;
    last->next->val = val;
  }
}

hnode *htable_find(htable *ht, int key) {
  int loc = hash(ht, key);
  hnode *hn = ht->table[loc];
  while (hn != NULL && hn->key != key) {
    hn = hn->next;
  }
  return hn;
}

void *htable_at(htable *ht, int key) {
  hnode *hn = htable_find(ht, key);
  if (hn == NULL) {
    return NULL;
  } else {
    return hn->val;
  }
}
