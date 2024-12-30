#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "test.h"
// #include "../src/headers/lexer.h"
#include "../src/headers/dict.h"
#include "../src/headers/template.h"



void template_test(void){
	Dict* dict = dict_new();
	dict_add(dict, "name", "Adrien");
	dict_add(dict, "age", "17");

	FILE* stream = fopen("/home/adrien/Documents/Projects/template-engine/bin/test.txt", "r");
	assert(stream != NULL);
	lList* token_list = tokenize(stream);
	fclose(stream);
	// llist_print(token_list, token_print_wrapper);

	char* response = apply_template(token_list, dict); 
	// printf("Got:\n%s\n", response);

	free(response);
}


void dict_test(void){

	printf(ANSI_COLOR_YELLOW "Testing dictionaries!\n" ANSI_COLOR_RESET);

	Dict* new_dict = dict_new();
	dict_add(new_dict, "name", "Adrien");
	dict_add(new_dict, "age", "17");
	dict_add(new_dict, "classe", "TE");

	// dict_print(new_dict);
	// printf(
	// 			"nom: %s\n"
	// 			"age: %s\n"
	// 			"classe: %s\n",
	// 			dict_get(new_dict, "name"),
	// 			dict_get(new_dict, "age"),
	// 			dict_get(new_dict, "classe")
	// );

	dict_free(new_dict);
	new_dict = NULL;
}

void tokenize_test(void){

	printf(ANSI_COLOR_YELLOW "Testing tokenazation!\n" ANSI_COLOR_RESET);

	/* Testing block, text and variables */
	// char input1[] = "" ;
	// char input2[] = "{{ name }}  test";
	// char input3[] = "{{ { }} }} {  "; // expect : START TEXT END END TEXT
	// char input4[] = "     This is text     ";
	// char input5[] = "   This is text    {{ as_well_as_a_variable some_crap }}   ";

	// FILE* stream = fopen("/home/adrien/Documents/Projects/template-engine/bin/test.txt", "r");
	// printf("Error: %s\n", strerror(errno));
	// assert(stream != NULL);
	// lList* list = tokenize(stream);
	// fclose(stream);
	// llist_print(list, token_print_wrapper);
	
	/* Free */
	// llist_free(list, token_free_wrapper);
	// list = NULL;
	

	lList* list;
	llist_append(&list, token_new(TEXT, "THIS IS A TEXT"), sizeof(Token*));
	llist_free(list, token_free_wrapper);

}

void tokencmp_test(void){
	
	printf(ANSI_COLOR_YELLOW "Testing token_cmp!\n" ANSI_COLOR_RESET);

	assert(
		token_cmp(token_new(TEXT, "Hello"), token_new(TEXT, "Hello")) == true
	);
	assert(
		token_cmp(token_new(IDENTIFIER, "x"), token_new(TEXT, "x")) == false 
	);
	assert(
		token_cmp(token_new(TEXT, "Hello"), token_new(TEXT, "Hell")) == false 
	);
	assert(
		token_cmp(NULL, NULL) == false
	);

	return;
}


/* Linked lists test */
void llist_test(void){
	int one = 1;
	int two = 2;
	lList* list = NULL;

	printf(ANSI_COLOR_YELLOW "Testing linked Lists!\n" ANSI_COLOR_RESET);

	llist_append(&list, &one, sizeof(int)); // creating the list

	assert(list != NULL);
	assert(list->len == 1);
	assert(list->tail != NULL);
	assert(list->head != NULL);
	assert( * ((int *)llist_get(list, 0)) == 1 );
	assert( llist_get(list, 1) == NULL);
	assert(*(int *)(list->head->data) == 1);
	assert(*(int *)(list->tail->data) == 1);

	llist_append(&list, &two, sizeof(int));

	assert(list != NULL);
	assert(list->len == 2);
	assert(list->tail != NULL);
	assert(list->head != NULL);
	assert( *(int *)llist_get(list, 0) == 1 );
	assert( *(int *)llist_get(list, 1) == 2 );
	assert( llist_get(list, 2) == NULL);
	assert(*(int *)(list->tail->data) == 2);
	assert(*(int *)(list->head->data) == 1);

	int popped_value = *(int *) llist_pop(list);

	assert(list != NULL);
	assert(list->len == 1);
	assert(list->tail != NULL);
	assert(list->head != NULL);
	assert( *(int *)llist_get(list, 0) == 1 );
	assert( llist_get(list, 1) == NULL);
	assert(*(int *)(list->head->data) == 1);
	assert(*(int *)(list->tail->data) == 1);
	assert(popped_value == 2);

	popped_value = *(int *) llist_pop(list);

	assert(list != NULL);
	assert(list->len == 0);
	assert(list->tail == NULL);
	assert(list->head == NULL);
	assert(popped_value == 1);
	assert( llist_get(list, 1) == NULL);
	assert( llist_get(list, 0) == NULL);

	return;
}


