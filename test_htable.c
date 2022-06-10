#include <stdio.h>
#include <stdlib.h>

#include "src/ds/htable.h"

int main() {
  htable *ht = htable_init();
  int *arr = (int *)malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; ++i) {
    arr[i] = i;
  }
  htable_insert(ht, 1, &arr[3]);
  htable_insert(ht, 2, &arr[4]);
  htable_insert(ht, 3, &arr[5]);

  void *val = htable_at(ht, 1);
  if (val != NULL) {
    printf("%d\n", *(int *)val);
  }
  void *val2 = htable_at(ht, 2);
  if (val2 != NULL) {
    printf("%d\n", *(int *)val2);
  }
  void *val3 = htable_at(ht, 3);
  if (val3 != NULL) {
    printf("%d\n", *(int *)val3);
  }
  htable_insert(ht, 2, &arr[5]);
  htable_destroy(ht);
  return 0;
}