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

/*
typedef struct __div_t
{
	int quot;
	int rem;
} div_t;

typedef struct __ldiv_t
{
	long quot;
	long rem;
} ldiv_t;
*/

NORETURN void exit(int status);
NORETURN void abort(void);

int atoi(const char *str);

void free(void *ptr);
void *malloc(size_t size);

//div_t div(int numer, int denom);
//ldiv_t ldiv(long int numer, long int denom);
int abs(int x);
long int labs(long int x);

#endif // __STDLIB_H
