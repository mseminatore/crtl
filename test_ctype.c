#include "stdio.h"
#include "ctype.h"
#include "testy/test.h"

//
static void test_islower()
{
	SUITE("islower");

	TEST(TRUE == islower('a'));
	TEST(TRUE == islower('z'));

	TEST(FALSE == islower('A'));
	TEST(FALSE == islower('Z'));
	TEST(FALSE == islower('1'));
}

//
static void test_isupper()
{
	SUITE("islower");

	TEST(TRUE == isupper('A'));
	TEST(TRUE == isupper('Z'));

	TEST(FALSE == isupper('a'));
	TEST(FALSE == isupper('z'));
	TEST(FALSE == isupper('1'));
}

//
static void test_isalpha()
{
	SUITE("isalpha");

	TEST(TRUE == isalpha('A'));
	TEST(TRUE == isalpha('a'));
	TEST(TRUE == isalpha('Z'));
	TEST(TRUE == isalpha('a'));

	TEST(FALSE == isalpha('0'));
	TEST(FALSE == isalpha('9'));
	TEST(FALSE == isalpha('-'));
}

//
static void test_isdigit()
{
	SUITE("isdigit");

	TEST(TRUE == isdigit('0'));
	TEST(TRUE == isdigit('9'));

	TEST(FALSE == isdigit('A'));
	TEST(FALSE == isdigit('a'));
	TEST(FALSE == isdigit('Z'));
	TEST(FALSE == isdigit('a'));
}

//
static void test_isalnum()
{
	SUITE("isalnum");

	TEST(TRUE == isalnum('0'));
	TEST(TRUE == isalnum('9'));

	TEST(TRUE == isalnum('A'));
	TEST(TRUE == isalnum('a'));
	TEST(TRUE == isalnum('Z'));
	TEST(TRUE == isalnum('a'));

	TEST(FALSE == isalnum('-'));
	TEST(FALSE == isalnum('@'));
	TEST(FALSE == isalnum('&'));
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

	TEST(TRUE == isspace(' '));
	TEST(TRUE == isspace('\f'));
	TEST(TRUE == isspace('\t'));
	TEST(TRUE == isspace('\n'));
	TEST(TRUE == isspace('\r'));

	TEST(FALSE == isspace('a'));
	TEST(FALSE == isspace('0'));
}

//
static void test_isprint()
{
	SUITE("isprint");

	TEST(TRUE == isprint(' '));
	TEST(TRUE == isprint('A'));
	TEST(TRUE == isprint('~'));

	TEST(FALSE == isprint('\t'));
	TEST(FALSE == isprint('\n'));
	TEST(FALSE == isprint(127));   // DEL
}

//
static void test_isgraph()
{
	SUITE("isgraph");

	TEST(TRUE == isgraph('A'));
	TEST(TRUE == isgraph('!'));
	TEST(TRUE == isgraph('~'));

	TEST(FALSE == isgraph(' '));   // space excluded
	TEST(FALSE == isgraph('\t'));
	TEST(FALSE == isgraph(127));
}

//
static void test_ispunct()
{
	SUITE("ispunct");

	TEST(TRUE == ispunct('!'));
	TEST(TRUE == ispunct('.'));
	TEST(TRUE == ispunct('@'));

	TEST(FALSE == ispunct('A'));
	TEST(FALSE == ispunct('9'));
	TEST(FALSE == ispunct(' '));
}

//
static void test_isxdigit()
{
	SUITE("isxdigit");

	TEST(TRUE == isxdigit('0'));
	TEST(TRUE == isxdigit('9'));
	TEST(TRUE == isxdigit('a'));
	TEST(TRUE == isxdigit('f'));
	TEST(TRUE == isxdigit('A'));
	TEST(TRUE == isxdigit('F'));

	TEST(FALSE == isxdigit('g'));
	TEST(FALSE == isxdigit('G'));
	TEST(FALSE == isxdigit('z'));
}

//
static void test_iscntrl()
{
	SUITE("iscntrl");

	TEST(TRUE == iscntrl('\0'));
	TEST(TRUE == iscntrl('\t'));
	TEST(TRUE == iscntrl('\n'));
	TEST(TRUE == iscntrl(127));   // DEL

	TEST(FALSE == iscntrl(' '));
	TEST(FALSE == iscntrl('A'));
}

//
static void test_isblank()
{
	SUITE("isblank");

	TEST(TRUE == isblank(' '));
	TEST(TRUE == isblank('\t'));

	TEST(FALSE == isblank('\n'));
	TEST(FALSE == isblank('A'));
	TEST(FALSE == isblank('0'));
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
	test_isprint();
	test_isgraph();
	test_ispunct();
	test_isxdigit();
	test_iscntrl();
	test_isblank();
}