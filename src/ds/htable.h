#ifndef _HTABLE_H_
#define _HTABLE_H_

typedef struct hnode{
    int key;
    void *val;
    struct hnode *next;
}hnode;

typedef struct htable{
    hnode **table;
    int size;
}htable;

hnode *hnode_init();
void hnode_destroy(hnode *hn);

htable *htable_init();
void htable_destroy(htable *ht);
void htable_insert(htable *ht, int key, void *val);
hnode *htable_find(htable *ht, int key);
void *htable_at(htable *ht, int key);

#endif
