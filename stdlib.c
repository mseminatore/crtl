// Copyright 2022 Mark Seminatore. All rights reserved.
#include "ctype.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"

#if defined(_WIN32)
	#include <windows.h>
#elif defined (__APPLE_CC__)
	#include <sys/syscall.h>
	#include "unistd.h"
#endif

#include "stdarg.h"

//
NORETURN void exit(int status)
{
	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#elif defined (__APPLE_CC__)
		syscall(SYS_exit, status);
	#endif
}

//
NORETURN void abort()
{
	exit(0);
}

//
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

//
int abs(int x)
{
	return x < 0 ? -x : x;
}

//
long int labs(long int x)
{
	return x < 0 ? -x : x;
}

#ifdef INC_DIV
 //
 div_t div(int numer, int denom)
 {
 	div_t result;

 	result.quot = numer / denom;
 	result.rem = numer - result.quot * denom;

 	return result;
 }
#endif

#ifdef INC_LDIV

 //
 ldiv_t ldiv(long int numer, long int denom)
 {
 	ldiv_t result;

 	result.quot = numer / denom;
 	result.rem = numer - result.quot * denom;

 	return result;
 }
#endif

// //
// void free(void *ptr)
// {
// 	assert(ptr);
	
// 	// TODO - free the ptr
// }

// //
// void *malloc(size_t size)
// {
// 	if (0 == size)
// 		return NULL;

// 	// TODO - alloc memory and return the ptr

// 	return NULL;
// }
