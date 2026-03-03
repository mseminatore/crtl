// Copyright 2022 Mark Seminatore. All rights reserved.
#include "testy/test.h"

extern void test_string();
extern void test_stdlib();
extern void test_ctype();
extern void test_stdio();

void test_main(int argc, char *argv[])
{
	MODULE("String Functions");
	test_string();
	
	MODULE("Stdlib Functions");
	test_stdlib();
	
	MODULE("Ctype Functions");
	test_ctype();
	
	MODULE("Stdio Functions");
	test_stdio();
}
