// Copyright 2022 Mark Seminatore. All rights reserved.
#include "math.h"
#include "testy/test.h"

//
static void test_fabs()
{
	SUITE("fabs");

	TEST(1.0 == fabs(1.0));
	TEST(1.0 == fabs(-1.0));
	TEST(0.0 == fabs(0.0));
	TEST(3.14 == fabs(-3.14));
}

//
static void test_fabsf()
{
	SUITE("fabsf");

	TEST(1.0f == fabsf(1.0f));
	TEST(1.0f == fabsf(-1.0f));
	TEST(0.0f == fabsf(0.0f));
}

//
static void test_fabsl()
{
	SUITE("fabsl");

	TEST(1.0L == fabsl(1.0L));
	TEST(1.0L == fabsl(-1.0L));
	TEST(0.0L == fabsl(0.0L));
}

//
void test_math()
{
	test_fabs();
	test_fabsf();
	test_fabsl();
}
