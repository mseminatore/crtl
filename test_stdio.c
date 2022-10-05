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

	int fd = open("./a.txt", O_CREAT | O_WRONLY, S_IWRITE);
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
void test_stdio()
{
	test_puts();
	test_open();
	test_fputs();
}
