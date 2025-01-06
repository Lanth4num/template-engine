#include "headers/template.h"
#include "headers/dict.h"
#include "headers/lexer.h"

#include <stdlib.h>
#include <string.h>

char* apply_template(lList* token_list, Dict* dict){

	llNode* node = token_list->head; 

	size_t max_buf = 1024;
	char* buffer = calloc( max_buf, sizeof(char) );
	size_t buf_size = 1;

	/* Go through the list */
	while (node != NULL) {

		Token* token = (Token *) node->data;
		token_type type = token->type;

		/* Concat if text */
		if ( type == TEXT ){
			buf_size += strlen(token->value);

			/* Make buffer larger */
			if (buf_size >= max_buf) {
				max_buf *= 2;
				buffer = realloc( buffer, max_buf);
			}

			strcat(buffer, token->value);
		} 

		/* Check for variable and replace them */
		else if ( type == IDENTIFIER ){
			char* variable = dict_get(dict, token->value); 
			if (variable == NULL) continue;

			/* Make buffer larger if needed */
			buf_size += strlen(token->value);
			if (buf_size >= max_buf) {
				max_buf *= 2;
				buffer = realloc( buffer, max_buf);
			}

			strcat(buffer, variable);
		}

		node = node->next;
	}


	/* Return the buffer */
	return buffer;
}
