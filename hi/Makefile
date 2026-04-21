CC=xgcc
CFLAGS= -v -D_X86_=1 -D_POSIX_ -DWIN32
LDFLAGS=-L/usr/lib
OBJS = hi.o

all: hi

.c.o:
	$(CC) $(CFLAGS) -c $<

hi.o: hi.c
	$(CC) $(CFLAGS) -c $<

hi: $(OBJS)
	cc $(OBJS) -o hi $(LDFLAGS)
	rm -f hi.o
	./hi
	rm -f hi

clean:
	rm -f $(OBJS)
	rm -f hi
