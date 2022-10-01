// Copyright 2022 Mark Seminatore. All rights reserved.

#pragma once

#ifndef __STDARG_H
#define __STDARG_H

#include "stdint.h"

typedef char* va_type;

#ifdef va_start
#	undef va_start
#endif

#ifdef va_arg
#	undef va_arg
#endif

#ifdef va_end
#	undef va_end
#endif

#define va_list va_type

#if defined(__aarch64__)
// first parameter is in W0/X0, next are on the stack
#   define va_start(argp, ptr) (argp = ((va_type)__builtin_frame_address(0))+16)
#else
#   define va_start(argp, ptr) ((va_type)(argp = ((va_type)(&ptr + 1))))
#endif

#define va_arg(argp, type) (*(type*)((intptr_t)(argp += sizeof(type), argp - sizeof(type))))
#define va_end(argp)

#endif	//ifndef __STDARG_H
