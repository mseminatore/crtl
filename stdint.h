//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#ifndef __STDINT_H
#define  __STDINT_H

#if defined(_WIN32)
    typedef int intptr_t;
    typedef unsigned uintptr_t;
#else
    typedef long intptr_t;
    typedef unsigned long uintptr_t;
#endif

#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN (-9223372036854775807LL - 1LL)
#define INT8_MAX (127)
#define INT16_MAX (32767)
#define INT32_MAX (2147483647)
#define INT64_MAX (9223372036854775807LL)
#define UINT8_MAX (255)
#define UINT16_MAX (65535)
#define UINT32_MAX (4294967295U)
#define UINT64_MAX (18446744073709551615ULL)

// 8-bit integer types
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;

// 16-bit integer types
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed short int_least16_t;
typedef unsigned short uint_least16_t;
typedef signed short int_fast16_t;
typedef unsigned short uint_fast16_t;

// 32-bit integer types
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed int int_least32_t;
typedef unsigned int uint_least32_t;
typedef signed int int_fast32_t;
typedef unsigned int uint_fast32_t;

// 64-bit integer types
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
typedef signed long long int_least64_t;
typedef unsigned long long uint_least64_t;
typedef signed long long int_fast64_t;
typedef unsigned long long uint_fast64_t;

#endif  // ifndef __STDINT_H
