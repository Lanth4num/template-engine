#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h>

/* stream related */
char fpeek(FILE*);
void skip_spaces(FILE* stream);

/* character checking related */
bool isvalid_space(char);
bool isvalid_alpha(char);
bool isvalid_variable_char(char);

/* printing related */
void str_print(void* str);
void int_print(void* integer);
void float_print(void* float_number);

#endif  // UTILS
