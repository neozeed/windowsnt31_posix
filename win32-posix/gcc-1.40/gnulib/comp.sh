export PATH=/bin
/bin/xgcc -I.. -I/usr/include -DBITS_PER_WORD=32 -DBITS_PER_UNIT=8 -D$1 -c ../gnulib2.c -o $1.obj
