# Copyright 2022 Mark Seminatore. All rights reserved.

TARGET	= crtl_test
LINKER	= cc -o
LIBNAME = libcrtl.a
#CFLAGS += -g -O2 #-D_DEBUG #-DNDEBUG
CFLAGS	+= -I. -g
LIBS =

DEPS 	= \
malloc/mm.h \
math.h \
string.h \
stddef.h \
assert.h \
stdio.h \
stdlib.h \
ctype.h \
testy/test.h \
unistd.h \
stdint.h \
errno.h \
limits.h \
config.h \
stdarg.h

OBJS	= \
malloc/mm.o \
math.o \
string.o \
assert.o \
errno.o \
stdio.o \
stdlib.o \
ctype.o \
syscall.o \
unistd.o

TEST_OBJS = \
test_string.o \
test_stdlib.o \
test_stdio.o \
test_math.o \
test_main.o \
testy/test_main.o \
test_ctype.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(LIBNAME) $(TARGET)
	
$(LIBNAME): $(OBJS)
	ar rcs $(LIBNAME) $(OBJS)

$(TARGET):	$(LIBNAME) $(TEST_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: $(TARGET)
	./$(TARGET)

test-release:
	$(MAKE) clean
	$(MAKE) CFLAGS="-I. -g -DNDEBUG"
	./$(TARGET)
	$(MAKE) clean
	$(MAKE) CFLAGS="-I. -g"

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(LIBNAME) malloc/mm.o
	