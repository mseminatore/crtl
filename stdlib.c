// Copyright 2022 Mark Seminatore. All rights reserved.
#include "ctype.h"
#include "stdlib.h"

#if defined(_WIN32)
	#include <windows.h>
#endif

//
void __exit(int status)
{
	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#endif
}

//
int atoi(const char *str)
{
	int result = 0;
	int places = strlen(str);

//	while (isdigit(*str))
//		result += 10 ^ places;

	return result;
}
