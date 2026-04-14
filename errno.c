//-------------------------------------------------------------------------------
// Copyright 2022 Mark Seminatore. All rights reserved.
//-------------------------------------------------------------------------------

int errno = 0;

char *err_strings[] = {
    "Operation not permitted",		// EPERM
    "No such file or directory",	// ENOENT
    "No such process",				// ESRCH
    "Interrupted system call",		// EINTR
    "I/O error",					// EIO
    "No such device or address",	// ENXIO
    "Argument list too long",		// E2BIG
    "Exec format error",			// ENOEXEC
    "Bad file descriptor",			// EBADF
    "No child processes",			// ECHILD
    "Resource temporarily unavailable", // EAGAIN
    "Out of memory",				// ENOMEM
    "Permission denied",			// EACCES
    "Bad address",					// EFAULT
    "Device or resource busy",		// EBUSY
    "File exists",					// EEXIST
    "Cross-device link",			// EXDEV
    "No such device",				// ENODEV
    "Not a directory",				// ENOTDIR
    "Is a directory",				// EISDIR
    "Invalid argument",			    // EINVAL
    "File table overflow",			// ENFILE
    "Too many open files",			// EMFILE
    "Not a typewriter",			    // ENOTTY
    "File too large",				// EFBIG
    "No space left on device",		// ENOSPC
    "Illegal seek",				    // ESPIPE
    "Read-only file system",		// EROFS
    "Too many links",				// EMLINK
    "Broken pipe",				    // EPIPE
    "Math argument out of domain of func", // EDOM
    "Resource deadlock would occur", // EDEADLK
    "File name too long",			// ENAMETOOLONG
    "No record locks available",	// ENOLCK
    "Function not implemented",		// ENOSYS
    "Directory not empty",			// ENOTEMPTY
    "Too many symbolic links encountered", // ELOOP
    "Operation would block"		// EWOULDBLOCK
};
