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
	char buf[16];

	SUITE("memmove");

	// non-overlapping
	TEST(0 == strcmp(memmove(buf, "Hello", 6), "Hello"));

	// overlapping: shift right (dst > src)
	memcpy(buf, "Hello", 6);
	memmove(buf + 1, buf, 5);
	TEST(buf[1] == 'H' && buf[2] == 'e');

	// overlapping: shift left (dst < src)
	memcpy(buf, "Hello", 6);
	memmove(buf, buf + 1, 4);
	TEST(buf[0] == 'e' && buf[1] == 'l');
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

	// found case: first char in str1 that appears in str2
	const char *p = strpbrk("Hello World", "World");
	TEST(p != NULL && *p == 'l');
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
static void test_memset()
{
	char buf[16];

	SUITE("memset");

	memset(buf, 'X', sizeof(buf));
	TEST(buf[0] == 'X');
	TEST(buf[15] == 'X');

	memset(buf, 0, sizeof(buf));
	TEST(buf[0] == 0);
	TEST(buf[15] == 0);

	// partial fill
	memset(buf, 'A', 4);
	TEST(buf[0] == 'A');
	TEST(buf[3] == 'A');
	TEST(buf[4] == 0);
}

//
static void test_memcmp()
{
	SUITE("memcmp");

	TEST(0 == memcmp("abc", "abc", 3));
	TEST(0 > memcmp("abc", "abd", 3));
	TEST(0 < memcmp("abd", "abc", 3));
	TEST(0 == memcmp("abc", "abz", 0));  // length 0 always equal
}

//
static void test_strncat()
{
	char buf[32];

	SUITE("strncat");

	strcpy(buf, "Hello");
	strncat(buf, " World", 6);
	TEST(0 == strcmp(buf, "Hello World"));

	// limit shorter than src — only appends n chars
	strcpy(buf, "Hi");
	strncat(buf, " there", 3);
	TEST(0 == strcmp(buf, "Hi th"));

	// limit=0 — nothing appended
	strcpy(buf, "abc");
	strncat(buf, "xyz", 0);
	TEST(0 == strcmp(buf, "abc"));
}

//
static void test_strncmp()
{
	SUITE("strncmp");

	TEST(0 == strncmp("abc", "abc", 3));
	TEST(0 == strncmp("abcX", "abcY", 3));  // differ beyond limit
	TEST(0 > strncmp("abc", "abd", 3));
	TEST(0 < strncmp("abd", "abc", 3));
	TEST(0 == strncmp("abc", "abz", 0));    // length 0 always equal
}

//
static void test_strdup()
{
	SUITE("strdup");

	char *p = strdup("Hello");
	TEST(p != NULL);
	TEST(0 == strcmp(p, "Hello"));
	free(p);

	char *e = strdup("");
	TEST(e != NULL);
	TEST(0 == strcmp(e, ""));
	free(e);
}

//
static void test_strndup()
{
	SUITE("strndup");

	// limit shorter than string
	char *p = strndup("Hello World", 5);
	TEST(p != NULL);
	TEST(0 == strcmp(p, "Hello"));
	free(p);

	// limit longer than string — copies whole string
	char *q = strndup("Hi", 100);
	TEST(q != NULL);
	TEST(0 == strcmp(q, "Hi"));
	free(q);
}

//
static void test_strrev()
{
	char buf[32];

	SUITE("_strrev");

	strcpy(buf, "Hello");
	_strrev(buf);
	TEST(0 == strcmp(buf, "olleH"));

	// single character
	strcpy(buf, "X");
	_strrev(buf);
	TEST(0 == strcmp(buf, "X"));

	// empty string
	strcpy(buf, "");
	_strrev(buf);
	TEST(0 == strcmp(buf, ""));
}

//
static void test_strcoll()
{
	SUITE("strcoll");

	TEST(0 == strcoll("same", "same"));
	TEST(0 > strcoll("ab", "ac"));
	TEST(0 < strcoll("ac", "ab"));
}

//
void test_string()
{
	test_strlen();
	test_memcpy();
	test_memmove();
	test_memset();
	test_memcmp();
	test_strcmp();
	test_strcpy();
	test_strncpy();
	test_strcat();
	test_strncat();
	test_strncmp();
	test_strpbrk();
	test_strchr();
	test_strrchr();
	test_strcspn();
	test_strspn();
	test_strtok();
	test_memchr();
	test_strstr();
	test_strdup();
	test_strndup();
	test_strrev();
	test_strcoll();
	test_strerror();
}


