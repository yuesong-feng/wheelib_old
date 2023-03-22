#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack stack;
struct stack {
  unsigned int size;
  void *base;
  void *top;
};

void stack_init_static(stack *stk, unsigned int size);

void stack_destroy_static(stack *stk);

stack *stack_init(unsigned int size);

void stack_destroy(stack *stk);

void *stack_top(stack *stk);

void *stack_push(stack *stk, unsigned int size);

void *stack_pop(stack *stk, unsigned int size);

unsigned int stack_size_used(stack *stk);

unsigned int stack_size_remain(stack *stk);

#endif
