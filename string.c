//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#include "config.h"
#include "string.h"
#include "assert.h"
#include "errno.h"

extern char *err_strings[];

//-------------------------------------------------------------------------------
// copy num bytes from src to dst
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// copy num bytes from src to dst
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// copy string src to string dst
//-------------------------------------------------------------------------------
char *strcpy(char *dst, const char *src)
{
    assert(dst);
    assert(src);

    char *pdst = dst;

    while (*src)
        *pdst++ = *src++;

    // make sure we are asciiz
    *pdst = '\0';

    return dst;
}

//-------------------------------------------------------------------------------
// copy num characters from src to dst
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// concatenate string src to the end of string dst
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// concatenate num characters from src to dst
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// compare num bytes of two blocks of memory
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// compare two strings
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// compare two strings up to num characters
//-------------------------------------------------------------------------------
int strncmp(const char *str1, const char *str2, size_t num)
{
	int result;

	assert(str1);
	assert(str2);
	assert(num);

	for (; num && *str1 && *str2 && *str1 == *str2; str1++, str2++, num--)
		;

	result = (num == 0) ? 0 : *str1 - *str2;

	return result;
}

//-------------------------------------------------------------------------------
// compare two strings using the current Locale rules
//-------------------------------------------------------------------------------
int strcoll(const char *str1, const char *str2)
{
    assert(str1);
    assert(str2);

	// TODO - fix up when locale is implemented
    return strcmp(str1, str2);
}

//-------------------------------------------------------------------------------
// Transforms the first n characters of the string src into current locale and places them in the string dest
//-------------------------------------------------------------------------------
size_t strxfrm(char *dst, const char *src, size_t num)
{
    size_t result = 0;

    assert(dst);
    assert(src);
    assert(num);

	// TODO - fix up when locale is implemented
    return result;
}

//-------------------------------------------------------------------------------
// Finds the first character in the string str1 that matches any character specified in str2
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// Searches for the first occurrence of the character value (an unsigned char) 
// in the first num bytes of the block of memory pointed by ptr
//-------------------------------------------------------------------------------
void *memchr(const void *ptr, int value, size_t num)
{
	assert(ptr);
	assert(num);

	char *p = (char*)ptr;

	for (; num; num--, p++)
	{
		if (*p == value)
			return (void*)p;
	}

	return NULL;
}

//-------------------------------------------------------------------------------
// Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// Calculates the length of the initial segment of str1 which consists entirely of characters not in str2
//-------------------------------------------------------------------------------
size_t strcspn(const char *str1, const char *str2)
{
    size_t count = 0;

    assert(str1);
    assert(str2);
	if (!str1 || !str2)
		return 0;

	int len = strlen(str2);

	for (; *str1; count++, str1++)
	{
		for (int i = 0; i < len; i++)
		{
			// if we find a char from str2 in str1 return the current count
			if (*str1 == str2[i])
				return count;
		}
	}

    return count;
}

//-------------------------------------------------------------------------------
// Calculates the length of the initial segment of str1 which consists entirely of characters in str2.
//-------------------------------------------------------------------------------
size_t strspn(const char *str1, const char *str2)
{
	size_t count = 0;

	assert(str1);
	assert(str2);
	if (!str1 || !str2)
		return 0;


	int len = strlen(str2);
	int found;

	for (; *str1; count++, str1++)
	{
		found = 0;
		for (int i = 0; i < len; i++)
		{
			// if we find a char from str2 in str1 advance to next char in str1
			if (*str1 == str2[i])
			{
				found = 1;
				break;
			}
		}

		// no char from str2 was found in current char of str1
		if (!found)
			return count;
	}

	return count;
}

//-------------------------------------------------------------------------------
// Finds the first occurrence of the substring str2 in the string str1
//-------------------------------------------------------------------------------
char *strstr(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	if (len2 > len1)
		return NULL;

	for (size_t i = 0; i <= len1 - len2; i++)
	{
		if (strncmp(&str1[i], str2, len2) == 0)
			return (char*)&str1[i];
	}

	return NULL;
}

//-------------------------------------------------------------------------------
// Sets the first num bytes of the block of memory pointed by ptr to the specified value
//-------------------------------------------------------------------------------
void *memset(void *ptr, int value, size_t num)
{
    assert(ptr);
    assert(num);

    char *dst = ptr;

    while (num--)
        *dst++ = value;
    
    return dst;
}

//-------------------------------------------------------------------------------
// Calculates the length of the string str, excluding the terminating null character
//-------------------------------------------------------------------------------
size_t strlen(const char *str)
{
	size_t count = 0;
	
	assert(str);

    while (*str++)
        count++;

    return count;
}

//-------------------------------------------------------------------------------
// Returns a string describing the error code errnum
//-------------------------------------------------------------------------------
char *strerror(int errnum)
{
	if (errnum < 0 || errnum >= CRTL_MAX_ERROR)
		return "unknown error";
		
	return err_strings[errnum];
}

//-------------------------------------------------------------------------------
// Breaks string str into a series of tokens separated by delim.
//-------------------------------------------------------------------------------
char *strtok(char *str, const char *delimiters)
{
	static char buf[CRTL_MAX_TOKEN_STRING];
	static char *ptr = NULL;
	char *token;
	int len;

	assert(delimiters);
	if (!delimiters)
		return NULL;

	// if str is provided reset the token string
	if (str)
	{
		strncpy(buf, str, CRTL_MAX_TOKEN_STRING);
		ptr = buf;
	}

	token = ptr;
	len = strlen(delimiters);

	for(; *ptr; ptr++)
	{
		// search over delimiters
		for(int i = 0; i < len; i++)
			// if we found a delimiter return the current token
			if (*ptr == delimiters[i])
			{
				*ptr++ = '\0';	// make token asciiz by overwriting the delimiter
				return token;
			}
	}

	return token;
}

#ifdef MALLOC
//-------------------------------------------------------------------------------
// Returns a pointer to a new string which is a duplicate of the string str
//-------------------------------------------------------------------------------
char *strdup(const char *str)
{
	assert(str);

	size_t len = strlen(str);
	char *dup = malloc(len + 1);

	if (dup)
		strcpy(dup, str);

	return dup;
}

//-------------------------------------------------------------------------------
// Returns a pointer to a new string which is a duplicate of the string str up 
// to num characters
//-------------------------------------------------------------------------------
char *strndup(const char *str, size_t num)
{
	assert(str);
	assert(num);

	size_t len = strlen(str);
	if (num < len)
		len = num;

	char *dup = malloc(len + 1);

	if (dup)
		strncpy(dup, str, len);

	return dup;
}
#endif // MALLOC

//-------------------------------------------------------------------------------
// reverse the given string in-place
//-------------------------------------------------------------------------------
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
