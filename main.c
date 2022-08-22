// Copyright 2022 Mark Seminatore. All rights reserved.
#include "test.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

//
int testnum = 0;
int testerrs = 0;

//
int main(int argc, char *argv[])
{
	puts("Begin tests...\n");

	test_string();
	test_stdlib();
	test_ctype();

	puts("\n");
	printf("Successfully completed %d tests.\n", testnum);

	exit(0);
}