//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------
#include "ctype.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"

#if defined(_WIN32)
	#include <windows.h>
#elif defined (__APPLE_CC__) || defined(__linux__)
	#include <sys/syscall.h>
	#include "unistd.h"
#endif

#include "stdarg.h"

//-------------------------------------------------------------------------------
// platform specific process exit and atexit implementation
//-------------------------------------------------------------------------------
typedef void (*atexit_func_t)(void);

#define MAX_ATEXIT_FUNCS 32
static atexit_func_t atexit_funcs[MAX_ATEXIT_FUNCS];
static int atexit_count = 0;

static unsigned int rand_seed = 1;

//-------------------------------------------------------------------------------
// platform specific process exit
//-------------------------------------------------------------------------------
NORETURN void exit(int status)
{
	// call the registered atexit functions
	for (int i = atexit_count - 1; i >= 0; i--)
	{
		atexit_funcs[i]();
	}

	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#elif defined (__APPLE_CC__) || defined(__linux__)
		syscall(SYS_exit, status);
	#endif

	while (1) {}
}

//-------------------------------------------------------------------------------
// abort the program
//-------------------------------------------------------------------------------
NORETURN void abort()
{
	exit(0);
}

//-------------------------------------------------------------------------------
// Registers a function to be called at normal process termination
//-------------------------------------------------------------------------------
int atexit(void (*func)(void))
{
	if (atexit_count >= MAX_ATEXIT_FUNCS)
		return -1;

	atexit_funcs[atexit_count++] = func;
	return 0;
}

//-------------------------------------------------------------------------------
// convert a string to an integer
//-------------------------------------------------------------------------------
int atoi(const char *str)
{
	int result = 0, places;
	int placeValue = 1;
	int sign = 1;

	// check for negative number
	if (str[0] == '-')
	{
		str++;
		sign = -1;
	}
	
	places = strlen(str);

	for (int i = places - 1; i >= 0; i--)
	{
		if (!isdigit(str[i]))
			return 0;

		result += (str[i] - '0') * placeValue;
		placeValue *= 10;
	}

	return sign * result;
}

//-------------------------------------------------------------------------------
// absolute value
//-------------------------------------------------------------------------------
int abs(int x)
{
	return x < 0 ? -x : x;
}

//-------------------------------------------------------------------------------
// absolute value for long int
//-------------------------------------------------------------------------------
long int labs(long int x)
{
	return x < 0 ? -x : x;
}

#ifdef INC_DIV
 //-------------------------------------------------------------------------------
 // compute quotient and remainder of integer division
 //-------------------------------------------------------------------------------
div_t div(int numer, int denom)
{
	div_t result;

 	result.quot = numer / denom;
 	result.rem = numer - result.quot * denom;

 	return result;
 }
#endif

#ifdef INC_LDIV

 //-------------------------------------------------------------------------------
 // compute quotient and remainder of long integer division
 //-------------------------------------------------------------------------------
ldiv_t ldiv(long int numer, long int denom)
 {
 	ldiv_t result;

 	result.quot = numer / denom;
 	result.rem = numer - result.quot * denom;

 	return result;
 }
#endif

//-------------------------------------------------------------------------------
// return a psuedo random number
//-------------------------------------------------------------------------------
int rand(void)
{
	int result;

	// Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs"
	unsigned int x = rand_seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	rand_seed = x;
	return (int)(x/2);
}

//-------------------------------------------------------------------------------
// set the seed for random number generation
//-------------------------------------------------------------------------------
void srand(unsigned int seed)
{
	rand_seed = seed;
}

#if 0
//-------------------------------------------------------------------------------
// free the memory block pointed to by ptr
//-------------------------------------------------------------------------------
void free(void *ptr)
{
	assert(ptr);
	
	// TODO - free the ptr
}

//-------------------------------------------------------------------------------
// alloc memory of size bytes and return a pointer to the allocated memory
//-------------------------------------------------------------------------------
void *malloc(size_t size)
{
	if (0 == size)
		return NULL;

	// TODO - alloc memory and return the ptr

	return NULL;
}

//-------------------------------------------------------------------------------
// alloc memory for an array of num elements of size bytes each and returns a pointer to the allocated memory. The memory is set to zero
//-------------------------------------------------------------------------------
void *calloc(size_t num, size_t size)
{
	if (0 == num || 0 == size)
		return NULL;

	size_t totalSize = num * size;

	// TODO - alloc memory and return the ptr

	return NULL;
}

//-------------------------------------------------------------------------------
// change the size of the memory block pointed to by ptr to newSize bytes
//-------------------------------------------------------------------------------
void *realloc(void *ptr, size_t newSize)
{
	if (0 == newSize)
	{
		free(ptr);
		return NULL;
	}

	if (!ptr)
		return malloc(newSize);

	// TODO - realloc the ptr to newSize and return the new ptr

	return NULL;
}

//-------------------------------------------------------------------------------
// convert a string to a long integer
//-------------------------------------------------------------------------------
long int atol(const char *str)
{
	return (long int)atoi(str);
}

//-------------------------------------------------------------------------------
// convert a string to a long integer with error checking
//-------------------------------------------------------------------------------
long int strtol(const char *str, char **endptr, int base)
{
	// TODO - convert str to a long int and return it. If endptr is not NULL, store the address of the first invalid character in *endptr. The base can be 2, 8, 10, or 16
	return 0;
}

//-------------------------------------------------------------------------------
// convert a string to an unsigned long integer with error checking
//-------------------------------------------------------------------------------
unsigned long int strtoul(const char *str, char **endptr, int base)
{
	// TODO - convert str to an unsigned long int and return it. If endptr is not NULL, store the address of the first invalid character in *endptr. The base can be 2, 8, 10, or 16
	return 0;
}

//-------------------------------------------------------------------------------
// sort an array of num elements of size bytes each, using the compar function to compare elements
//-------------------------------------------------------------------------------
void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *))
{
	// TODO - sort the array pointed to by base, which contains num elements of size bytes each, using the compar function to compare elements
}

#endif

//-------------------------------------------------------------------------------
// perform a binary search for key in the array pointed to by base, which contains num elements of size bytes each, using the compar function to compare elements
//-------------------------------------------------------------------------------
void *bsearch(const void *key, const void *base, size_t num, size_t size, int (*compar)(const void *, const void *))
{
	// perform a binary search for key in the array pointed to by base, which contains num elements of size bytes each, using the compar function to compare elements
	void *low = (void *)base;
	void *high = (char *)base + (num - 1) * size;
	void *mid;

	while (low <= high)
	{
		mid = (char *)low + (((char *)high - (char *)low) / size / 2) * size;

		int cmp = compar(key, mid);

		if (cmp < 0)
			high = (char *)mid - size;
		else if (cmp > 0)
			low = (char *)mid + size;
		else
			return mid;
	}

	return NULL;
}
