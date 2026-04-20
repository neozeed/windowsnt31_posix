# native CC
CC = cc
CFLAGS =



LIBS = -lgnulib -L/usr/lib

OBJS=   abandon.o attack.o autover.o capture.o check_out.o checkcond.o \
        compkl.o computer.o damage.o damaged.o dcrept.o destruct.o \
        dock.o dumpgame.o dumpme.o dumpssradio.o events.o externs.o \
        getcodi.o getpar.o help.o impulse.o initquad.o kill.o klmove.o \
        lose.o lrscan.o move.o nova.o out.o phaser.o play.o ram.o \
        ranf.o rest.o schedule.o score.o setup.o setwarp.o \
        shield.o snova.o srscan.o systemname.o torped.o utility.o \
        visual.o warp.o win.o cgetc.o nullsleep.o main.o



all: trek

abandon.o:
	${CC} ${CFLAGS} -c $*.c

.c.o:
	${CC} ${CFLAGS} -c $*.c


trek: $(OBJS)
	cc -o trek $(OBJS) $(LIBS)


clean:
	rm -f $(OBJS)
	rm -f trek

