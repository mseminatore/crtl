// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDIO_H
#define __STDIO_H

typedef struct
{
	int status;
} FILE;

#define stdin 0
#define stout 1
#define stderr 2
#define EOF -1

int puts(const char *str);
int printf(const char *format, ...);
int putchar(int c);
int fputs(const char *str, FILE *stream);

#endif	//__STDIO_H