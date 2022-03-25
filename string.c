#include "string.h"
#include "assert.h"

//
void *memcpy(void *dest, const void *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    void *pDest = dest;

    while (num--)
    {
        *((char*)dest)++ = (*(char*)src)++;
    }

    return pDest;
}

//
void *memmove(void *dest, const void *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    char *pDest = dest;
    unsigned char byte;

    while (num--)
    {
        byte = (*(char*)src)++;
        *pDest++ = byte;
    }

    return pDest;
}

//
char *strcpy(char *dest, char *src)
{
    assert(dest);
    assert(src);

    char *pDest = dest;

    while (*src)
        *dest++ = *src++;

    // make sure we are asciiz
    *dest = '\0';
    return pDest;
}

//
char *strncpy(char *dest, char *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    char *pDest = dest;

    for (; num && *src; num--)
        *dest++ = *src++;

    // make sure we are asciiz
    *dest = '\0';

    return pDest;
}

//
char *strcat(char *dest, char *src)
{
    assert(dest);
    assert(src);

    char *pDest = dest;

    // find the end of the destnation string
    while (*dest++)
        ;

    // concatenate the source string
    while (*src)
        *dest++ = *src++;

    // make sure we are asciiz
    *dest = '\0';

    return pDest;
}

//
char *strncat(char *dest, char *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    char *pDest = dest;

    // find the end of the destnation string
    while (*dest++)
        ;

    // concatenate the source string
    for (; num && *src; num--)
        *dest++ = *src++;

    // make sure we are asciiz
    *dest = '\0';

    return pDest;
}

//
int memcmp(const void *str1, const void *str2, size_t n)
{
    int result;

    assert(str1);
    assert(str2);
    assert(n);

    char *p1 = str1;
    char *p2 = str2;

    for (; n && *p1 && *p2 && *p1 == *p2; p1++, p2++, n--)
        ;

    result = *p2 - *p1;
    return result;
}

//
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
int strcoll(const char *str1, const char *str2)
{
    int result;

    assert(str1);
    assert(str2);

    return result;
}

//
int strncmp(const char *str1, const char *str2, size_t num)
{
    int result;

    assert(str1);
    assert(str2);
    assert(num);

    return result;
}

//
size_t strxfrm(char *destination, const char *source, size_t num)
{
    size_t result;

    assert(destination);
    assert(source);
    assert(num);

    return result;
}

//
const char *strchr(const char *str, int character)
{
    assert(str);

    return str;
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

    char *dest = ptr;

    while (num--)
        *dest++ = value;
    
    return dest;
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
