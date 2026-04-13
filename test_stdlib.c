// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include "testy/test.h"

static void no_op(void) {}

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
static void test_rand()
{
	SUITE("rand");

	srand(1);
	TEST(rand() >= 0);

	srand(1);
	TEST(rand() <= RAND_MAX);

	// consecutive calls return different values
	srand(1);
	int r1 = rand();
	int r2 = rand();
	TEST(r1 != r2);
}

//
static void test_srand()
{
	SUITE("srand");

	// same seed produces same first value
	srand(1);
	int r1 = rand();
	srand(1);
	int r2 = rand();
	TEST(r1 == r2);

	// same seed produces same full sequence
	srand(42);
	int seq_a = rand();
	int seq_b = rand();
	srand(42);
	TEST(rand() == seq_a);
	TEST(rand() == seq_b);

	// different seeds produce different first values
	srand(1);
	int ra = rand();
	srand(2);
	int rb = rand();
	TEST(ra != rb);
}

//
static void test_atexit()
{
	SUITE("atexit");

	// verify it returns 0 (success) for a valid function pointer
	TEST(0 == atexit(abort));

	// registering a no-op function also returns 0
	TEST(0 == atexit(no_op));

	// fill the registry until overflow; verify failure returns non-zero
	int ret = 0;
	while (ret == 0)
		ret = atexit(no_op);
	TEST(ret != 0);
}

//
void test_stdlib()
{
	test_atoi();
	test_abs();
	test_labs();
	test_atexit();
	test_rand();
	test_srand();
}
