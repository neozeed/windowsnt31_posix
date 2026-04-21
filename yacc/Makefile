CFLAGS=-O -DWORD32
CC=xgcc
head: yacc 
yacc: y1.o y2.o y3.o y4.o
	cc -o yacc y?.o  -L/usr/lib
y1.o y2.o y3.o y4.o: dextern files
install:
	install -s yacc $(DESTDIR)/usr/bin
	install -c yaccpar $(DESTDIR)/usr/lib
clean :
	rm -f *.o  yacc
