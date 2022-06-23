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
static void test_abs()
{
	SUITE("abs");

	TEST(1 == abs(1));
	TEST(1 == abs(-1));
	TEST(0 == abs(0));
}

//
void test_stdlib()
{
	test_atoi();
	test_abs();
}
