// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDDEF_H
#define __STDDEF_H

#ifndef size_t
    #if defined(_WIN64)
		typedef unsigned __int64 size_t;
	#elif defined(_WIN32)
        typedef unsigned int size_t;
    #else
        typedef unsigned long size_t;
    #endif
#endif

#if defined (_WIN64)
	typedef __int64 ptrdiff_t;
#elif defined(_WIN32)
	typedef int ptrdiff_t;
#endif

#ifndef NULL
#	define NULL ((void*)0)
#endif

#endif // __STDDEF_H