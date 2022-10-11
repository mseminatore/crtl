#pragma once

#ifndef __UNISTD_H
#define __UNISTD_H

#ifndef _WIN32
// open file flags
#define O_RDONLY    0x00000000
#define O_WRONLY    0x00000001
#define O_RDWR      0x00000002

#define O_CREAT     0x00000008
#define O_APPEND    0x00000200
#define O_TRUNC     0x00000400
#define O_EXCL      0x00000800

// File modes
// Read, write, execute/search by owner
#define S_IRWXU         0000700
#define S_IRUSR         0000400
#define S_IWUSR         0000200
#define S_IXUSR         0000100
// Read, write, execute/search by group
#define S_IRWXG         0000070
#define S_IRGRP         0000040
#define S_IWGRP         0000020
#define S_IXGRP         0000010
// Read, write, execute/search by others
#define S_IRWXO         0000007
#define S_IROTH         0000004
#define S_IWOTH         0000002
#define S_IXOTH         0000001

#define S_ISUID         0004000         // set user id on execution
#define S_ISGID         0002000         // set group id on execution
#define S_ISVTX         0001000         // directory restrcted delete

INT syscall(INT number, ...);
INT open(const char *pathname, int flags, ...);
INT close(INT fd);
size_t read(INT fd, void *buf, size_t count);
INT write(INT fd, const void *buf, size_t count);

#endif

// TODO - update for non ARM64 arch
#if defined(__aarch64__)
    typedef long INT;
    typedef unsigned short mode_t;
#else
    typedef int INT;
    typedef unsigned short mode_t;
#endif

#endif	// ifndef __UNISTD_H
