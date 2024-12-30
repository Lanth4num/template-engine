#include "test.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

	// dict_test();
	// llist_test();
	// tokencmp_test();
	tokenize_test();
	// template_test();

	printf(ANSI_COLOR_GREEN "Test passed!\n" ANSI_COLOR_RESET);
	return 0;
}
