// Copyright 2022 Mark Seminatore. All rights reserved.
#include "ctype.h"

//
int islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

//
int isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

//
int isalpha(int c)
{
	return islower(c) || isupper(c);
}

//
int isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

//
int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

//
int tolower(int c)
{
	if (!isupper(c))
		return c;

	return c - 32;
}

//
int toupper(int c)
{
	if (!islower(c))
		return c;

	return c + 32;
}

//
int isspace(int c)
{
	return c == ' '
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\f';
}
