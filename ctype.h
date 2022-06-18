// Copyright 2022 Mark Seminatore. All rights reserved.
#pragma once

#ifdef _DLL
#	undef _DLL
#endif

#ifndef __CTYPE_H
#define __CTYPE_H

int islower(int c);
int isupper(int c);
int isalpha(int c);
int isdigit(int c);
int isalnum(int c);

int tolower(int c);
int toupper(int c);

#endif  // __CTYPE_H
