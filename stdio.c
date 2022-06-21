// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
#endif

//
int putchar(int c)
{
	return 1;
}

//
int fputs(const char *str, FILE *stream)
{
	assert(str && stream);
	if (!str || !stream)
		return EOF;

	return 1;
}

//
int puts(const char *str)
{
	assert(str);
	if (!str)
		return EOF;

	int len = strlen(str);

#if defined(_WIN32)
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
	{
		DWORD written = 0;

		// If GetStdHandle or WriteConsole return false, then you may need to use AllocConsole().
		WriteConsoleA(stdOut, str, len, &written, NULL);
	}
#endif

#if defined(__APPLE_CC__)
	//int result = syscall(0x20000004, stdout, str, strlen(str));
	#if defined(__APPLE_CC__)
		asm ("mov X0, #1");
		asm ("mov X1, %0" : : "r"(str));
		asm ("mov X2, %x0" : : "r"(len));
		asm ("movz X16, #0x200, lsl 16");
		asm ("add X16, X16, #4");
		asm ("svc #0");
	#endif
#endif

	return 1;
}

//
int printf(const char *format, ...)
{
	puts(format);
	return 0;
}
