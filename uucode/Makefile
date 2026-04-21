CC=xgcc
CFLAGS= -v -D_X86_=1 -D_POSIX_ -DWIN32
LDFLAGS=-L/usr/lib
OBJS = uuencode.o uudecode.o

all: uuencode uudecode

# why doesn't this pick up?
.c.o:
	$(CC) $(CFLAGS) -c $<


uudecode.o: uudecode.c
	$(CC) $(CFLAGS) -c $<

uuencode: uuencode.o
	cc uuencode.o -o uuencode $(LDFLAGS)

uudecode: uudecode.o
	cc uudecode.o -o uudecode $(LDFLAGS)

clean:
	rm -f $(OBJS)
	rm -f uuencode uudecode
