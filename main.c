#include "string.h"
#include "assert.h"
#include "stdio.h"

//
void test_strlen()
{
	assert(strlen("Hello") == 4);
	assert(strlen("") == 0);
}

//
int main(int argc, char *argv[])
{
	puts("Starting tests\n");

	test_strlen();
}