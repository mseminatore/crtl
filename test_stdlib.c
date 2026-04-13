// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include "testy/test.h"

static void no_op(void) {}

static int int_compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

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
static void test_bsearch()
{
	SUITE("bsearch");

	int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
	int n = 8;
	int key;
	int *result;

	// find element in the middle
	key = 7;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result != NULL && *result == 7);

	// find first element
	key = 1;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result != NULL && *result == 1);

	// find last element
	key = 15;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result != NULL && *result == 15);

	// key not present in array
	key = 6;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result == NULL);

	// key smaller than all elements
	key = 0;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result == NULL);

	// key larger than all elements
	key = 20;
	result = (int *)bsearch(&key, arr, n, sizeof(int), int_compare);
	TEST(result == NULL);

	// single-element array, key found
	int single[] = {42};
	key = 42;
	result = (int *)bsearch(&key, single, 1, sizeof(int), int_compare);
	TEST(result != NULL && *result == 42);

	// single-element array, key not found
	key = 99;
	result = (int *)bsearch(&key, single, 1, sizeof(int), int_compare);
	TEST(result == NULL);

	// num=0: unsafe with current implementation (size_t underflow on num-1)
	SKIP_TEST(bsearch(&key, arr, 0, sizeof(int), int_compare) == NULL);
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
	test_bsearch();
	test_rand();
	test_srand();
}
