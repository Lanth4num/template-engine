#ifndef INCLUDE_LEXER
#define INCLUDE_LEXER

#include "llist.h"
#include <stdbool.h>

typedef struct Token Token;

typedef enum{
	TEXT,
	/* for varialbes */
	IDENTIFIER,
	START_ID_BLOCK,
	END_ID_BLOCK,
	/* About conditions */
	START_CONDITION_BLOCK,	/* {% */
	END_CONDITION_BLOCK,		/* %} */
	IF,
	ELSE,
	END_IF,
}token_type;

struct Token{
	token_type type;
	char* value;
};


/* function definitions */
Token* token_new(token_type, char const * literal);
bool token_cmp(Token const *, Token const *);
void token_print_wrapper(void* token);
void token_print(Token*);
lList* tokenize(FILE* file_stream);

#endif  // INCLUDE_LEXER


