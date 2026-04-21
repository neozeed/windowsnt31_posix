

F77 = f2c
FFLAGS = -T/tmp

all: snoopy


OBJS = snpcal.o snppic.o
CTRAN = snpcal.c snppic.c

snoopy: $(OBJS)
	cc $(OBJS) -o snoopy -lf2c -L/usr/lib

snpcal.o: snpcal.c
	$(CC) -c snpcal.c

snppic.o: snppic.c
	$(CC) -c snppic.c

snpcal.c: snpcal.f
	$(F77) $(FFLAGS) snpcal.f

snppic.c: snppic.f
	$(F77) $(FFLAGS) snppic.f


clean:
	rm -f snoopy $(OBJS) $(CTRAN)
