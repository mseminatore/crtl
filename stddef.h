#ifndef __STDDEF_H
#define __STDDEF_H

#ifndef size_t
    #if defined(_WIN32)
        typedef unsigned int size_t;
    #else
        typedef unsigned long size_t;
    #endif
#endif

#endif // __STDDEF_H