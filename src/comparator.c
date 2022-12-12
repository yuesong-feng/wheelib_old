#include "comparator.h"

#include "string.h"

int cmp_str(void *str1, void *str2) {
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);
  return cmp_str_with_len(str1, len1, str2, len2);
}
int cmp_str_with_len(void *str1, size_t len1, void *str2, size_t len2) {
  size_t min_len = len1 < len2 ? len1 : len2;
  int ret = memcmp(str1, str2, min_len);
  if (ret == 0) {
    if (len1 < len2)
      ret = -1;
    else if (len1 > len2)
      ret = +1;
  }
  return ret;
}
int cmp_int(void *int1, void *int2) {
  int num1 = *(int *)int1;
  int num2 = *(int *)int2;
  if (num1 < num2)
    return -1;
  else if (num1 > num2)
    return +1;
  else
    return 0;
}
