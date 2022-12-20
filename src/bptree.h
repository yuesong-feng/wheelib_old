#ifndef BPTREE_H
#define BPTREE_H
#include <stdbool.h>

typedef void *Key;
typedef void *Val;

typedef int (*Comparator)(void *, void *);

// degree == 2, for example, will create a 2-3-4 tree (each node contains 1-3 keys
// and 2-4 ptrs).
typedef struct BPNode {
  int degree;
  Comparator cmp;
  bool leaf;
  Key *keys;
  int keys_len;
  union {
    struct BPNode **nodes;
    Val *vals;
  } ptrs;
  int ptrs_len;
  struct BPNode *next;
} BPNode;

typedef struct BPTree {
  BPNode *root;
  int degree;
  Comparator cmp;
} BPTree;

BPNode *BPNode_init(int degree, Comparator cmp, bool leaf);
void BPNode_destroy(BPNode *node);

BPTree *BPTree_init(int degree, Comparator cmp);
void BPTree_destroy(BPTree *tree);
int BPTree_insert(BPTree *tree, Key key, Val val);

#endif