
//
int open(const char *pathname, int flags)
{
	return -1;
}

// //
int close(int fd)
{
	return syscall(SYS_close, fd);
}

// //
size_t read(int d, void *buf, size_t count)
{
	return syscall(SYS_read, buf, count);
}

// //
int write(int fd, const void *buf, size_t count)
{
	return syscall(SYS_write, buf, count);
}