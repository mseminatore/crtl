// Copyright 2022 Mark Seminatore. All rights reserved.
#include "string.h"
#include "assert.h"
#include "stdio.h"

static int testnum = 1;

// simple test harness
#define TEST(s) puts("Testing that: " ## #s ## "\n"); assert(#s)

//
void test_strlen()
{
	puts("\nTesting strlen()\n");

	TEST(strlen("Hello") == 5);
	TEST(strlen("") == 0);
}

//
void test_memcpy()
{
	puts("\nTesting memcmp()\n");

}

//
void test_strcmp()
{
	puts("\nTesting strcmp()\n");

	TEST(0 == strcmp("same", "same"));
	TEST(0 > strcmp("ab", "ac"));
	TEST(0 < strcmp("abcd", "ABCD"));
}

//
void test_strcpy()
{
	char result[64];

	puts("\nTesting strcpy()\n");

	TEST(0 == strcmp(strcpy(result, "Hello!"), "Hello!"));
}

//
void test_strcat()
{
	char result[64] = "Hello ";

	puts("\nTesting strcat()\n");

	TEST(0 == strcmp("Hello World!", strcat(result, "World!")));
}

//
int main(int argc, char *argv[])
{
	puts("Starting tests.\n");

	test_strlen();
	test_strcmp();
	test_strcpy();
	test_strcat();

	puts("\nFinished tests.\n");
}