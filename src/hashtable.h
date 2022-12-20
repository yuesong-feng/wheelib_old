#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stddef.h>

typedef void *Key;
typedef void *Val;

typedef struct hash_node {
  Key key;
  Val val;
  struct hash_node *next;  // 该哈希桶中下一个节点

} hash_node;

typedef struct hash_table {
  hash_node **buckets;  // 数组，每一个元素是hash_node的指针
  size_t size;          // 桶数组的大小
  size_t count;         // 哈希表中元素个数
} hash_table;

hash_table *hash_table_init(size_t size);
void hash_table_destroy(hash_table *ht);
int hash_table_insert(hash_table *ht, Key key, Val val);
void *hash_table_find(hash_table *ht, Key key);

#endif
