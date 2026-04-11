// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "testy/test.h"

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
static void test_labs()
{
	SUITE("labs");

	TEST(1L == labs(1L));
	TEST(1L == labs(-1L));
	TEST(0L == labs(0L));
	TEST(2147483648L == labs(-2147483648L));
}

//
static void test_atexit()
{
	SUITE("atexit");

	// atexit is a stub; verify it returns 0 (success) for a valid function pointer
	TEST(0 == atexit(abort));
}

//
void test_stdlib()
{
	test_atoi();
	test_abs();
	test_labs();
	test_atexit();
}
