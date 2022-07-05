#include "stdarg.h"

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

		asm("mov X0, %w0" : : "r"(status));
		asm("movz X16, #0x200, lsl 16");
		asm("add X16, X16, %0" : : "r"(number));
		asm("svc #0" : "r"(result));
	}
	break;

	case SYS_read:
		break;

	case SYS_write:
	{
		int status = va_arg(argp, int);

		asm("mov X0, #0");
		asm("movz X16, #0x200, lsl 16");
		asm("add X16, X16, %0" : : "r"(number));
		asm("svc #0" : "r"(result));

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
