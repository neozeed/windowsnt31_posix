CC=xgcc
CCL=cc
# CFLAGS=-O -Dunix=1 -Dvax=1
CFLAGS=	-Dunix=1 -O -g  -D_X86_=1 -D_POSIX_ -DWIN32 

cpp:	cpp.o cpy.o rodata.o
	$(CCL) $(CFLAGS) -o cpp rodata.o cpp.o cpy.o  

cpp.o:	cpp.c
	$(CC) $(CFLAGS) -c $<

cpy.c: cpy.y
	yacc cpy.y
#	../as/:yyfix yyexca yyact yypact yypgo yyr1 yyr2 yychk yydef
	mv y.tab.c cpy.c
cpy.o:	cpy.c yylex.c
	$(CC) $(CFLAGS) -c $<

rodata.o: cpy.c
	$(CCL) $(CFLAGS) -c rodata.c

clean:
	rm -f *.s *.o cpy.c 

install:
	install -s cpp $(DESTDIR)/lib

