#include "stddef.h"
#include "unistd.h"

// 
#if defined(__APPLE_CC__)
#	include <sys/syscall.h>
#endif

//
INT open(const char *pathname, int flags)
{
	return -1;
}

// //
INT close(INT fd)
{
	return syscall(SYS_close, fd);
}

// //
size_t read(INT fd, void *buf, size_t count)
{
	return syscall(SYS_read, fd, buf, count);
}

// //
INT write(INT fd, const void *buf, size_t count)
{
	return syscall(SYS_write, fd, buf, count);
}