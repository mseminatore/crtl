// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
#endif

#if defined(__OSX__) || defined(__MACH__) || defined(__APPLE_CC__)
	#include <unistd.h>
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

#if defined(_WIN32)
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
	{
		DWORD written = 0;

		// If GetStdHandle or WriteConsole return false, then you may need to use AllocConsole().
		WriteConsoleA(stdOut, str, strlen(str), &written, NULL);
	}
#endif

#if defined(__APPLE_CC__)
	int result = syscall(0x20000004, stdout, str, strlen(str));
#endif

	return 1;
}

//
int printf(const char *format, ...)
{
	puts(format);
	return 0;
}
