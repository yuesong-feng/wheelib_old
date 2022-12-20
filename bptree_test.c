#include "bptree.h"

#include <stdio.h>

#include "comparator.h"

int main() {
  int degree = 4;
  BPTree *tree = BPTree_init(degree, cmp_str);
  BPTree_insert(tree, "yue", NULL);
  BPTree_insert(tree, "song", NULL);
  BPTree_insert(tree, "feng", NULL);
  BPTree_insert(tree, "str123", NULL);
  BPTree_insert(tree, "str1", NULL);
  BPTree_insert(tree, "str84", NULL);

  BPNode *node = tree->root;
  while (node->leaf == false) {
    node = node->ptrs.nodes[0];
  }
  while (node != NULL) {
    for (int i = 0; i < node->keys_len; ++i) {
      printf("%s\n", (char *)node->keys[i]);
    }
    node = node->next;
  }

  BPTree_destroy(tree);
  return 0;
}