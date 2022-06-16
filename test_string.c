#include "stdio.h"
#include "string.h"
#include "test.h"

//
static void test_strlen()
{
	puts("\nTesting strlen()\n");

	TEST(strlen("Hello") == 5);
	TEST(strlen("") == 0);
}

//
static void test_memcpy()
{
	puts("\nTesting memcmp()\n");

}

//
static void test_strcmp()
{
	puts("\nTesting strcmp()\n");

	TEST(0 == strcmp("same", "same"));
	TEST(0 > strcmp("ab", "ac"));
	TEST(0 < strcmp("abcd", "ABCD"));
}

//
static void test_strcpy()
{
	char result[64] = "";

	puts("\nTesting strcpy()\n");

	TEST(0 == strcmp(strcpy(result, "Hello!"), "Hello!"));
}

//
static void test_strcat()
{
	char result[64] = "Hello ";

	puts("\nTesting strcat()\n");

	TEST(0 == strcmp("Hello World!", strcat(result, "World!")));
}

//
void test_string()
{
	test_strlen();
	test_strcmp();
	test_strcpy();
	test_strcat();
}
