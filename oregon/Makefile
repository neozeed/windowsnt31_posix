
CC = cc
F77 = f2c
FFLAGS = -T/tmp
CFLAGS = -g 
OBJS = f2c.o oregon.o

oregon: $(OBJS)
	cc $(OBJS) -o oregon -L/usr/lib -lf2c

oregon.c: oregon.f
	$(F77) $(FFLAGS) oregon.f

oregon.o: oregon.c
	$(CC) $(CFLAGS) -c oregon.c

f2c.o: f2c.c
	$(CC) $(CFLAGS) -c f2c.c

clean:
	rm -f oregon.c $(OBJS) oregon

