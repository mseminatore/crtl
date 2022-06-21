// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDLIB_H
#define __STDLIB_H

#include "stddef.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if defined(__clang__)
#   define NORETURN __attribute__((noreturn))
#else
#   define NORETURN __declspec(noreturn)
#endif

NORETURN void __exit(int status);
int atoi(const char *str);

#endif // __STDLIB_H
