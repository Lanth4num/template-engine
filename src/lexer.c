#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "headers/lexer.h"
#include "headers/llist.h"
#include "headers/utils.h"

void token_print_wrapper(void* token){
	token_print((Token*) token);
	return;
}

void token_print(Token* token){

	int len = strlen(token->value);
	switch (token->type) {
		case START_ID_BLOCK:	
			printf("ID_START");
			break;
		case END_ID_BLOCK:
			printf("ID_END");
			break;
		case TEXT:
			printf("TEXT: ");
			if (len > 20) printf("\"%.10s...(%d)\"", token->value, len);
			else printf("\"%s\"", token->value);
			break;
		case IDENTIFIER:
			printf("ID: \"%s\"", token->value);
			break;
		default:
			printf("Not yet handled");
	}

	return;
}


Token* token_new(token_type type, char const * literal){
	Token* token = (Token*) malloc(sizeof(Token));
	assert(token != NULL);

	token->type = type;

	/* Copy string and bind it to Token */
	char* str = (char*) calloc( (strlen(literal)+1), sizeof(char) );
	assert(token != NULL);
	strcpy(str, literal); 
	token->value = str;

	return token;
}


bool token_cmp(Token const * token1, Token const * token2){
	/* Returns false if one of the token or both are NULL */
	if (token1 == NULL || token2 == NULL) return false;

	/* Compare types */
	if (token1->type != token2->type) return false;

	/* Compare value strings */
	if (strcmp(token1->value, token2->value) != 0 ) return false;

	return true;

}


lList* tokenize(FILE* file){
	assert(file!= NULL);

	lList* list = NULL;

	/* Keep track of condition block */
	// bool is_in_condition_block = false;
	bool is_in_variable_block = false;

	/* Loop through the string */
	int c;
	skip_spaces(file);

	while ((c = getc(file)) != EOF) {

		Token* token;

		/* For variables */
		if (c == '{' && fpeek(file) == '{'){
			/* resets the buffer */
			is_in_variable_block = true;
			getc(file);
			token = token_new(START_ID_BLOCK, "{{");
			llist_append(&list, token, sizeof(Token));
		}

		else if (c == '}' && fpeek(file) == '}'){
			is_in_variable_block = false;
			getc(file);

			token = token_new(END_ID_BLOCK, "}}");
			llist_append(&list, token, sizeof(Token));

			/* Do not skip spaces after this one */
			continue;
		}

		else if (is_in_variable_block){
			/* Get the variable */
			char buffer[100];
			size_t ptr = 0;

			do {
				buffer[ptr] = c;
				ptr += 1;
			} while ( !isvalid_space(c = getc(file)) && ptr < 100-1);
			ungetc(c, file);

			buffer[ptr] = '\0';

			token = token_new(IDENTIFIER, buffer);
			llist_append(&list, token, sizeof(Token));
		}

		/* For TEXT */
		else{
			char buffer[1024];
			size_t buf_ptr = 0;
			do {
				buffer[buf_ptr] = c;
				buf_ptr += 1;
				c = getc(file);
			} while(c!=EOF && c!='{' && c!='}' && buf_ptr < 1023);
			ungetc(c, file);
			buffer[buf_ptr] = '\0';

			token = token_new(TEXT, buffer);
			llist_append(&list, token, sizeof(Token));
			/* Do not skip spaces after text */
			continue;
		}

		token_free(token);
		skip_spaces(file);
	}

	return list;
}


void token_free(Token* token){
	free(token->value);
	free(token);
	return;
}

void token_free_wrapper(void* ptr){
	token_free((Token*) ptr);
	return;
}

