// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
#else
	#include <sys/syscall.h>
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

#if defined(__APPLE_CC__)
	return syscall(SYS_write, stream->fildes, str, strlen(str));
#endif
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
	return syscall(SYS_write, stdout, str, strlen(str));
	// asm ("mov X0, #1");
	// asm ("mov X1, %0" : : "r"(str));
	// asm ("mov X2, %x0" : : "r"(len));
	// asm ("movz X16, #0x200, lsl 16");
	// asm ("add X16, X16, #4");
	// asm ("svc #0");
#endif

	return 1;
}

//
int printf(const char *format, ...)
{
	puts(format);
	return 0;
}
