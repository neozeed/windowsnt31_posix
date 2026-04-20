
OBJS = getopt.o getopt1.o regex.o sed.o utils.o alloca.o

CFLAGS=-DUSG -D__STDC__
CC=cc

sed: $(OBJS)
	cc $(OBJS) -o sed -L/usr/lib

alloca.o: alloca.c
	$(CC) $(CFLAGS) -c $*.c


