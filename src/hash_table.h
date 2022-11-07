#ifndef _HASH_TABLE_
#define _HASH_TABLE_
typedef struct {
	char* key;
	char* value;
} ht_item;

typedef struct {
	int size;
	int count;
	ht_item** items;
} ht_hash_table;

static ht_item *ht_new_item(const char* k, const char* v) ;

ht_hash_table* ht_new() ;

static void ht_del_item(ht_item* i) ;

void ht_del_hash_table(ht_hash_table *ht) ;


#endif
