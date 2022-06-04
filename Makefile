TARGET	= crtl_test
LINKER	= cc -o
DEPS 	= string.h stddef.h assert.h stdio.h stdlib.h
OBJS	= string.o assert.o main.o stdio.o stdlib.o
CFLAGS	= -I. -g
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET):	$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
	