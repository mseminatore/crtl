// Copyright 2022 Mark Seminatore. All rights reserved.

#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

//
void __assert_impl (const char *msg, const char *filename, int line)
{
	printf("Assertion failed: %s, file %s, line %d\n", msg, filename, line);
    exit(0);
}
