#include "skiplist.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

// 分配一个Node，next指针的层数为height
inline static Node *NewNode(Key key, int height) {
  Node *node = (Node *)malloc(sizeof(Node) + (height - 1) * sizeof(Node *));
  if (node == NULL) return NULL;
  node->key = key;
  return node;
}

// 找到大于或等于key的第一个节点，如果prev不为空则记录遍历路径的前一层节点
inline static Node *FindGreaterOrEqual(SkipList *sl, Key key, Node **prev) {
  Node *x = sl->head;
  int level = sl->height - 1;  // 当前level，从0开始，所以最开始是sl->height - 1
  while (true) {
    Node *next = x->next[level];  // 当前level的下一个节点
    if ((next != NULL) && sl->cmp(next->key, key) < 0) {
      // 下一个节点key比查找的key小，则直接走到下一个节点
      x = next;
    } else {
      if (prev != NULL) prev[level] = x;  // 记录该层遍历到的节点
      // 下一个节点是NULL，或者下一个节点key大于等于查找的key，则向下走一个level
      if (level == 0)
        return next;
      else
        level--;
    }
  }
}

// 新节点的层数随机
inline static int RandomHeight() {
  static const unsigned int prob = 4;
  int height = 1;
  srand((unsigned)time(NULL));
  while (height < MAX_HEIGHT && rand() % prob == 0) {
    // 1/prob 的概率增加一层
    height++;
  }
  assert(height > 0);
  assert(height <= MAX_HEIGHT);
  return height;
}

SkipList *SkipList_init(Comparator cmp) {
  SkipList *sl = (SkipList *)malloc(sizeof(SkipList));
  if (sl == NULL) {
    return NULL;
  }
  sl->cmp = cmp;
  sl->height = 1;
  // 初始化头节点，头节点level数为MAX_HEIGHT
  sl->head = NewNode((Key)0, MAX_HEIGHT);
  if (sl->head == NULL) {
    free(sl);
    return NULL;
  }
  for (int i = 0; i < MAX_HEIGHT; ++i) {
    sl->head->next[i] = NULL;
  }
  return sl;
}

void SkipList_destroy(SkipList *sl) {
  Node *x = sl->head;
  while (x != NULL) {
    Node *next = x->next[0];
    free(x);
    x = next;
  }
  free(sl);
}

int SkipList_insert(SkipList *sl, Key key) {
  Node *prev[MAX_HEIGHT];
  // 找到大于或等于key的第一个节点，并记录遍历路径中每层上一个节点
  Node *x = FindGreaterOrEqual(sl, key, prev);
  // 跳表不允许存储两个相同的key
  assert(x == NULL || sl->cmp(key, x->key) != 0);
  // 新节点的高度随机，1/4的概率会增加一层
  int height = RandomHeight();
  // 层数大于当前跳表的最高level
  if (height > sl->height) {
    for (int i = sl->height; i < height; ++i) {
      prev[i] = sl->head;
    }
    sl->height = height;
  }
  x = NewNode(key, height);
  if (x == NULL) {
    return -1;
  }
  for (int i = 0; i < height; ++i) {
    x->next[i] = prev[i]->next[i];
    prev[i]->next[i] = x;
  }
  return 0;
}

bool SkipList_contains(SkipList *sl, Key key) {
  // 找到key大于或等于当前key的下一个节点
  Node *x = FindGreaterOrEqual(sl, key, NULL);
  if (x != NULL && sl->cmp(key, x->key) == 0)
    return true;
  else
    return false;
}
