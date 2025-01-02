#include "headers/llist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

llNode* llnode_new(void * data){
	
	/* Creating node */
	llNode* new_node = (llNode*) malloc(sizeof(llNode));
	assert(new_node != NULL);

	/* Adding the pointer to the node (doesn't allocate memory) */
	new_node->data = data; 

	/* Returning node */
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}


/* put the data at the end of the list */
void llist_append(lList** list, void * data){
	assert(list != NULL);
	/* Creating new node with corresponding data */
	llNode* new_node = llnode_new(data);

	/* Set head to new node if NULL provided and return*/
	if (*list == NULL){
		/* Creating the new list */
		lList* new_list = (lList*) malloc(sizeof(lList)); 
		assert(new_list != NULL);
		new_list->head = new_node;
		new_list->tail = new_node;
		new_list->len = 1;

		/* Assigning it to list from args */
		*list = new_list;

		/* Returning */
		return;
	}

	/* Adding it to the end of the list */
	new_node->prev = (*list)->tail;
	(*list)->tail->next = new_node;

	/* Updating len and tail */
	(*list)->len += 1;
	(*list)->tail = new_node;

	/* Returning */
	return;
}


/* Returns the data of the node or NULL on out of range */
void* llist_get(lList const * list, size_t const index){

	if (list == NULL) return NULL;

	/* Go to the indexth node */
	llNode const * ptr = list->head; 
	size_t i;
	for (i=0; i<index && ptr!=NULL; i++) {
		ptr = ptr->next;
	}

	/* Out of range case */
	if (ptr == NULL) return NULL;

	/* Return data of ith node */
	return ptr->data;
}


/* Detaches last element and returns it */
/* NOTE: Doesn't free space */
void* llist_pop(lList* list){

	assert(list != NULL);

	if (list->len <= 0) { /* Trying to pop empty list */
		return NULL;
	} 
	

	/* Saves data for return and node to free it */
	void *data = list->tail->data;
	llNode* old_tail = list->tail;

	/* Update tail to the previous node if it exists */
	if ( list->tail->prev != NULL ){
		list->tail = list->tail->prev;
	}
	list->tail->next = NULL;
	list->len -= 1;

	/* If the list is now empty, sets head and tail to NULL */
	if (list->len == 0){
		list->tail = NULL;
		list->head = NULL;
	}

	/* Free the node, but not data */
	free(old_tail);

	/* Returns the last element */
	return data;
}


void llist_free(lList* list, void (*free_function)(void*)){
	
	llNode* node = list->head; 
	/* Loop through all elements */
	while( node != NULL){

		llNode* next = node->next;

		/* Call free function on them */
		if (free_function != NULL){
			free_function(node->data);
			node->data = NULL;
		}

		/* Free the node itself */
		free(node);

		node = next;
	}

	/* Free the list itself */
	free(list);
}


void llist_print(lList* list, void (*print_function)(void*)){
	size_t len = list->len;
	size_t index = 0;

	printf("[\n");
	while (index < len){
		void* data = llist_get(list, index);
		assert(data != NULL);
		print_function(data);
		printf(",\n");
		index += 1;
	}
	printf("]\n");

	return;
}
