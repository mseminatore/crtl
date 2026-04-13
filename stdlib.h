//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#ifndef __STDLIB_H
#define __STDLIB_H

#include "config.h"
#include "stddef.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if defined(__GNUC__) || defined(__clang__)
#   define NORETURN __attribute__((noreturn))
#else
#   define NORETURN __declspec(noreturn)
#endif

#ifdef CRTL_INC_DIV
	typedef struct div_t
	{
		int quot;
		int rem;
	} div_t;

	div_t div(int numer, int denom);

#endif

#ifdef CRTL_INC_LDIV
	typedef struct ldiv_t
	{
		long quot;
		long rem;
	} ldiv_t;

	ldiv_t ldiv(long int numer, long int denom);

#endif

NORETURN void exit(int status);
NORETURN void abort(void);
int atexit(void (*func)(void));

int atoi(const char *str);

void free(void *ptr);
void *malloc(size_t size);

int abs(int x);
long int labs(long int x);

void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t newSize);

int rand(void);
void srand(unsigned int seed);

long int atol(const char *str);
long int strtol(const char *str, char **endptr, int base);
unsigned long int strtoul(const char *str, char **endptr, int base);
void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t num, size_t size, int (*compar)(const void *, const void *));

#endif // __STDLIB_H
