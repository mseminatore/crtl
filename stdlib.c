// Copyright 2022 Mark Seminatore. All rights reserved.
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

#if defined(_WIN32)
	#include <windows.h>
#endif

//
NORETURN void exit(int status)
{
	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#endif

	#if defined(__APPLE_CC__)
		asm ("mov X0, #0");
		asm ("movz X16, #0x200, lsl 16");
		asm ("add X16, X16, #1");
		asm ("svc #0");
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
