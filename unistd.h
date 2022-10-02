#pragma once

#ifndef __UNISTD_H
#define __UNISTD_H

// open file flags
#define O_RDONLY    0x00000000
#define O_WRONLY    0x00000001
#define O_RDWR      0x00000002

#define O_CREAT     0x00000008
#define O_APPEND    0x00000200

// TODO - update for non ARM64 arch
typedef long INT;

INT syscall(INT number, ...);
INT open(const char *pathname, int flags, ...);
INT close(INT fd);
size_t read(INT fd, void *buf, size_t count);
INT write(INT fd, const void *buf, size_t count);

#endif	// ifndef __UNISTD_H
