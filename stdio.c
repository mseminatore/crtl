// Copyright 2022 Mark Seminatore. All rights reserved.
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

#if defined(_WIN32)
	#pragma warning (disable : 4996)
	#define _CRT_SECURE_NO_WARNINGS
	#include <Windows.h>
	// TODO - do we need to AllocConsole() or AttachConsole() on startup?
	#include <fcntl.h>
	#include <io.h>
#else
	#include <sys/syscall.h>
	#include "unistd.h"
#endif

#include "stdarg.h"

#define PRINTF_MAX 256

//typedef struct _FLOAT
//{
//	unsigned long long sign : 1;
//	unsigned long long exp : 11;
//	unsigned long long mant : 52;
//} _FLOAT;
//
//union FLOAT
//{
//	_FLOAT f;
//	double d;
//};

//
FILE _stdin		= { 0, 0, 0},	*stdin = &_stdin;
FILE _stdout	= { 0, 1 ,0 },	*stdout = &_stdout;
FILE _stderr	= { 0, 2, 0 },	*stderr = &_stderr;

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
	if (!stream || 1 != write(stream->fildes, &chr, 1))
		return EOF;

	return 1;
}

//
int fputc(int chr, FILE *stream)
{
	return putc(chr, stream);
}

//
int fputs(const char *str, FILE *stream)
{
	assert(str && stream);
	if (!str || !stream)
		return EOF;

	return write(stream->fildes, str, strlen(str));
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
	int result = write(STDOUT_FILENO, str, len);
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

	// TODO - process mode argument

	int flags = 0;
	int fd = open(filename, flags);
	if (fd < 2)
		return NULL;

	// alloc FILE structure
	// TODO - replace with static array alloc
	FILE *stream = (FILE*)malloc(sizeof(FILE));
	assert(stream);
	if (!stream)
		return NULL;

	stream->fildes = fd;
	
	return stream;
}

//
int fclose(FILE *stream)
{
	assert(stream);
	if (!stream)
		return EOF;

	int result = close(stream->fildes);
	stream->fildes = -1;
	stream->status = -1;

	// free FILE structure
	free(stream);

	return result;
}

//
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	assert(ptr && stream /*&& stream->status != -1 && stream->fildes != -1*/);
	if (!ptr || !stream)
		return 0;

	return read(stream->fildes, ptr, nmemb * size);
}

//
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	assert(ptr && stream);
	if (!ptr || !stream)
		return 0;

	return write(stream->fildes, ptr, nmemb * size);
}

//int vsprintf(char *str, const char *format, va_list arg);

//int sprintf(char *str, const char *format, ...);

//
int vfprintf(FILE *stream, const char *format, va_list argp)
{
	int count = 0, chr;
	char buf[PRINTF_MAX], *pbuf = buf;

	assert(stream && format);

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

			case 'f':
			{
				assert(("not yet implemented", 0));

				//union FLOAT f;

				//double val = va_arg(argp, double);
				//f.d = val;
				//printf("%c", f.f.sign);
			}
			break;

			case 'c':
			{
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

	fputs(buf, stream);

	return count;
}

//
int fprintf(FILE *stream, const char *format, ...)
{
	int count;
	va_list argp;

	assert(stream && format);

	va_start(argp, format);
		count = vfprintf(stream, format, argp);
	va_end(argp);

	return count;
}

//
int vprintf(const char *format, va_list argp)
{
	return vfprintf(stdout, format, argp);
}

//
int printf(const char *format, ...)
{
	int count;
	va_list argp;

	assert(format);

	va_start(argp, format);
		count = vprintf(format, argp);
	va_end(argp);

	return count;
}

//int remove(const char *filename);
//int fgetc(FILE *stream);
//char *fgets(char *str, int n, FILE *stream);

//
//int getc(FILE *stream)
//{
//	assert(stream);
//}
//
////
//int getchar(void)
//{
//
//}
//
////
//char *gets(char *str)
//{
//	assert(str);
//}
//
////
//int ungetc(int chr, FILE *stream)
//{
//	assert(stream);
//}

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
