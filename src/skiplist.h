#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <stdbool.h>

#define MAX_HEIGHT 12  // 跳表最高level
typedef void *Key;     // 跳表中Key的类型
typedef int (*Comparator)(void *, void *);

typedef struct Node {
  Key key;
  // 指向下一个key，长度是该节点的level，next[0]是最底层链表的指针
  // 从next[1]开始需要另外分配内存，sizeof(Node) + sizeof(Node *) * (height - 1)
  // struct Node *next[1];
  struct Node * next[1];
} Node;

typedef struct SkipList {
  Comparator cmp;  // Key的比较器
  int height;      // 跳表最高节电的高度，也是头节点的高度
  Node *head;      // 头节点
} SkipList;

SkipList *SkipList_init(Comparator cmp);
void SkipList_destroy(SkipList *sl);
int SkipList_insert(SkipList *sl, Key key);
bool SkipList_contains(SkipList *sl, Key key);

#endif