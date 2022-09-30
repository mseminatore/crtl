// Copyright 2022 Mark Seminatore. All rights reserved.
#include "string.h"
#include "assert.h"

// copy num bytes from src to dst
void *memcpy(void *dst, const void *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;
	const char *psrc = src;

    while (num--)
    {
        *pdst++ = *psrc++;
    }

    return dst;
}

// copy num bytes from src to dst
void *memmove(void *dst, const void *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;
	const char *psrc = src;

    char byte;

    while (num--)
    {
        byte = *psrc++;
        *pdst++ = byte;
    }

    return dst;
}

// copy string src to string dst
char *strcpy(char *dst, const char *src)
{
    assert(dst);
    assert(src);

    char *pdst = dst;

    while (*src)
        *dst++ = *src++;

    // make sure we are asciiz
    *dst = '\0';
    return pdst;
}

//
char *strncpy(char *dst, const char *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;

    for (; num && *src; num--)
        *pdst++ = *src++;

    // make sure we are asciiz
    *pdst = '\0';

    return dst;
}

//
char *strcat(char *dst, const char *src)
{
    assert(dst);
    assert(src);

    char *pdst = dst;

    // find the end of the destnation string
	while (*pdst)
		pdst++;

    // concatenate the source string
    while (*src)
        *pdst++ = *src++;

    // make sure we are asciiz
    *pdst = '\0';

    return dst;
}

//
char *strncat(char *dst, const char *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;

    // find the end of the dstnation string
    while (*pdst++)
        ;

    // concatenate the source string
    for (; num && *src; num--)
        *pdst++ = *src++;

    // make sure we are asciiz
    *pdst = '\0';

    return dst;
}

//
int memcmp(const void *str1, const void *str2, size_t n)
{
    int result;

    assert(str1);
    assert(str2);
    assert(n);

    char *p1 = (char*)str1;
    char *p2 = (char*)str2;

    for (; n && *p1 && *p2 && *p1 == *p2; p1++, p2++, n--)
        ;

    result = *p2 - *p1;
    return result;
}

// compare two strings
int strcmp(const char *str1, const char *str2)
{
    int result;

    assert(str1);
    assert(str2);

    for (; *str1 && *str2 && *str1 == *str2; str1++, str2++)
        ;

    result = *str1 - *str2;
    return result;
}

//
int strncmp(const char *str1, const char *str2, size_t num)
{
	int result;

	assert(str1);
	assert(str2);
	assert(num);

	for (; num && *str1 && *str2 && *str1 == *str2; str1++, str2++, num--)
		;

	result = *str1 - *str2;

	return result;
}

// compare two strings using the current Locale rules
int strcoll(const char *str1, const char *str2)
{
    assert(str1);
    assert(str2);

	// TODO - fix up when locale is implemented
    return strcmp(str1, str2);
}

// Transforms the first n characters of the string src into current locale and places them in the string dest
size_t strxfrm(char *dst, const char *src, size_t num)
{
    size_t result = 0;

    assert(dst);
    assert(src);
    assert(num);

    return result;
}

// Finds the first character in the string str1 that matches any character specified in str2
char *strpbrk(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	for (size_t i = 0; i < len1; i++)
	{
		for (size_t j = 0; j < len2; j++)
		{
			if (str1[i] == str2[j])
				return (char*)&str1[i];
		}
	}

	return NULL;
}

// Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str
char *strchr(const char *str, int c)
{
	assert(str);

	size_t len = strlen(str);

	for (size_t i = 0; i < len; i++)
	{
		if (str[i] == c)
			return (char*)&str[i];
	}

	return NULL;
}


// Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str
char *strrchr(const char *str, int c)
{
    assert(str);

	size_t len = strlen(str);
	
	for (size_t i = len; i >= 0; i--)
	{
		if (str[i] == c)
			return (char*)&str[i];
	}

    return NULL;
}

//
size_t strcspn(const char *str1, const char *str2)
{
    size_t count = 0;

    assert(str1);
    assert(str2);

    return count;
}

//
void *memset (void *ptr, int value, size_t num)
{
    assert(ptr);
    assert(num);

    char *dst = ptr;

    while (num--)
        *dst++ = value;
    
    return dst;
}

//
size_t strlen(const char *str)
{
    assert(str);

    size_t count = 0;

    while (*str++)
        count++;

    return count;
}

//
char *strerror(int errnum)
{
	return "unknown";
}

// reverse the given string in-place
char *_strrev(char *str)
{
	char *p1, *p2;

	assert(str);
	if (!str || !*str)
		return NULL;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		char c = *p2;

		*p2 = *p1;
		*p1 = c;
	}

	return str;
}
