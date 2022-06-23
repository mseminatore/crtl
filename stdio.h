// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDIO_H
#define __STDIO_H

typedef struct
{
	int status;
	int fildes;
} FILE;

// standard IO handles
#define stdin 0
#define stdout 1
#define stderr 2

#define BUFSIZ 4096

#ifndef EOF
#	define EOF -1
#endif

int puts(const char *str);
int printf(const char *format, ...);
int putchar(int c);
int fputs(const char *str, FILE *stream);

#endif	//__STDIO_H