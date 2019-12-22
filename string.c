#include <string.h>
#include <assert.h>

//
//
//
void *memcpy(void *dest, const void *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    void *pDest = dest;

    while (num--)
    {
        (*(char*)dest)++ = (*(char*)src)++;
    }

    return pDest;
}

//
//
//
void *memmove(void *dest, const void *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    void *pDest = dest;
    unsigned char byte;

    while (num--)
    {
        byte = (*(char*)src)++;
        *dest++ = byte;
    }

    return pDest;
}

//
//
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
//
//
char *strncpy(char *dest, char *src, size_t num)
{
    assert(dest);
    assert(src);
    assert(num);

    char *pDest = dest;

    return pDest;
}

//
//
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
//
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
//
//
void *memset (void *ptr, int value, size_t num)
{
    assert(ptr);
    assert(num);

    void *dest = ptr;

    while (num--)
        *ptr++ = value;
    
    return dest;
}

//
//
//
size_t strlen(const char *str)
{
    assert(str);
    
    size_t count = 0;

    while (*str++)
        count++;

    return count;
}
