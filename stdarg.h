//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#pragma once

#ifndef __STDARG_H
#define __STDARG_H

#include "stdint.h"

#ifdef va_start
#	undef va_start
#endif

#ifdef va_arg
#	undef va_arg
#endif

#ifdef va_end
#	undef va_end
#endif

#if defined(__GNUC__) || defined(__clang__)
// Use compiler builtins: correct for both x86_64 (register-based ABI) and ARM64
#   define va_list   __builtin_va_list
#   define va_start(ap, last) __builtin_va_start(ap, last)
#   define va_arg(ap, type)   __builtin_va_arg(ap, type)
#   define va_end(ap)         __builtin_va_end(ap)
#else
// Fallback for MSVC and other compilers
typedef char* va_type;
#   define va_list va_type
#   define va_start(argp, ptr) ((va_type)(argp = ((va_type)(&ptr + 1))))
#   define va_arg(argp, type) (*(type*)((intptr_t)(argp += sizeof(type), argp - sizeof(type))))
#   define va_end(argp)
#endif

#endif	//ifndef __STDARG_H
