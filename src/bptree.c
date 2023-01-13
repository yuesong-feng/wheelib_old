#include "bptree.h"

#include <assert.h>
#include <stdlib.h>

static inline int max_keys(int degree) { return degree * 2 - 1; }
static inline int min_keys(int degree) { return degree - 1; }
static inline int max_ptrs(int degree) { return degree * 2; }
static inline int min_ptrs(int degree) { return degree; }

// 在某个leaf节点中插入key val
static int BPNode_insert_leaf(BPNode *node, Key key, Val val) {
  assert(node->leaf == true);
  int i = node->keys_len;
  if (i == 0) {
    node->keys[0] = key;
    node->ptrs.vals[0] = val;
    node->keys_len++;
    node->ptrs_len++;
    return 0;
  }
  


  return 0;
}

BPNode *BPNode_init(int degree, Comparator cmp, bool leaf) {
  BPNode *node = (BPNode *)malloc(sizeof(BPNode));
  if (node == NULL) return NULL;
  node->degree = degree;
  node->cmp = cmp;
  node->leaf = leaf;
  node->keys = (Key *)malloc(sizeof(Key) * max_keys(degree));
  if (node->keys == NULL) {
    free(node);
    return NULL;
  }
  for (int i = 0; i < max_keys(degree); ++i) {
    node->keys[i] = NULL;
  }
  if (leaf) {
    node->ptrs.vals = (Val *)malloc(sizeof(Val) * max_ptrs(degree));
    if (node->ptrs.vals == NULL) {
      free(node->keys);
      free(node);
      return NULL;
    }
    for (int i = 0; i < max_ptrs(degree); ++i) {
      node->ptrs.vals[i] = (Val)0;
    }
  } else {
    node->ptrs.nodes = (BPNode **)malloc(sizeof(BPNode *) * max_ptrs(degree));
    if (node->ptrs.nodes == NULL) {
      free(node->keys);
      free(node);
      return NULL;
    }
    for (int i = 0; i < max_ptrs(degree); ++i) {
      node->ptrs.nodes[i] = NULL;
    }
  }
  node->keys_len = 0;
  node->ptrs_len = 0;
  node->next = NULL;
  return node;
}

void BPNode_destroy(BPNode *node) {
  if (node->leaf) {
    free(node->ptrs.vals);
  } else {
    free(node->ptrs.nodes);
  }
  free(node->keys);
  free(node);
}

BPTree *BPTree_init(int degree, Comparator cmp) {
  BPTree *tree = (BPTree *)malloc(sizeof(BPTree));
  if (tree == NULL) return NULL;
  tree->degree = degree;
  tree->cmp = cmp;
  tree->root = NULL;
  return tree;
}
void BPTree_destroy(BPTree *tree) {
  BPNode *node = tree->root;
  while (node->leaf == false) {
    BPNode *down = node->ptrs.nodes[0];
    while (node != NULL) {
      BPNode *next = node->next;
      BPNode_destroy(node);
      node = next;
    }
    node = down;
  }
  assert(node->leaf == true);
  while (node != NULL) {
    BPNode *next = node->next;
    BPNode_destroy(node);
    node = next;
  }
}
int BPTree_insert(BPTree *tree, Key key, Val val) {
  if (key == (Key)0) {
    return -1;
  }
  if (tree->root == NULL) {
    tree->root = BPNode_init(tree->degree, tree->cmp, true);
    if (tree->root == NULL) return -1;
    return BPNode_insert_leaf(tree->root, key, val);
  } else {
    return -1;
  }
  return 0;
}
