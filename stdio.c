#include "stdio.h"
#include "assert.h"

int puts(const char *str)
{
	assert(str);
	if (!str)
		return EOF;

	return 1;
}

int printf(const char *format, ...)
{
	return 0;
}
