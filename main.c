#include "string.h"
#include "assert.h"

//
void test_strlen()
{
	assert(strlen("Hello") == 5);
}

//
int main(int argc, char *argv[])
{
	test_strlen();
}