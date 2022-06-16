// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "test.h"

//
static void test_atoi()
{
	SUITE("atoi");

	TEST(123 == atoi("123"));
	TEST(-123 == atoi("-123"));
	TEST(0 == atoi("Hello"));
}

//
void test_stdlib()
{
	test_atoi();
}
