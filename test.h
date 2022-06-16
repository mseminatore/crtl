// Copyright 2022 Mark Seminatore. All rights reserved.
#pragma once

#ifndef __TEST_H
#define __TEST_H

#include "assert.h"

// simple test harness
#define TEST(s) puts("\tChecking that: " ## #s ## "\n"); assert(#s); putchar(251)
#define SUITE(s) puts("\nTesting " s "...\n")

void test_string();
void test_stdlib();

#endif // #ifndef __TEST_H
