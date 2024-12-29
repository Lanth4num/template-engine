#ifndef INCLUDE_TEMPLATE
#define INCLUDE_TEMPLATE

#include "lexer.h"
#include "dict.h"

/* Returns the string with replaced value */
char* apply_template(lList* token_list, Dict* dict); 

#endif  // INCLUDE_TEMPLATE
