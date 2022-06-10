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
	assert(0 > strcmp("ab", "ac"));
	assert(0 < strcmp("abcd", "ABCD"));
}

//
void test_strcpy()
{
	char result[64];

	puts("Testing strcpy()\n");

	strcpy(result, "Hello!");
	assert(0 == strcmp(result, "Hello!"));
}

//
void test_strcat()
{
	char result[64] = "Hello ";

	puts("Testing strcat()\n");

	assert(0 == strcmp("Hello World!", strcat(result, "World!")));
}

//
int main(int argc, char *argv[])
{
	puts("Starting tests.\n");

	test_strlen();
	test_strcmp();
	test_strcpy();
	test_strcat();

	puts("Finished tests.\n");
}