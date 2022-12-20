#include <stdio.h>
#include <string.h>

#include "hashtable.h"

int main() {
  hash_table *ht = hash_table_init(8);

  hash_table_insert(ht, "key1", "val1");
  hash_table_insert(ht, "key2", "val2");
  hash_table_insert(ht, "key3", "val3");
  hash_table_insert(ht, "key4", "val4");
  hash_table_insert(ht, "key5", "val5");
  hash_table_insert(ht, "key5", "change");

  printf("%s\n", (char *)hash_table_find(ht, "key1"));
  printf("%s\n", (char *)hash_table_find(ht, "key4"));
  printf("%s\n", (char *)hash_table_find(ht, "key2"));
  printf("%s\n", (char *)hash_table_find(ht, "key3"));
  printf("%s\n", (char *)hash_table_find(ht, "key5"));

  printf("%lu\n", ht->count);

  hash_table_destroy(ht);
}
