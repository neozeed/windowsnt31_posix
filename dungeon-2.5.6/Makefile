# Makefile for Dungeon.
# Note: as of this date (Sept 1998), the Gnu fortran compiler will not
# compile Dungeon, because of some unimplemented intrinsic functions
# which are needed.  The free f2c compiler from 
#
# 	http://netlib.bell-labs.com/netlib/f2c/
#
# compiles the sources quite competently.  It should also be available
# in most Linux and *BSD distributions.

FC = f2c
FFLAGS = -A -C -Nn802 -T/tmp
CFLAGS = -O
LDFLAGS = -L/usr/lib

DOBJS = actors.o ballop.o clockr.o demons.o dgame.o dmain.o dso.o \
	dsub.o dverb1.o dverb2.o gdt.o machdep.o nobjs.o np.o np2.o \
	objcts.o rooms.o sverbs.o verbs.o villns.o 

all:	dungeon textcnv

dungeon: $(DOBJS) gettim.o
	$(CC) -o dungeon $(DOBJS) gettim.o -lf2c $(LDFLAGS)

.c.o:
	$(FC) $(FFLAGS) $*.f
	$(CC) $(CFLAGS) -c $*.c -o $<
	
.f.c:
	$(FC) $(FFLAGS) $<


textcnv: textcnv.c textcnv.o
	$(CC) -o textcnv textcnv.o $(LDFLAGS) -lf2c

# The gettim.C function enables Dungeon to keep track of the elapsed
# time in the game.  The uppercase suffix normally indicates a C++
# program, so it is overridden.  That way, "make clean" will not remove
# the one C program which must be kept.

gettim.o: gettim.C
	$(CC) -O -c gettim.C
	mv gettim.obj gettim.o

gettim.C: gettim.CC
	cp gettim.CC gettim.C

libdungeon.a:
	rm -f libdungeon.a
	ar rcuv libdungeon.a *.o
	ar d libdungeon.a dmain.o np2.o
#	\ranlib libdungeon.a

clean:
	-\rm -f *.c *.o textcnv dungeon dungeon.s
