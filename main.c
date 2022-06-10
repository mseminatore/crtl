#include "string.h"
#include "assert.h"
#include "stdio.h"

//
void test_strlen()
{
	puts("Testing strlen()\n");

	assert(strlen("Hello") == 5);
	assert(strlen("") == 0);
}

//
void test_memcpy()
{
	puts("Testing memcmp()\n");

}

//
void test_strcmp()
{
	puts("Testing strcmp()\n");

	assert(0 == strcmp("same", "same"));
}

//
int main(int argc, char *argv[])
{
	puts("Starting tests.\n");

	test_strlen();
	test_strcmp();

	puts("Finished tests.\n");
}