#include <stdio.h>

#include "comparator.h"

int main() {
  int a = 3, b = 2;
  int cmp1 = cmp_int(&a, &b);

  const char* str1 = "abc";
  const char* str2 = "abcd";
  int cmp2 = cmp_str((void*)str1, (void*)str2);

  printf("%d %d\n", cmp1, cmp2);
  return 0;
}
