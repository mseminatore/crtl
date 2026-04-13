//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#include "stdarg.h"
#include "stdlib.h"
#include "assert.h"

#if defined(__APPLE_CC__)
#	include <sys/syscall.h>

//-------------------------------------------------------------------------------
// system call numbers for OSX
//-------------------------------------------------------------------------------
long syscall(long number, ...)
{
	long result = 0;

	// On OSX we must add 0x2000000 to form the system call number
	// add 0x2000000 to number
	// TODO - do not do this for Linux
	long sysnum = number + 0x2000000;

	va_list argp;

	va_start(argp, number);

	switch (number)
	{
	case SYS_exit:
	{
		long status = va_arg(argp, long);
		
#if defined(__aarch64__)
		asm("mov X0, %0" : : "r"(status));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
#elif defined(__x86_64__)
		asm volatile("syscall" : : "a"(sysnum), "D"(status) : "rcx", "r11", "memory");
#endif

	}
		break;

	case SYS_read:
	{
		long fd 	= va_arg(argp, long);
		char *buf 	= va_arg(argp, char*);
		size_t len 	= va_arg(argp, size_t);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(fd), "S"(buf), "d"(len)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(fd));
		asm("mov X1, %0" : : "r"(buf));
		asm("mov X2, %x0" : : "r"(len));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif
	}
		break;

	case SYS_write:
	{
		long fd 	= va_arg(argp, long);
		char *buf 	= va_arg(argp, char*);
		size_t len 	= va_arg(argp, size_t);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(fd), "S"(buf), "d"(len)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(fd));
		asm("mov X1, %0" : : "r"(buf));
		asm("mov X2, %x0" : : "r"(len));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif

	}
		break;

	case SYS_open:
	{
		char *path 	= va_arg(argp, char*);
		long flags 	= va_arg(argp, long);
		long mode 	= va_arg(argp, long);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(path), "S"(flags), "d"(mode)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(path));
		asm("mov X1, %0" : : "r"(flags));
		asm("mov X2, %x0" : : "r"(mode));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif		
	}
		break;

	case SYS_close:
	{
		long fd = va_arg(argp, long);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(fd)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(fd));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif
	}
		break;

	case SYS_unlink:
	{
		char *path = va_arg(argp, char*);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(path)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(path));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif
	}
		break;
	
	case SYS_chdir:
	{
		char *path = va_arg(argp, char*);
		
#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(path)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(path));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif
	}
		break;

	case SYS_rename:
	{
		char *oldpath = va_arg(argp, char*);
		char *newpath = va_arg(argp, char*);

#if defined(__x86_64__)
		asm volatile("syscall"
			: "=a"(result)
			: "0"(sysnum), "D"(oldpath), "S"(newpath)
			: "rcx", "r11", "memory");
#elif defined(__aarch64__)
		asm("mov X0, %0" : : "r"(oldpath));
		asm("mov X1, %0" : : "r"(newpath));
		asm("mov X16, %0" : : "r"(sysnum));
		asm("svc #0");
		asm("mov %0, X0" : "=r"(result));
#endif
	}
		break;

	case SYS_fork:
	{

	}
		break;
		
	default:
		assert(0);
		return -1;
	}

	va_end(argp);

	return result;
}

#endif
