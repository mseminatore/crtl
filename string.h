#ifndef __STRING_H
#define __STRING_H

#include "stddef.h"

#ifndef NULL
#	define NULL ((void*)0)
#endif

void *memcpy(void *dst, const void *src, size_t num);
void *memmove(void *dst, const void *src, size_t num);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t num);

char *strcat(char *dst, const char *src);
char *strncat(char *dst, const char *src, size_t num);

int memcmp(const void *ptr1, const void *ptr2, size_t num);
int strcmp(const char *str1, const char *str2);
int strcoll(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t num);
size_t strxfrm(char *dst, const char *src, size_t num);

void *memchr(const void *ptr, int value, size_t num);
char *strchr(const char *str, int character);
size_t strcspn(const char *str1, const char *str2);
char *strpbrk(const char *str1, const char *str2);
char *strrchr(const char *str, int character);
size_t strspn(const char *str1, const char *str2);
char *strstr(const char *str1, const char *str2);
char *strtok(char *str, const char *delimiters);

void *memset (void *ptr, int value, size_t num);
char *strerror(int errnum);
size_t strlen(const char *str);

#endif // __STRING_H
