#include "headers/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

char fpeek(FILE* stream){
	assert(stream != NULL);
	int c;
	c = getc(stream);
	ungetc(c, stream);	
	return c;
}

void skip_spaces(FILE* stream){
	assert(stream != NULL);
	int c = fpeek(stream);
	while(isvalid_space(c) && c != EOF){
		getc(stream);
		c = fpeek(stream);
	}
	return;
}

bool isvalid_space(char c){
	if (c == ' ' || c == '\t') return true;
	return false;
}

bool isvalid_alpha(char c){
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= 'a' && c <= 'z') return true;
	return false;
}

bool isvalid_variable_char(char c){
	if ( isvalid_alpha(c) || c == '_' || c=='-' ){
		return true;
	}
	return false;
}

void str_print(void* str){
	printf("%s", (char*) str);
}

void int_print(void* integer){
	printf("%d", *(int*) integer);
}

void float_print(void* float_number){
	printf("%f", *(float*) float_number);
}


