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
FILE _stdin = { 0, 0, 0}, *stdin = &_stdin;
FILE _stdout = { 0, 1 ,0 }, *stdout = &_stdout;
FILE _stderr = { 0, 2, 0 }, *stderr = &_stderr;

//
int putchar(int c)
{
	char chr[2];

	chr[0] = c;
	chr[1] = 0;
	puts(chr);
	return 1;
}

//
int putc(int chr, FILE *stream)
{
	assert(stream);
}

//
int fputs(const char *str, FILE *stream)
{
	assert(str && stream);
	if (!str || !stream)
		return EOF;

#if defined(__APPLE_CC__)
	return write(stream->fildes, str, strlen(str));

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
	int result = write(stdout, str, len);
	if (result != len)
		return EOF;
#endif

	return 1;
}

//
FILE *fopen(const char *filename, const char *mode)
{
	assert(filename && mode);
	if (!filename || ! mode)
		return NULL;

#if defined(__APPLE_CC__)
	int flags = 0;
	int fd = open(filename, flags);
#endif
	// TODO - alloc FILE structure
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

	// TODO - free FILE structure
	return EOF;
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

//int remove(const char *filename);
//int fgetc(FILE *stream);
//char *fgets(char *str, int n, FILE *stream);
//int fputc(int chr, FILE *stream);

//
int getc(FILE *stream)
{
	assert(stream);
}

//
int getchar(void)
{

}

//
char *gets(char *str)
{
	assert(str);
}

//
int ungetc(int chr, FILE *stream)
{
	assert(stream);
}

//
char *_itoa(int value, char *str, int base)
{
	char *pchr = str;
	int place_value;

	// check for negative numbers
	if (value < 0 && base == 10)
		*pchr++ = '-';

	while (value)
	{
		place_value = value % base;

		*pchr++ = place_value + '0';
		value /= base;
	}

	*pchr = 0;	// make sure we are asciiz!

	return _strrev(str);
}
