#include "skiplist.h"
#include "comparator.h"
#include <stdio.h>

int main() {
  SkipList *sl = SkipList_init(cmp_str);
  SkipList_insert(sl, "yue");
  SkipList_insert(sl, "song");
  SkipList_insert(sl, "feng");
  SkipList_insert(sl, "str123");
  SkipList_insert(sl, "str1");
  SkipList_insert(sl, "str84");
  bool c1 = SkipList_contains(sl, "feng");
  Node *x = sl->head;
  printf("%d\n", c1);
  while (x != NULL) {
    printf("%s\n", (const char *)x->key);
    x = x->next[0];
  }
  SkipList_destroy(sl);

  SkipList *sl2 = SkipList_init(cmp_int);
  int arr[10] = {9, 2, 4, 3, 10, 8, 6, 7, 5, 1};
  for (int i = 0; i < 10; ++i) {
    SkipList_insert(sl2, arr + i);
  }
  x = sl2->head->next[0];
  while (x != NULL) {
    printf("%d\n", *(int *)x->key);
    x = x->next[0];
  }
  SkipList_destroy(sl2);
  return 0;
}
