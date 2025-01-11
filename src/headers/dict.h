#ifndef INCLUDE_DICT
#define INCLUDE_DICT

#include "llist.h"
typedef struct dict Dict;

// creates new dict if NULL provided as first arg
Dict* dict_new(void);
void dict_add(Dict*, char const * key, char const * value);
char* dict_get(Dict const *, char const * key);
void dict_print(Dict const *);
void dict_free(Dict *);
void dict_snprint(Dict const* dict, size_t size, char* string);

#endif  // INCLUDE_DICT
