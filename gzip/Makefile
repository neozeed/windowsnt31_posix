
CC=xgcc

OBJS = bits.o   getopt.o        trees.o         unpack.o        zip.o \
crypt.o         inflate.o       unlzh.o         unzip.o \
deflate.o       lzw.o           unlzw.o         util.o gzip.o

# broken options?
OOPTS = -DNO_STDIN_FSTAT \
	-D__STDC__

CFLAGS=	-O -g -D_X86_=1 -D_POSIX_ -DWIN32 $(OPTS) 

gzip: $(OBJS)
	cc -L/usr/lib $(OBJS) -o gzip


clean:
	rm -f $(OBJS)
	rm -f gzip
