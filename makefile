TARGET	= crtl.lib
LINKER	= cc -o
OBJS	= string.o assert.o
CFLAGS	= 

$(OBJS):	string.c assert.c
	$(CC) $< $(CFLAGS)

$(TARGET):	$(OBJS)
	$(LINKER) $(TARGET) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
	