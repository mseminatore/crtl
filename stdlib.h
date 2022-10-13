// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDLIB_H
#define __STDLIB_H

#include "rtconfig.h"
#include "stddef.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if defined(__clang__)
#   define NORETURN __attribute__((noreturn))
#else
#   define NORETURN __declspec(noreturn)
#endif

#ifdef INC_DIV
	typedef struct div_t
	{
		int quot;
		int rem;
	} div_t;

	div_t div(int numer, int denom);

#endif

#ifdef INC_LDIV
	typedef struct ldiv_t
	{
		long quot;
		long rem;
	} ldiv_t;

	ldiv_t ldiv(long int numer, long int denom);

#endif

NORETURN void exit(int status);
NORETURN void abort(void);

int atoi(const char *str);

void free(void *ptr);
void *malloc(size_t size);

int abs(int x);
long int labs(long int x);

#endif // __STDLIB_H
