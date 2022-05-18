#include "string.h"
#include "assert.h"

//
int test_string()
{
	assert(strlen("Hello") == 6);
}

//
int main(int argc, char *argv[])
{
	test_string();
}