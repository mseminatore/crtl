// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
#else
	#include <sys/syscall.h>
	#include "unistd.h"
#endif

#include "stdarg.h"

#define PRINTF_MAX 256

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
FILE *fopen(const char *filename, const char *mode)
{
	assert(filename && mode);
	if (!filename || ! mode)
		return NULL;

	return NULL;
}

//
int fclose(FILE *stream)
{
	assert(stream);
	if (!stream)
		return EOF;

	#if defined(_WIN32)
	#else
		int result = close(stream->fildes);
		stream->fildes = -1;
		return result;
	#endif

	return EOF;
}

//
char *_itoa(int value, char *str, int base)
{
	char *pchr = str;
	int place_value;

	while (value)
	{
		place_value = value % base;

		*pchr++ = place_value + '0';
		value /= base;
	}

	*pchr = 0;	// make sure we are asciiz!

	return _strrev(str);
}

//
int fprintf(FILE *stream, const char *format, ...)
{
	return 0;
}

//
int printf(const char *format, ...)
{
	int count = 0, chr;
	char buf[PRINTF_MAX], *pbuf = buf;

	va_list argp;

	va_start(argp, format);

	while ((chr = *format))
	{
		if (chr == '%')
		{
			// get format specififer
			format++;
			switch (*format)
			{
			case '%':
				*pbuf++ = '%';
				count++;
				break;

			case 'i':
			case 'd':
			{
				int ival = va_arg(argp, int);
				char int_string[32];

				_itoa(ival, int_string, 10);
				strcpy(pbuf, int_string);
				int len = strlen(int_string);
				pbuf += len;
				count += len;
			}
			break;

			case 'c':
			{
				format++;
				*pbuf++ = va_arg(argp, char);
				count++;
			}
			break;

			case 's':
			{
				char *pstr = va_arg(argp, char*);

				strcpy(pbuf, pstr);
				int len = strlen(pstr);
				pbuf += len;
				count += len;
			}
			break;

			default:
				assert(0);
				return -1;
			}
		}
		else
		{
			*pbuf++ = chr;
			count++;
		}

		format++;
	}

	*pbuf = 0;	// make sure we are asciiz

	va_end(argp);

	puts(buf);

	return count;
}
