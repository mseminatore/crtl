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
#define va_start(argp, ptr) ((va_type)(argp = ((va_type)(&ptr + sizeof(ptr)))))
#define va_arg(argp, type) ((type)((intptr_t)(argp += sizeof(type))))
#define va_end(argp)

#endif	//ifndef __STDARG_H
