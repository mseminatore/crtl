// Copyright 2022 Mark Seminatore. All rights reserved.
#pragma once

#ifndef __CTYPE_H
#define __CTYPE_H

#ifdef _DLL
#	undef _DLL
#endif

int islower(int c);
int isupper(int c);
int isalpha(int c);
int isdigit(int c);
int isalnum(int c);

int tolower(int c);
int toupper(int c);

int isspace(int c);

#endif  // __CTYPE_H
