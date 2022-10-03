// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
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
	SUITE("open");

	int fd = open("a.txt", O_APPEND | O_WRONLY);
	write(fd, "Hello", 5);
	close(fd);
}

//
void test_stdio()
{
	test_puts();
	test_open();
}
