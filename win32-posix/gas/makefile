!include <ntwin32.mak>

C_DEFINES=-DWIN_NT -DUSG -DSTDC_HEADERS -D_POSIX_SOURCE -DDIRENT -DSTACK_DIRECTION=-1 -D__STDC__ -DDF_POSIX -D_POSIX_ -DCONVERT_TO_SLASHES -UCONVERT_TO_BACKSLASHES


A = as.obj xrealloc.obj xmalloc.obj hash.obj hex-value.obj \
	atof-generic.obj append.obj messages.obj expr.obj app.obj \
	frags.obj input-file.obj input-scrub.obj output-file.obj \
	subsegs.obj symbols.obj version.obj flonum-const.obj \
	flonum-copy.obj flonum-mult.obj bignum-copy.obj obstack.obj

X386 = i386.obj atof-ieee.obj write.obj read.obj


U386 = xenixomf.obj omfwrite.obj

XOBJ = $(A) $(X386) $(U386)


# CFLAGS = /DUSG=1 /D_WIN32
.c.obj:
        $(cc) $(cflags) $(psxvars) $(cvars) $(cdebug) $(C_DEFINES) $(C_INCLUDES) $*.c


default: ax386.exe

ax386.exe: $(XOBJ)
	$(link) $(linkdebug) $(psxflags) -out:$*.exe $** $(psxlibs)


clean:
	@del $(OBJ)
	@del ax386.exe
