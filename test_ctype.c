#include "stdio.h"
#include "test.h"

//
static void test_islower()
{
	SUITE("islower");

	TEST(true == islower('a'));
	TEST(true == islower('z'));

	TEST(false == islower('A'));
	TEST(false == islower('Z'));
	TEST(false == islower('1'));
}

//
static void test_isupper()
{
	SUITE("islower");

	TEST(true == isupper('A'));
	TEST(true == isupper('Z'));

	TEST(false == isupper('a'));
	TEST(false == isupper('z'));
	TEST(false == isupper('1'));
}

//
static void test_isalpha()
{
	SUITE("isalpha");

	TEST(true == isalpha('A'));
	TEST(true == isalpha('a'));
	TEST(true == isalpha('Z'));
	TEST(true == isalpha('a'));

	TEST(false == isalpha('0'));
	TEST(false == isalpha('9'));
	TEST(false == isalpha('-'));
}

//
static void test_isdigit()
{
	SUITE("isdigit");

	TEST(true == isdigit('0'));
	TEST(true == isdigit('9'));

	TEST(false == isdigit('A'));
	TEST(false == isdigit('a'));
	TEST(false == isdigit('Z'));
	TEST(false == isdigit('a'));
}

//
static void test_isalnum()
{
	SUITE("isalnum");

	TEST(true == isalnum('0'));
	TEST(true == isalnum('9'));

	TEST(true == isalnum('A'));
	TEST(true == isalnum('a'));
	TEST(true == isalnum('Z'));
	TEST(true == isalnum('a'));

	TEST(false == isalnum('-'));
	TEST(false == isalnum('@'));
	TEST(false == isalnum('&'));
}

//
static void test_tolower()
{
	SUITE("tolower");

	TEST('a' == tolower('A'));
	TEST('z' == tolower('Z'));
	TEST('a' == tolower('a'));
	TEST('z' == tolower('z'));
	TEST('0' == tolower('0'));
	TEST('9' == tolower('9'));
	TEST('@' == tolower('@'));
}

//
static void test_toupper()
{
	SUITE("toupper");

	TEST('A' == toupper('A'));
	TEST('Z' == toupper('Z'));
	TEST('A' == toupper('a'));
	TEST('Z' == toupper('z'));
	TEST('0' == toupper('0'));
	TEST('9' == toupper('9'));
	TEST('@' == toupper('@'));
}

//
static void test_isspace()
{
	SUITE("isspace");

	TEST(true == isspace(' '));
	TEST(true == isspace('\f'));
	TEST(true == isspace('\t'));
	TEST(true == isspace('\n'));
	TEST(true == isspace('\r'));

	TEST(false == isspace('a'));
	TEST(false == isspace('0'));
}

//
void test_ctype()
{
	test_islower();
	test_isupper();
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_tolower();
	test_toupper();
	test_isspace();
}