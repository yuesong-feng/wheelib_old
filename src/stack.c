#include "stack.h"

#include <assert.h>
#include <stdlib.h>

void stack_init_static(stack *stk, unsigned int size) {
  stk->size = size;
  stk->base = malloc(stk->size);
  stk->top = stk->base + stk->size;
}

stack *stack_init(unsigned int size) {
  stack *stk = malloc(sizeof(stack));
  if (stk == NULL) return NULL;
  stk->size = size;
  stk->base = malloc(stk->size);
  stk->top = stk->base + stk->size;
  return stk;
}

void stack_destroy_static(stack *stk) {
  stk->size = 0;
  free(stk->base);
  stk->base = NULL;
  stk->top = NULL;
}

void stack_destroy(stack *stk) {
  free(stk->base);
  free(stk);
}

void *stack_top(stack *stk) { return stk->top; }

void *stack_push(stack *stk, unsigned int size) {
  assert(stk->base + size <= stk->top);
  stk->top -= size;
  return stk->top;
}

void *stack_pop(stack *stk, unsigned int size) {
  assert(stk->top + size <= stk->base + stk->size);
  void *ret = stk->top;
  stk->top += size;
  return ret;
}