#ifndef __STRING_H
#define __STRING_H

#define NULL (void*)0

typedef unsigned int size_t;

void *memcpy(void *dest, const void *src, size_t num);
void *memmove(void *dest, const void *src, size_t num);

char *strcpy(char *dest, char *src);
char *strncpy(char *dest, char *src, size_t num);

char *strcat(char *dest, char *src);
char *strncat(char *dest, char *src);

size_t strlen(const char *str);

#endif // __STRING_H
