# Copyright 2022 Mark Seminatore. All rights reserved.

TARGET	= crtl_test
LINKER	= cc -o

DEPS 	= \
string.h \
stddef.h \
assert.h \
stdio.h \
stdlib.h \
ctype.h \
test.h \
unistd.h \
stdint.h \
errno.h \
stdarg.h

OBJS	= \
stdarg.o \
string.o \
assert.o \
errno.o \
main.o \
stdio.o \
stdlib.o \
ctype.o \
syscall.o \
unistd.o \
test_string.o \
test_stdlib.o \
test_stdio.o \
test_ctype.o

CFLAGS	= -I. -g
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET):	$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
	