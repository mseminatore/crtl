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

//long syscall(long, ...);

NORETURN void exit(int status);
NORETURN void abort(void);

int atoi(const char *str);

void free(void *ptr);
void *malloc(size_t size);
int abs(int x);

#endif // __STDLIB_H
