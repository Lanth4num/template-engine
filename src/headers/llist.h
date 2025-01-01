#ifndef INCLUDE_LLIST
#define INCLUDE_LLIST

#include <stdio.h>

typedef struct llNode llNode;
typedef struct lList lList;

struct lList{
	llNode* head;
	llNode* tail;
	size_t len;
};

struct llNode{
	void* data;
	llNode* next;
	llNode* prev;
};

llNode* llnode_new(void * data);
lList* llist_new(llNode*);
void* llist_get(lList const * list, size_t const index);
/* can be used as llist_new when used with NULL data size */
void llist_append(lList** list, void * data);
void* llist_pop(lList* list);
void llist_free(lList*, void (*free_function)(void*));

void llist_print(lList* list, void (*print_function)(void*));

#endif  // INCLUDE_LLIST
