# native CC
CC =  xgcc

LIBS = -lgnulib -L/usr/lib
CFLAGS = -msoft-float -O -g


OBJ = astro.o date_p.o phoon.o

all: phoon

astro.o: astro.c
	$(CC) $(CFLAGS) -c $<



phoon: $(OBJ)
	cc -o phoon $(OBJ) $(LIBS)


clean:
	rm -f $(OBJ)
	rm -f phoon

