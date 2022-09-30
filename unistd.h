#pragma once

#ifndef __UNISTD_H
#define __UNISTD_H

// TODO - update for non ARM64 arch
typedef long INT;

INT syscall(INT number, ...);
INT open(const char *pathname, int flags);
INT close(INT fd);
size_t read(INT fd, void *buf, size_t count);
INT write(INT fd, const void *buf, size_t count);

#endif	// ifndef __UNISTD_H
