#include "headers/dict.h"
#include "headers/llist.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct dict_element dictElement;

struct dict {
	lList* list;
};

struct dict_element{
	unsigned int hash;
	char const * key;
	char* value;
};

/* Simple hash function, should be rewritten to a better one later */
unsigned int hash_key(char const * key){

	unsigned int h = 0;
	for (int i=0; key[i] != '\0'; i++) {
		h += key[i]*7;
	}
	return h;
}


Dict* dict_new(void){
	Dict* dict = malloc(sizeof(Dict));
	dict->list = NULL;
	assert(dict != NULL);
	return dict;
}


/* it allocates the key and value */
void dict_add(Dict* dict, char const * key, char const * value){

	assert(dict != NULL);

	/* Creating the dict element */
	dictElement* new_el = malloc(sizeof(dictElement));
	char* key_str = malloc(sizeof(char) * (strlen(key)+1));
	char* value_str = malloc(sizeof(char) * (strlen(value)+1));

	assert(key_str != NULL);
	assert(value_str != NULL);
	strcpy(key_str, key);
	strcpy(value_str, value);

	new_el->key = key_str;
	new_el->hash = hash_key(key);
	new_el->value = value_str;

	/* Append it to the end of the list */
	llist_append(&(dict->list), new_el);
}


char* dict_get(Dict const * dict, char const * key){

	unsigned int hashed_key = hash_key(key);
	
	/* Go through the list */
	llNode* node = dict->list->head;	
	while (node != NULL){
		dictElement* el = node->data;

		/* Check if index and key corresponds */
		if ( hashed_key == el->hash && strcmp(key, el->key) == 0 ){
			return el->value;
		}

		node = node->next;
	}

	/* Else: return NULL */
	return NULL;
}


void dict_element_free(void* data){
	dictElement* dict_el = (dictElement*) data;

	/* Free content */
	free(dict_el->value);
	free((void *)(dict_el->key));

	/* Free dict_el itself */
	free(data);
}

void dict_free(Dict * dict){

	/* Free the list */
	llist_free(dict->list, dict_element_free);
	/* Free the dict itself */
	free(dict);
	
	return;
}


void dict_print(Dict const * dict){

	assert(dict != NULL);

	/* Loop through all the keys */
	size_t i=0;
	dictElement* dict_el;
	printf("{\n");
	while ((dict_el = llist_get(dict->list, i)) != NULL) {
		printf("\t\"%s\": \"%s\",\n", dict_el->key, dict_el->value);
		i++;
	}
	printf("}\n");

}


/* WARNING not sure it works well and without memory corruption */
void dict_snprint(Dict const* dict, size_t size, char* string){
	assert(size != 0);
	string[0] = '\0';

	/* Loop through all the keys */
	size_t bufsize = 20;
	char* buffer = malloc(bufsize);
	size_t i=0;
	dictElement* dict_el;
	strncat(string, "{\n", size-strlen(string));

	while ((dict_el = llist_get(dict->list, i)) != NULL) {
		/* Print each element */
		if ( snprintf(buffer, bufsize, "\t\"%s\": \"%s\",\n", dict_el->key, dict_el->value) >= (int) bufsize) {
			/* Append it to string */
			strncat(string, buffer, size-strlen(string));
			i++;
		} else {
			/* Resize buffer */
			bufsize *= 2;
			buffer = realloc(buffer, bufsize);
		}
	}

	strncat(string, "}\n", size-strlen(string));
	free(buffer);
}
