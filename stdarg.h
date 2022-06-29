#pragma once

#ifndef __STDARG_H
#define __STDARG_H

typedef char* va_type;

#define va_list va_type
#define va_start(argp, ptr) (va_type)(argp = (&ptr + sizeof(ptr)))
#define va_arg(argp, type) ((type)(argp += sizeof(type)))
#define va_end(argp)

#endif	//ifndef __STDARG_H
