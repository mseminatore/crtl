#pragma once

#ifndef __UNISTD_H
#define __UNISTD_H

int	syscall(int number, ...);
int open(const char *pathname, int flags);
int close(int fd);
size_t read(int d, void *buf, size_t count);
int write(int fd, const void *buf, size_t count);

#endif	// ifndef __UNISTD_H
