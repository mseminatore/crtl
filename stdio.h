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

#endif	//__STDIO_H