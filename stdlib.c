// Copyright 2022 Mark Seminatore. All rights reserved.
#include "ctype.h"
#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#include <windows.h>
#elif defined (__APPLE_CC__)
	#include <sys/syscall.h>
//	#include <unistd.h>
#endif

//
int	syscall(int number, ...)
{
	int result = 0;

	va_list argp;

	va_start(argp, number);

	switch(number)
	{
	case SYS_exit:
	{
		int status = va_arg(argp, int);

		asm ("mov X0, %w0" : : "r"(status));
		asm ("movz X16, #0x200, lsl 16");
		asm ("add X16, X16, %0" : : "r"(number));
		asm ("svc #0" : "r"(result));
	}
		break;

	case SYS_read:
		break;

	case SYS_write:
	{
		int status = va_arg(argp, int);
		
		asm ("mov X0, #0");
		asm ("movz X16, #0x200, lsl 16");
		asm ("add X16, X16, %0" : : "r"(number));
		asm ("svc #0" : "r"(result));

	}
		break;

	case SYS_open:
		break;
	
	case SYS_close:
		break;

	default:
		assert(0);
		return -1;
	}
	
	va_end(argp);

	return result;
}

//
NORETURN void exit(int status)
{
	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#elif defined (__APPLE_CC__)
		syscall(SYS_exit, status);
		// asm ("mov X0, #0");
		// asm ("movz X16, #0x200, lsl 16");
		// asm ("add X16, X16, #1");
		// asm ("svc #0");
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

	for (int i = places; i > 0; i--)
	{
		if (!isdigit(str[i]))
			return 0;

		result += str[i] - '0' * placeValue;
		placeValue *= 10;
	}

	return sign * result;
}

//
int abs(int x)
{
	return x < 0 ? -x : x;
}
