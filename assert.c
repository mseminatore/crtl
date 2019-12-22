#include <assert.h>

void __assert_impl (const char *msg, const char *filename, int line)
{
    printf("Assertion failed: %s, file %s, line $d\n", msg, filename, line);
    exit(0);
}
