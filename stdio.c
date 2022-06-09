#include "stdio.h"
#include "assert.h"

#if defined(_WIN32)
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
#endif

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

	return 1;
}

//
int printf(const char *format, ...)
{
	puts(format);
	return 0;
}
