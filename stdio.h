#ifndef _STDIO_H
#define _STDIO_H

#define stdin 0
#define stout 1
#define stderr 2
#define EOF -1

int puts(const char *str);
int printf(const char *format, ...);

#endif	_STDIO_H