#include "hashtable.h"

#include <stdlib.h>
#include <string.h>

static unsigned int hash_function(const char *buf, unsigned int len) {
  unsigned int hash = 5381;

  while (len--) hash = ((hash << 5) + hash) + (*buf++); /* hash * 33 + c */
  return hash;
}

hash_table *hash_table_init(size_t size) {
  hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
  if (ht == NULL) return NULL;
  ht->count = 0;
  ht->size = size;
  ht->buckets = (hash_node **)malloc(size * sizeof(hash_node *));
  if (ht->buckets == NULL) {
    free(ht);
    return NULL;
  }
  for (int i = 0; i < size; ++i) {
    ht->buckets[i] = NULL;
  }
  return ht;
}
void hash_table_destroy(hash_table *ht) {
  for (int i = 0; i < ht->size; ++i) {
    if (ht->buckets[i] != NULL) free(ht->buckets[i]);
  }
  free(ht->buckets);
  free(ht);
}

int hash_table_insert(hash_table *ht, Key key, Val val) {
  hash_node *node = (hash_node *)malloc(sizeof(hash_node));
  if (node == NULL) {
    return -1;
  }
  node->key = key;
  node->val = val;
  node->next = NULL;
  unsigned int index = hash_function(key, sizeof(key));
  index %= ht->size;
  hash_node *current = ht->buckets[index];
  if (current == NULL) {
    ht->buckets[index] = node;
    ht->count++;
  } else {
    while (current->next != NULL) {
      current = current->next;
    }
    if (strcmp(current->key, key) == 0) {
      current->val = val;
    } else {
      current->next = node;
      ht->count++;
    }
  }
  return 0;
}

void *hash_table_find(hash_table *ht, Key key) {
  unsigned int index = hash_function(key, sizeof(key));
  index %= ht->size;
  hash_node *node = ht->buckets[index];
  if (node == NULL) return NULL;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->val;
    }
    node = node->next;
  }
  return NULL;
}