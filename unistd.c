//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

#include "stddef.h"
#include "unistd.h"
#include "stdarg.h"

#if defined(__APPLE_CC__) || defined(__linux__)
#	include <sys/syscall.h>
#endif

//-------------------------------------------------------------------------------
// Opens the file specified by pathname and returns a file descriptor.
//-------------------------------------------------------------------------------
INT open(const char *pathname, int flags, ...)
{
	mode_t mode = 0;

	va_list argp;
	va_start(argp, flags);

	if (flags & O_CREAT)
		mode = (mode_t)va_arg(argp, int);

	va_end(argp);

	return syscall(SYS_open, pathname, flags, mode);
}

//-------------------------------------------------------------------------------
// Closes the given file descriptor.
//-------------------------------------------------------------------------------
INT close(INT fd)
{
	return syscall(SYS_close, fd);
}

//-------------------------------------------------------------------------------
// Reads data from the given file descriptor into the array pointed to by buf.
//-------------------------------------------------------------------------------
size_t read(INT fd, void *buf, size_t count)
{
	return syscall(SYS_read, fd, buf, count);
}

//-------------------------------------------------------------------------------
// Writes data from the array pointed to by buf to the given file descriptor.
//-------------------------------------------------------------------------------
INT write(INT fd, const void *buf, size_t count)
{
	return syscall(SYS_write, fd, buf, count);
}

//-------------------------------------------------------------------------------
// Deletes the file specified by pathname.
//-------------------------------------------------------------------------------
INT unlink(const char *pathname)
{
	return syscall(SYS_unlink, pathname);
}

//-------------------------------------------------------------------------------
// Renames the file specified by oldpath to newpath.
//-------------------------------------------------------------------------------
INT _rename(const char *oldpath, const char *newpath)
{
	return syscall(SYS_rename, oldpath, newpath);
}
