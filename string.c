#include "string.h"
#include "assert.h"

// copy num bytes from src to dst
void *memcpy(void *dst, const void *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;

    while (num--)
    {
        *pdst++ = (*(char*)src)++;
    }

    return pdst;
}

//
void *memmove(void *dst, const void *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;
    unsigned char byte;

    while (num--)
    {
        byte = (*(char*)src)++;
        *pdst++ = byte;
    }

    return pdst;
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
        *dst++ = *src++;

    // make sure we are asciiz
    *dst = '\0';

    return pdst;
}

//
char *strcat(char *dst, const char *src)
{
    assert(dst);
    assert(src);

    char *pdst = dst;

    // find the end of the dstnation string
    while (*dst++)
        ;

    // concatenate the source string
    while (*src)
        *dst++ = *src++;

    // make sure we are asciiz
    *dst = '\0';

    return pdst;
}

//
char *strncat(char *dst, const char *src, size_t num)
{
    assert(dst);
    assert(src);
    assert(num);

    char *pdst = dst;

    // find the end of the dstnation string
    while (*dst++)
        ;

    // concatenate the source string
    for (; num && *src; num--)
        *dst++ = *src++;

    // make sure we are asciiz
    *dst = '\0';

    return pdst;
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

// compare two strings using the current Locale rules
int strcoll(const char *str1, const char *str2)
{
    int result = 0;

    assert(str1);
    assert(str2);

    return result;
}

//
int strncmp(const char *str1, const char *str2, size_t num)
{
    int result = 0;

    assert(str1);
    assert(str2);
    assert(num);

    return result;
}

//
size_t strxfrm(char *dstination, const char *source, size_t num)
{
    size_t result = 0;

    assert(dstination);
    assert(source);
    assert(num);

    return result;
}

//
char *strchr(const char *str, int character)
{
    assert(str);

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
