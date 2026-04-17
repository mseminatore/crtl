// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "testy/test.h"

static void no_op(void) {}

static int int_compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

static int int_compare_desc(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
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
static void test_atol()
{
	SUITE("atol");

	TEST(123L == atol("123"));
	TEST(-456L == atol("-456"));
	TEST(0L == atol("Hello"));
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

	// num=0: should return NULL (bug fixed: no longer unsafe)
	key = 99;
	TEST(NULL == bsearch(&key, arr, 0, sizeof(int), int_compare));

	// integration: qsort an unsorted array, then bsearch for elements
	int unsorted[] = {15, 3, 9, 1, 7, 5, 13, 11};
	qsort(unsorted, 8, sizeof(int), int_compare);
	key = 1;
	result = (int *)bsearch(&key, unsorted, 8, sizeof(int), int_compare);
	TEST(result != NULL && *result == 1);
	key = 9;
	result = (int *)bsearch(&key, unsorted, 8, sizeof(int), int_compare);
	TEST(result != NULL && *result == 9);
	key = 6;
	result = (int *)bsearch(&key, unsorted, 8, sizeof(int), int_compare);
	TEST(result == NULL);
}

//
static void test_qsort()
{
	SUITE("qsort");

	// sort unsorted array
	int arr1[] = {5, 2, 8, 1, 9, 3};
	int exp1[] = {1, 2, 3, 5, 8, 9};
	qsort(arr1, 6, sizeof(int), int_compare);
	TEST(EQUAL_ARRAY(arr1, exp1));

	// sort reverse-sorted array
	int arr2[] = {9, 7, 5, 3, 1};
	int exp2[] = {1, 3, 5, 7, 9};
	qsort(arr2, 5, sizeof(int), int_compare);
	TEST(EQUAL_ARRAY(arr2, exp2));

	// sort already-sorted array
	int arr3[] = {1, 3, 5, 7};
	int exp3[] = {1, 3, 5, 7};
	qsort(arr3, 4, sizeof(int), int_compare);
	TEST(EQUAL_ARRAY(arr3, exp3));

	// sort single element
	int arr4[] = {42};
	int exp4[] = {42};
	qsort(arr4, 1, sizeof(int), int_compare);
	TEST(EQUAL_ARRAY(arr4, exp4));

	// num=0: no crash, array unchanged
	int arr5[] = {7, 3};
	int exp5[] = {7, 3};
	qsort(arr5, 0, sizeof(int), int_compare);
	TEST(EQUAL_ARRAY(arr5, exp5));

	// sort descending using reverse comparator
	int arr6[] = {1, 3, 5, 7, 9};
	int exp6[] = {9, 7, 5, 3, 1};
	qsort(arr6, 5, sizeof(int), int_compare_desc);
	TEST(EQUAL_ARRAY(arr6, exp6));
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
	TEST(0 == atexit(no_op));

	// registering another no-op also returns 0
	TEST(0 == atexit(no_op));

	// fill the registry until overflow; verify failure returns non-zero
	int ret = 0;
	while (ret == 0)
		ret = atexit(no_op);
	TEST(ret != 0);
}

//
static void test_malloc()
{
	SUITE("malloc");

	TEST(NULL == malloc(0));

	void *p = malloc(64);
	TEST(p != NULL);
	free(p);

	// free(NULL) must not crash
	free(NULL);
	TEST(1);
}

static void test_calloc()
{
	SUITE("calloc");

	TEST(NULL == calloc(0, 16));
	TEST(NULL == calloc(4, 0));

	char *p = (char *)calloc(4, 16);
	TEST(p != NULL);
	TEST(p[0] == 0);
	TEST(p[63] == 0);
	free(p);
}

static void test_realloc()
{
	SUITE("realloc");

	// realloc(NULL, n) behaves like malloc(n)
	void *p = realloc(NULL, 64);
	TEST(p != NULL);

	// grow — data preserved
	memset(p, 0xAB, 64);
	void *p2 = realloc(p, 128);
	TEST(p2 != NULL);
	TEST(((unsigned char *)p2)[0] == 0xAB);
	TEST(((unsigned char *)p2)[63] == 0xAB);

	// shrink — first n bytes preserved
	void *p3 = realloc(p2, 32);
	TEST(p3 != NULL);
	TEST(((unsigned char *)p3)[0] == 0xAB);
	TEST(((unsigned char *)p3)[31] == 0xAB);

	// realloc(ptr, 0) frees and returns NULL
	void *p4 = realloc(p3, 0);
	TEST(p4 == NULL);
}

void test_stdlib()
{
	test_atoi();
	test_atol();
	test_abs();
	test_labs();
	test_atexit();
	test_bsearch();
	test_qsort();
	test_rand();
	test_srand();
	test_malloc();
	test_calloc();
	test_realloc();
}
