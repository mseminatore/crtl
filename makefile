TARGET	= crtl.lib
LINKER	= cc -o
OBJS	= string.o
CFLAGS	= 

$(OBJS):	string.c
	$(CC) $< $(CFLAGS)

$(TARGET):	$(OBJS)
	$(LINKER) $(TARGET) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
	