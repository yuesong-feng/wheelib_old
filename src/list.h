#ifndef _LIST_H_
#define _LIST_H_

#define NULL ((void *)0)

#define LIST(TYPE)      \
  struct {              \
    unsigned int count; \
    TYPE *start;        \
    TYPE *end;          \
  }

#define LIST_NODE(TYPE) \
  struct {              \
    TYPE *prev;         \
    TYPE *next;         \
  }

#define LIST_INIT_STATIC \
  { 0, NULL, NULL }

#define LIST_INIT(list)  \
  do {                   \
    (list).count = 0;    \
    (list).start = NULL; \
    (list).end = NULL;   \
  } while (0)

#define LIST_NODE_INIT_STATIC \
  { NULL, NULL }

#define LIST_NODE_INIT(node) \
  do {                       \
    (node).prev = NULL;      \
    (node).next = NULL;      \
  } while (0)

#define LIST_ADD_TAIL(list, node, link)   \
  do {                                    \
    ++((list).count);                     \
    ((node)->link).prev = (list).end;     \
    ((node)->link).next = NULL;           \
    if ((list).end != NULL) {             \
      (((list).end)->link).next = (node); \
    }                                     \
    (list).end = (node);                  \
    if ((list).start == NULL) {           \
      (list).start = (node);              \
    }                                     \
  } while (0)

#define LIST_ADD_HEAD(list, node, link)     \
  do {                                      \
    ++((list).count);                       \
    ((node)->link).next = (list).start;     \
    ((node)->link).prev = NULL;             \
    if ((list).start != NULL) {             \
      (((list).start)->link).prev = (node); \
    }                                       \
    (list).start = (node);                  \
    if ((list).end == NULL) {               \
      (list).end = (node);                  \
    }                                       \
  } while (0)

#define LIST_FOR_EACH(node, link, list) \
  for ((node) = (list).start; (node) != NULL; (node) = ((node)->link).next)

#endif
