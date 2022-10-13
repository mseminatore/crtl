// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#if defined(__APPLE_CC__)
#	include "unistd.h"
#else
#	include <fcntl.h>
#	include <io.h>
#	include <sys/stat.h>
#endif

#include "test.h"

//
static void test_puts()
{
	SUITE("puts");

	TEST(1 == puts("Hello"));
}

//
static void test_open()
{
	char str[] = "Hello there!\n";
	int len = strlen(str);

	SUITE("open");
	
#if defined(_WIN32)
	int fd = open("./a.txt", O_CREAT | O_WRONLY, S_IWRITE | S_IREAD);
#else
	int fd = open("./a.txt", O_CREAT | O_WRONLY, S_IRWXU);
#endif

	TEST(fd > 0);
	TEST(len == write(fd, str, len));

	close(fd);
}

//
static void test_fputs()
{
	SUITE("fputs");

	TEST(fputs("Hello!", stdout));
}

//
static void test_sprintf()
{
	char str[256];

	SUITE("sprintf");

	sprintf(str, "Hi %s, is it %d o'clock yet%c%c", "there", 1, '?', '!');

	TEST(0 == strcmp("Hi there, is it 1 o'clock yet?!", str));
}

//
static void test_fprintf()
{
	SUITE("fprintf");

	int result = fprintf(stdout, "%s", "Hello");
	TEST(5 == result);
}

//
static void test_fwrite()
{
	SUITE("fwrite");

	FILE *f = fopen("./write_test.txt", "wt");
	
	TEST(f != NULL);

	char str[] = "Hello there!";

	TEST(1 == fwrite(str, strlen(str), 1, f));
	fclose(f);
}

//
static void test_fread()
{
	SUITE("fread");

	FILE *f = fopen("./write_test.txt", "rt");

	TEST(f != NULL);

	char str[] = "Hello there!";
	char buf[32];

	TEST(1 == fread(buf, strlen(str), 1, f));
	TEST(0 == strcmp(str, buf));
	fclose(f);
}

//
void test_stdio()
{
	test_puts();
	test_open();
	test_fputs();
	test_sprintf();
	test_fprintf();
	test_fwrite();
	test_fread();
}
