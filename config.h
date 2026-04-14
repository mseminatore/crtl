//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#ifndef __CONFIG_H
#define __CONFIG_H

//-------------------------------------------------------------------------------
// Configuration for CRTL
//-------------------------------------------------------------------------------
#define CRTL_USE_STDIO 1
#define CRTL_USE_STDLIB 1
#define CRTL_USE_STRING 1

//-------------------------------------------------------------------------------
// platform specific process exit and atexit implementation
//-------------------------------------------------------------------------------
#define CRTL_MAX_ATEXIT_FUNCS 32

// Uncomment the following lines to include the div and ldiv functions in stdlib
// #define CRTL_INC_DIV
// #define CRTL_INC_LDIV

// Uncomment the following line to include floating point support in stdio
// #define CRTL_INC_FLOAT

// configurable max size for printf output
#define CRTL_PRINTF_MAX 256

// configurable max size for token string in strtok
#define CRTL_MAX_TOKEN_STRING 256

//-------------------------------------------------------------------------------
// maximum error code value for strerror
//-------------------------------------------------------------------------------
#define CRTL_MAX_ERROR EWOULDBLOCK

#endif // __CONFIG_H
