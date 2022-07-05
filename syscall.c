#include "stdarg.h"
#include "stdlib.h"
#include "assert.h"

#if defined(__APPLE_CC__)
#	include <sys/syscall.h>

//
int	syscall(int number, ...)
{
	int result = 0;

	va_list argp;

	va_start(argp, number);

	switch (number)
	{
	case SYS_exit:
	{
		int status = va_arg(argp, int);
		
#if defined(__aarch64__)
		asm("mov X0, %w0" : : "r"(status));
		asm("movz X16, #0x200, lsl 16");
		asm("add X16, X16, %0" : : "r"(number));
		asm("svc #0" : "r"(result));
#elif defined(__x86_64__)
// add 0x2000000 to number
		asm("mov rax, _ptr %0" : : "r"(number));
		asm("mov rdi, %0" : : "r"(status));
		asm("syscall" : "=r"(result));
#endif

	}
		break;

	case SYS_read:
	{

	}
		break;

	case SYS_write:
	{
		int fd = va_arg(argp, int);
		void *buf = va_arg(argp, void*);
		size_t len = va_arg(argp, size_t);

#if defined(__aarch64__)
		asm("mov X0, #0");
		asm("movz X16, #0x200, lsl 16");
		asm("add X16, X16, %0" : : "r"(number));
		asm("svc #0" : "r"(result));
#elif defined(__x86_64__)
		asm("mov rax, %0" : : "r"(number));
		asm("mov rdi, %0" : : "r"(fd));
		asm("mov rsi, %0" : : "r"(buf));
		asm("mov rdx, %0" : : "r"(len));
		asm("syscall" : "=r"(result));
#endif

	}
		break;

	case SYS_open:
		break;

	case SYS_close:
		break;

	default:
		assert(0);
		return -1;
	}

	va_end(argp);

	return result;
}

#endif
