#include "string.h"
#include "assert.h"

//
void test_strlen()
{
	assert(strlen("Hello") == 5);
	assert(strlen("") == 0);
}

//
int main(int argc, char *argv[])
{
	test_strlen();
}