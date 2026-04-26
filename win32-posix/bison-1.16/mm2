!include <ntwin32.mak>

C_DEFINES=-DWIN_NT -DSTDC_HEADERS -D_POSIX_SOURCE -DDIRENT -DSTACK_DIRECTION=-1 -D__STDC__ -DDF_POSIX -D_POSIX_ -DCONVERT_TO_SLASHES -UCONVERT_TO_BACKSLASHES

all: bison.exe

OBJS = allocate.obj    bcopy.obj       closure.obj     conflicts.obj   derives.obj\
files.obj       getargs.obj     getopt.obj      getopt1.obj     gram.obj\
lalr.obj        lex.obj         LR0.obj         main.obj        mktemp.obj\
nullable.obj    output.obj      print.obj       reader.obj      reduce.obj\
symtab.obj      version.obj     warshall.obj    \

bison.exe: $(OBJS)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

.c.obj:
        $(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c


clean:
	del $(OBJS)
	del bison.exe
