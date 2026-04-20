# native CC
CC = xgcc


LIBS = -L/usr/lib

WHETOBJ = whet.o

LINOBJ = linpack.o

DHRYOBJ2 = dhry21a.o dhry21b.o timers.o

DHRYOBJ = dhry.o


all: whet lin dhry dhry2
#all: whet
#all: dhry
#all: dhry2
#all: lin

dhry.o:
	$(CC) $(CFLAGS) -c dhry.c


whet: $(WHETOBJ)
	cc -o whet $(WHETOBJ) $(LIBS)


lin: $(LINOBJ)
	cc -o lin $(LINOBJ) $(LIBS)


dhry: $(DHRYOBJ)
	cc -o dhry $(DHRYOBJ) $(LIBS)

dhry2: $(DHRYOBJ2)
	cc -o dhry2 $(DHRYOBJ2) $(LIBS)

clean:
	rm -f $(WHETOBJ) $(LINOBJ) $(DHRYOBJ) $(DHRYOBJ2)
	rm -f whet lin dhry dhry2

