#include "stddef.h"
#include "unistd.h"
#include "stdarg.h"

// 
#if defined(__APPLE_CC__)
#	include <sys/syscall.h>
#endif

//
INT open(const char *pathname, int flags, ...)
{
	// TODO - if O_CREAT is passed then the next vararg is mode flags
	mode_t mode = 0;

	if (flags & O_CREAT)
	{
		va_list argp;
		va_start(argp, flags);

		mode = va_arg(argp, mode_t);

		va_end(argp);
		return syscall(SYS_open, pathname, flags);
	}

	return syscall(SYS_open, pathname, flags);
}

//
INT close(INT fd)
{
	return syscall(SYS_close, fd);
}

//
size_t read(INT fd, void *buf, size_t count)
{
	return syscall(SYS_read, fd, buf, count);
}

//
INT write(INT fd, const void *buf, size_t count)
{
	return syscall(SYS_write, fd, buf, count);
}