!include <ntwin32.mak>

C_DEFINES=-DWIN_NT -DSTDC_HEADERS -D_POSIX_SOURCE -DDIRENT -DSTACK_DIRECTION=-1 -D__STDC__ -DDF_POSIX -D_POSIX_ -DCONVERT_TO_SLASHES -UCONVERT_TO_BACKSLASHES
C_INCLUDES=-I. -Iconfig -DTARGET_CPU_I386


# Nmake macros for building Windows 32-Bit apps
CPU=i386

TARGET_CPU=i386
#TARGET_CPU=i860
#TARGET_CPU=m68k
#TARGET_CPU=ns32k
#TARGET_CPU=sparc
#TARGET_CPU=vax

TARG=config\$(TARGET_CPU)
#
#CFLAGS= /Ic:\xenixnt\h /I. /Iconfig
#CFLAGS= /Ic:\msvc32s\include /I. /Iconfig
CFLAGS= -I. -Iconfig -DTARGET_CPU_I386

#CC = cl /Od
#CC = cl /O
#CC = cc
#link = link
#conlibs = -L/usr/lib

CC1OBJ = c-tab.obj c-decl.obj c-typeck.obj c-conv.obj toplev.obj version.obj \
	tree.obj print-tree.obj stor-layout.obj fold-const.obj rtl.obj rtlanal.obj \
	expr.obj stmt.obj expmed.obj explow.obj optabs.obj varasm.obj symout.obj \
	dbxout.obj sdbout.obj emit-rtl.obj integrate.obj jump.obj cse.obj \
	loop.obj flow.obj stupid.obj combine.obj regclass.obj local-alloc.obj global-alloc.obj \
	reload.obj reload1.obj caller-save.obj final.obj recog.obj pragma.obj \
	errno.obj alloca.obj

CC1INSNOBJ = insn-emt.obj insn-xrt.obj insn-out.obj insn-peep.obj insn-rcg.obj \
	obstack.obj 

CC1DEPS = insn-flags.h insn-codes.h insn-config.h insn-emt.c insn-peep.c insn-rcg.c \
	insn-xrt.c insn-out.c insn-out.obj

CCCPOBJ = cccp.obj cexp.obj version.obj obstack.obj alloca.obj


default: cc1.exe cccp.exe xgcc.exe gnulib.lib


cc1.exe: $(CC1DEPS) $(CC1OBJ) $(CC1INSNOBJ) insn-flags.h insn-config.h
	$(link) $(linkdebug) $(psxflags) -out:$*.exe insn-out.obj $(CC1OBJ) $(CC1INSNOBJ) $(psxlibs)

cccp.exe: $(CCCPOBJ)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

cc1x.exe: $(CC1DEPS) $(CC1OBJ) $(CC1INSNOBJ) insn-flags.h insn-config.h
	$(link) $(conflags) /NODEFAULTLIB:libc.lib /NODEFAULTLIB:OLDNAMES.LIB  -out:cc1.exe $(CC1OBJ) $(CC1INSNOBJ) alloca.obj $(conlibs)

genflags.exe: genflags.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

.c.obj:
	$(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c


gencodes.exe: gencodes.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

genconfig.exe: genconfig.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)


genemit.exe: genemit.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

genpeep.exe: genpeep.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

GENRECOG=genrecog.obj rtl.obj obstack.obj alloca.obj
genrecog.exe: insn-config.h $(GENRECOG)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $(GENRECOG) $(psxlibs)

genextract.exe: genextract.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

genoutput.exe: genoutput.obj rtl.obj obstack.obj alloca.obj
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

expr.obj: insn-flags.h insn-config.h insn-codes.h
	$(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c

cccp.obj: cccp.c
#	$(CC) -g -D__STDC__ -I. -Iconfig -c $<
	$(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c

insn-out.c: genoutput.exe
	genoutput $(TARG).md > insn-out.c

insn-xrt.c: genextract.exe
	genextract $(TARG).md > insn-xrt.c

insn-rcg.c: genrecog.exe
	genrecog $(TARG).md > insn-rcg.c

insn-flags.h: genflags.exe
	genflags $(TARG).md > insn-flags.h

insn-codes.h: gencodes.exe
	gencodes $(TARG).md > insn-codes.h

insn-config.h: genconfig.exe
	genconfig $(TARG).md > insn-config.h

insn-emt.c: genemit.exe
	genemit $(TARG).md > insn-emt.c

insn-peep.c: genpeep.exe
	genpeep $(TARG).md > insn-peep.c


insn-out.obj: insn-out.c
	$(CC) $(CFLAGS) -D__STDC__ -I. -Iconfig -c insn-out.c

c-tab.c: c-parse.y
	\bin\bison  -v c-parse.y -o c-tab.c
	del  c-tab.output 

cexp.c: cexp.y
	\bin\bison  -v cexp.y -o cexp.c
	del cexp.output

xgcc.exe: gcc.obj unlink.obj obstack.obj alloca.obj version.obj newargcv.obj mktemp.obj
#	$(CC) -o xgcc gcc.obj unlink.obj obstack.obj alloca.obj version.obj newargcv.obj mktemp.obj $(conlibs)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)

gnulib.lib: _gnulib.obj
	lib32 -DEBUGTYPE:BOTH -MACHINE:$(CPU) -SUBSYSTEM:posix -OUT:$*.lib $** 

clean:
	del *.obj
	del insn-*
	del stamp-*
	del c-parse.objutput c-tab.c cexp.c
	del gencodes.exe genemit.exe genflags.exe genpeep.exe \
		genconfig.exe genextract.exe  genoutput.exe genrecog.exe
	del cc1.exe xgcc.exe cccp.exe cpp.exe
	del gnulib.lib
	del *.ilk *.pdb *.exe