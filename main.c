// Copyright 2022 Mark Seminatore. All rights reserved.
#include "test.h"
#include "string.h"
#include "stdio.h"

//
static int testnum = 1;
static int testerrs = 0;

//
int main(int argc, char *argv[])
{
	puts("Starting tests.\n");

	test_string();
	test_stdlib();

	puts("\nFinished tests.\n");
}