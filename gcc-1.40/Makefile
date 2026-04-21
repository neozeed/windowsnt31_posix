# Nmake macros for building Windows 32-Bit apps
CPU=i386

TARGET_CPU=i386
#TARGET_CPU=i860
#TARGET_CPU=m68k
#TARGET_CPU=ns32k
#TARGET_CPU=sparc
#TARGET_CPU=vax

TARG=config/$(TARGET_CPU)
#
#CFLAGS= /Ic:\xenixnt\h /I. /Iconfig
#CFLAGS= /Ic:\msvc32s\include /I. /Iconfig
CFLAGS= -I. -Iconfig -DTARGET_CPU_I386

#CC = cl /Od
#CC = cl /O
CC = cc
link = link
conlibs = -L/usr/lib

CC1OBJ = c-tab.o c-decl.o c-typeck.o c-conv.o toplev.o version.o \
	tree.o print-tree.o stor-layout.o fold-const.o rtl.o rtlanal.o \
	expr.o stmt.o expmed.o explow.o optabs.o varasm.o symout.o \
	dbxout.o sdbout.o emit-rtl.o integrate.o jump.o cse.o \
	loop.o flow.o stupid.o combine.o regclass.o local-alloc.o global-alloc.o \
	reload.o reload1.o caller-save.o final.o recog.o pragma.o \
	errno.o

CC1INSNOBJ = insn-emt.o insn-xrt.o insn-out.o insn-pep.o insn-rcg.o \
	obstack.o 

CC1DEPS = insn-flags.h insn-codes.h insn-config.h insn-emt.c insn-pep.c insn-rcg.c \
	insn-xrt.c insn-out.c insn-out.o

CCCPOBJ = cccp.o cexp.o version.o obstack.o alloca.o


default: cc1 cccp xgcc

alloca.o: alloca.c
	$(CC) -c $<

cc1: $(CC1DEPS) $(CC1OBJ) $(CC1INSNOBJ) insn-flags.h insn-config.h
	$(CC) -o cc1 $(CC1OBJ) $(CC1INSNOBJ) alloca.o $(conlibs)

cccp: $(CCCPOBJ)
	$(CC) -o cccp $(CCCPOBJ) $(conlibs)

cc1x.exe: $(CC1DEPS) $(CC1OBJ) $(CC1INSNOBJ) insn-flags.h insn-config.h
	$(link) $(conflags) /NODEFAULTLIB:libc.lib /NODEFAULTLIB:OLDNAMES.LIB  -out:cc1.exe $(CC1OBJ) $(CC1INSNOBJ) alloca.o $(conlibs)

genflags: c-tab.o c-decl.o c-typeck.o c-conv.o toplev.o \
	version.o tree.o print-tree.o stor-layout.o fold-const.o \
	rtl.o rtlanal.o genflags.o obstack.o \
	genflags.o rtl.o obstack.o alloca.o
	$(CC) -o genflags genflags.o rtl.o obstack.o alloca.o $(conlibs)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

gencodes: gencodes.o rtl.o obstack.o alloca.o
	$(CC) -o gencodes gencodes.o rtl.o obstack.o alloca.o $(conlibs)

genconfig: genconfig.o rtl.o obstack.o alloca.o
	$(CC) -o genconfig genconfig.o rtl.o obstack.o alloca.o $(conlibs)


genemit: expr.o stmt.o expmed.o explow.o optabs.o varasm.o \
	symout.o dbxout.o sdbout.o emit-rtl.o genemit.o \
	insn-config.h insn-flags.h
	$(CC) -o genemit genemit.o rtl.o obstack.o alloca.o $(conlibs)

genpeep: insn-emt.o integrate.o jump.o cse.o loop.o \
	flow.o stupid.o combine.o regclass.o local-alloc.o \
	global-alloc.o reload.o reload1.o caller-save.o genpeep.o \
	rtl.o obstack.o alloca.o
	$(CC) -o genpeep genpeep.o rtl.o obstack.o alloca.o $(conlibs)

genrecog: insn-pep.o final.o recog.o genrecog.o alloca.o
	$(CC) -o genrecog genrecog.o rtl.o obstack.o alloca.o $(conlibs)

genextract: insn-rcg.o genextract.o alloca.o
	$(CC) -o genextract genextract.o rtl.o obstack.o alloca.o $(conlibs)

genoutput: insn-xrt.o genoutput.o genoutput.o rtl.o obstack.o alloca.o
	$(CC) -o genoutput genoutput.o rtl.o obstack.o alloca.o $(conlibs)

expr.o: insn-flags.h insn-config.h insn-codes.h

cccp.o: cccp.c
	$(CC) -g -D__STDC__ -I. -Iconfig -c $<

insn-out.c: genoutput
	./genoutput $(TARG).md > insn-out.c

insn-xrt.c: genextract
	./genextract $(TARG).md > insn-xrt.c

insn-rcg.c: genrecog
	./genrecog $(TARG).md > insn-rcg.c

insn-flags.h: genflags
	./genflags $(TARG).md > insn-flags.h

insn-codes.h: gencodes
	./gencodes $(TARG).md > insn-codes.h

insn-config.h: genconfig
	./genconfig $(TARG).md > insn-config.h

insn-emt.c: genemit
	./genemit $(TARG).md > insn-emt.c

insn-pep.c: genpeep
	./genpeep $(TARG).md > insn-pep.c


insn-out.o: insn-out.c
	$(CC) $(CFLAGS) -D__STDC__ -I. -Iconfig -c insn-out.c

c-tab.c: c-parse.y
	bison  -v ./c-parse.y -o c-tab.c
	rm -f c-tab.output 

cexp.c: cexp.y
	bison  -v ./cexp.y -o cexp.c
	rm -f cexp.output

xgcc: gcc.o unlink.o obstack.o alloca.o version.o newargcv.o mktemp.o
	$(CC) -o xgcc gcc.o unlink.o obstack.o alloca.o version.o newargcv.o mktemp.o $(conlibs)
	

clean:
	rm -f *.o
	rm -f insn-*
	rm -f stamp-*
	rm -f c-parse.output c-tab.c cexp.c
	rm -f gencodes        genemit         genflags        genpeep \
		genconfig       genextract      genoutput       genrecog
	rm -f cc1 xgcc cccp cpp
