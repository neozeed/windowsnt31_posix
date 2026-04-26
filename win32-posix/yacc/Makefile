!include <ntwin32.mak>

C_DEFINES=-DWIN_NT -DSTDC_HEADERS -D_POSIX_SOURCE -DDIRENT -DSTACK_DIRECTION=-1 -D__STDC__ -DDF_POSIX -D_POSIX_ -DCONVERT_TO_SLASHES -UCONVERT_TO_BACKSLASHES


PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man

OBJS = y1.obj   y2.obj   y3.obj   y4.obj unlink.obj

yacc.exe: $(OBJS)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)


.c.obj:
        $(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c

clean:
	del $(OBJS) yacc.exe
