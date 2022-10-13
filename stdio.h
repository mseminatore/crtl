// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDIO_H
#define __STDIO_H

#include "stddef.h"

#if defined(_WIN32)
	#define _CRT_SECURE_NO_WARNINGS
	#pragma warning (disable : 4996)
#endif

typedef unsigned long fpos_t;

typedef struct
{
	int status;
	int fildes;
	fpos_t pos;
} FILE;

// standard IO handles
#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#if defined(_WIN32)
#	define open _open
#	define close _close
#	define write _write
#endif

extern FILE *stdin, *stdout, *stderr;

#define BUFSIZ			4096
#define FOPEN_MAX		256
#define FILENAME_MAX	256
#define TMP_MAX			32
#define L_tmpnam		256

#define SEEK_CUR		1
#define SEEK_END		2
#define SEEK_SET		0

#ifndef EOF
#	define EOF -1
#endif

#ifndef va_list
	typedef char* va_type;
	#define va_list va_type
#endif

#if defined(_WIN32)
	#define DIR_MARKER "\\"
#else
	#define DIR_MARKER "/"
#endif

// standard IO
int printf(const char *format, ...);
int vprintf(const char *format, va_list arg);
int putchar(int c);
int putc(int chr, FILE *stream);
int puts(const char *str);

// stream IO
int fclose(FILE *stream);
FILE *fopen(const char *filename, const char *mode);
int fputc(int chr, FILE *stream);
int fputs(const char *str, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *fgets(char *str, int n, FILE *stream);
char *gets(char *str);

// formatted output
int vfprintf(FILE *stream, const char *format, va_list arg);
int vsprintf(char *str, const char *format, va_list arg);
int sprintf(char *str, const char *format, ...);

char *_itoa(int value, char *str, int base);

//int feof(FILE *stream);
//int ferror(FILE *stream);
//int fflush(FILE *stream);
//void clearerr(FILE *stream);
//int remove(const char *filename);
//int ungetc(int chr, FILE *stream);
//void perror(const char *str);

#endif	//__STDIO_H