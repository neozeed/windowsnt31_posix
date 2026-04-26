!include <ntwin32.mak>

C_DEFINES=-DWIN_NT -DSTDC_HEADERS -D_POSIX_SOURCE -DDIRENT -DSTACK_DIRECTION=-1 -D__STDC__ -DDF_POSIX -D_POSIX_ -DCONVERT_TO_SLASHES -UCONVERT_TO_BACKSLASHES


PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man

OBJS = doname.obj   dosys.obj  files.obj    main.obj     misc.obj y.tab.obj

make.exe: $(OBJS)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)


.c.obj:
        $(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c

y.tab.obj: y.tab.c

y.tab.c:
	\bin\yacc gram.y

test: make
	@cd testsuite && ./runtest

clean:
	del $(OBJS) make.exe y.tab.c
