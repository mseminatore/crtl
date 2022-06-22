// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __ASSERT_H
#define __ASSERT_H

#ifdef NDEBUG 
    #define assert(expr) ((void)0)
#else
    #define assert(expr) (void)((expr) || (__assert_impl(#expr, __FILE__, __LINE__), 0))
#endif

extern void __assert_impl (const char *msg, const char *filename, int line);

#endif // __ASSERT_H

