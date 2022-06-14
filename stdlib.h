// Copyright 2022 Mark Seminatore. All rights reserved.
#ifndef __STDLIB_H
#define __STDLIB_H

#include "stddef.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void __exit(int status);
int atoi(const char *str);

#endif // __STDLIB_H
