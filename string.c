#include <string.h>

void *memcpy(void *dest, const void *src, size_t num)
{
    void *pDest = dest;

    while (num--)
    {
        *pDest++ = *src++;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t num)
{
    void *pDest = dest;
    unsigned char byte;

    while (num--)
    {
        byte = *src++;
        *pDest++ = byte;
    }

    return dest;
}

char *strcpy(char *dest, char *src)
{
    while (*src)
        *dest++ = *src++;
}

char *strncpy(char *dest, char *src, size_t num)
{

}

char *strcat(char *dest, char *src)
{
    char *pDest = dest;

    // find the end of the destnation string
    while (*pDest++);

    // concatenate the source string
    while (*src)
        *pDest++ = *src++;

    return dest;
}

char *strncat(char *dest, char *src)
{

}

void *memset (void *ptr, int value, size_t num)
{
    void *dest = ptr;

    while (num--)
        *ptr++ = value;
    
    return dest;
}

size_t strlen(const char *str)
{
    size_t count = 0;

    while (*str++)
        count++;

    return count;
}