TARGET	= crtl_test
LINKER	= cc -o
DEPS 	= string.h stddef.h assert.h stdio.h stdlib.h ctype.h test.h
OBJS	= string.o assert.o main.o stdio.o stdlib.o ctype.o test_string.o test_stdlib.o test_ctype.o
CFLAGS	= -I. -g
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET):	$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
	