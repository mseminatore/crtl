#ifndef __STDINT_H
#define  __STDINT_H

#if defined(_WIN32)
    typedef int intptr_t;
    typedef unsigned uintptr_t;
#else
    typedef long intptr_t;
    typedef unsigned long uintptr_t;
#endif

#endif  // ifndef __STDINT_H
