#ifndef _LIST_H_
#define _LIST_H_

typedef struct listnode {
  void *val;
  struct listnode *next;
  struct listnode *prev;
} listnode;

typedef struct list {
  listnode *head;
  int size;
} list;

/*
 * State structs for various looping macros below.
 */
typedef struct ForEachState
{
	const list *l;				/* list we're looping through */
	int			i;				/* current element index */
} ForEachState;

#define foreach(cell, lst)	\
	for (ForEachState cell##__state = {(lst), 0}; \
		 (cell##__state.l != NIL && \
		  cell##__state.i < cell##__state.l->length) ? \
		 (cell = &cell##__state.l->elements[cell##__state.i], true) : \
		 (cell = NULL, false); \
		 cell##__state.i++)

list *list_init();
void list_destroy(list *l);
int list_empty(list *l);
void list_push_back(list *l, void *val);
void list_push_front(list *l, void *val);
void list_pop_back(list *l);
void list_pop_front(list *l);
void *list_back(list *l);
void *list_front(list *l);
int list_size(list *l);

#endif