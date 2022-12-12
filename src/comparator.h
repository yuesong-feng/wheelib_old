#ifndef COMPARATOR_H
#define COMPARATOR_H
#include <stddef.h>

int cmp_str(void *str1, void *str2);
int cmp_str_with_len(void *str1, size_t len1, void *str2, size_t len2);
int cmp_int(void *int1, void *int2);

#endif
