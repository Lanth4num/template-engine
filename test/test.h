#ifndef INCLUDE_TEST
#define INCLUDE_TEST

#include "../src/headers/lexer.h"
#include "../src/headers/llist.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

void dict_test(void);
void llist_test(void);
void tokencmp_test(void);
void tokenize_test(void);
void template_test(void);

#endif  // INCLUDE_TEST


