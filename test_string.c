// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "testy/test.h"

//
static void test_strlen()
{
	SUITE("strlen");

	TEST(strlen("Hello") == 5);
	TEST(strlen("") == 0);
}

//
static void test_memcpy()
{
	char result[64] = "";

	SUITE("memcpy");

	TEST(0 == strcmp(memcpy(result, "Hello", strlen("Hello") + 1), "Hello"));
}

//
static void test_memmove()
{
	char result[64] = "";

	SUITE("memmove");

	TEST(0 == strcmp(memmove(result, "Hello", strlen("Hello") + 1), "Hello"));
}

//
static void test_strcmp()
{
	SUITE("strcmp");

	TEST(0 == strcmp("same", "same"));
	TEST(0 > strcmp("ab", "ac"));
	TEST(0 < strcmp("abcd", "ABCD"));
}

//
static void test_strcpy()
{
	char result[64] = "";

	SUITE("strcpy");

	TEST(0 == strcmp(strcpy(result, "Hello!"), "Hello!"));
	TEST(0 == strcmp(strcpy(result, ""), ""));
}

//
static void test_strncpy()
{
	char result[64] = "";

	SUITE("strncpy");

	TEST(0 == strcmp(strncpy(result, "Hello", 3), "Hel"));
	TEST(0 != strcmp(strncpy(result, "Hello", 4), "Hel"));
}

//
static void test_strcat()
{
	char result[64] = "Hello ";

	SUITE("strcat");

	TEST(0 == strcmp("Hello World!", strcat(result, "World!")));
}

//
static void test_strpbrk()
{
	SUITE("strpbrk");

	TEST(NULL == strpbrk("ABC", "DEF"));
}

//
static void test_strchr()
{
	SUITE("strchr");

	TEST('H' == *strchr("Hello", 'H'));
	TEST('e' == *strchr("Hello", 'e'));
	TEST('l' == *strchr("Hello", 'l'));
}

//
static void test_strrchr()
{
	SUITE("strrchr");

	TEST('H' == *strrchr("Hello", 'H'));
	TEST('e' == *strrchr("Hello", 'e'));
	TEST('l' == *strrchr("Hello", 'l'));
}

//
static void test_strcspn()
{
	SUITE("strcspn");

	TEST(2 == strcspn("Hello", "World"));
	TEST(1 == strcspn("Hello", "There"));
	TEST(4 == strcspn("Stop", "Pill"));
	TEST(0 == strcspn("Hello", "Hill"));
}

//
static void test_strspn()
{
	SUITE("strspn");

	TEST(5 == strspn("Hello", "Hello"));
	TEST(0 == strspn("Hello", "There"));
	TEST(4 == strspn("Hello", "Help"));
}

//
static void test_strtok()
{
	SUITE("strtok");

	TEST(0 == strcmp("Hello", strtok("Hello there", " ")));
	TEST(0 == strcmp("there", strtok(NULL, " ")));
}

//
static void test_memchr()
{
	char buf[] = "Hello";

	SUITE("memchr");

	TEST('H' == *(char *)memchr(buf, 'H', 5));
	TEST('l' == *(char *)memchr(buf, 'l', 5));
	TEST(NULL == memchr(buf, 'z', 5));
}

//
static void test_strstr()
{
	char *p;

	SUITE("strstr");

	p = strstr("Hello World", "World");
	TEST(p != NULL && 0 == strcmp("World", p));

	p = strstr("Hello World", "Hello");
	TEST(p != NULL && 0 == strcmp("Hello World", p));

	TEST(NULL == strstr("Hello World", "xyz"));
	TEST(NULL == strstr("Hi", "Hello World"));
}

//
static void test_strerror()
{
	SUITE("strerror");

	// known valid error codes
	TEST(0 == strcmp(strerror(EPERM),  "Operation not permitted"));
	TEST(0 == strcmp(strerror(ENOENT), "No such file or directory"));
	TEST(0 == strcmp(strerror(EINVAL), "Invalid argument"));
	TEST(0 == strcmp(strerror(ELOOP),  "Too many symbolic links encountered"));
	TEST(0 == strcmp(strerror(ENOTBLK), "Block device required"));

	// index 0 is "Success"
	TEST(0 == strcmp(strerror(0), "Success"));

	// out-of-range returns "unknown error"
	TEST(0 == strcmp(strerror(-1),         "unknown error"));
	TEST(0 == strcmp(strerror(ELOOP + 1),  "unknown error"));
}

//
void test_string()
{
	test_strlen();
	test_memcpy();
	test_memmove();
	test_strcmp();
	test_strcpy();
	test_strncpy();
	test_strcat();
	test_strpbrk();
	test_strchr();
	test_strrchr();
	test_strcspn();
	test_strspn();
	test_strtok();
	test_memchr();
	test_strstr();
	test_strerror();
}


