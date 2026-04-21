       CHARACTER*74 BBB
       OPEN(UNIT=16,FILE='TEXTDATA.DAT',STATUS='OLD')

       OPEN(UNIT=17,FILE='DTEXT.DAT',STATUS='UNKNOWN',
     1       FORM='UNFORMATTED',ACCESS='DIRECT',
     2       RECL=78)
C        RECL SHOULD BE 78 FOR THE IBM-PC WITH MICROSOFT FORTRAN OR
C        CONVERSIONS USING F2C.
C
C        FOR VMS FORTRAN OR MIPS F77, TRY RECL = 20
C !!!!!       SEE ALSO MACHDEP.FOR    !!!!!!!!!!

       JREC = 1
1      CONTINUE
       DO 2 I=1,74
2      BBB(I:I) = ' '
       READ(16,100)IREC,BBB
100    FORMAT(I5,A74)
        do 3 i=1,74
        bbb(i:i) = char( xor( ichar(bbb(i:i)), 10 ) )
3       continue
       WRITE(17,REC=JREC)IREC,BBB
       JREC=JREC+1
       IF(IREC.NE.-1)GOTO 1
       CLOSE(16)
       CLOSE(17)
       END


