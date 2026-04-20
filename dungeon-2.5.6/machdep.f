C***************************************************C
C                                                   C
C  ALL THESE 'AND'S WITH 65535 ARE IMPORTANT        C
C  LEAVE THEM IN                                    C
C                                                   C
C***************************************************C
C                                                   C
C  FOR THE PC, VAX/VMS AND MY MIPS 120, THESE       C
C      WORK AS-IS.                                  C
C  FOR MANY UNIX MACHINES IAND -> AND, IOR -> OR    C
C      IEOR -> XOR                                  C
C***************************************************C
        INTEGER FUNCTION ZAND(I,J)
	IMPLICIT INTEGER(A-Z)
        ZAND = AND(AND(I,J),65535)
        RETURN
        END
        INTEGER FUNCTION ZOR(I,J)
	IMPLICIT INTEGER(A-Z)
        ZOR = AND(OR(I,J),65535)
        RETURN
        END
        INTEGER FUNCTION ZXOR(I,J)
	IMPLICIT INTEGER(A-Z)
        ZXOR = AND(XOR(I,J),65535)
        RETURN
        END
        INTEGER FUNCTION ZNOT(I)
	IMPLICIT INTEGER(A-Z)
        ZNOT = AND(XOR(I,-1),65535)
        RETURN
        END
        SUBROUTINE EXIT()
        STOP
        END
C***************************************************C
C                                                   C
C       FOR THESE TWO, YOU ARE ON YOUR OWN          C
C       ONLY ITIME REALLY MATTERS                   C
C                                                   C
C***************************************************C
	SUBROUTINE ITIME(H,M,S)
	IMPLICIT INTEGER(A-Z)
c       CALL GETTIM(H,M,S,TK)
	call gettim( h, m, s )
	RETURN
	END
        SUBROUTINE KDATE(I,J,K)
	IMPLICIT INTEGER(A-Z)
c       CALL GETDAT(I,J,K)
	i=11
	j=11
	k=11
        RETURN
        END
C***************************************************C
C                                                   C
C       THESE SHOULD BE PORTABLE                    C
C                                                   C
C***************************************************C
        SUBROUTINE INIRND(I)
	IMPLICIT INTEGER(A-Z)
        COMMON /RANSEED/J
        SAVE
        J = I
        RETURN
        END
        INTEGER FUNCTION ZRND(IRANGE)
	IMPLICIT INTEGER(A-Z)
        COMMON /RANSEED/ISEED
        SAVE
        ISEED = ISEED*69069+1
C***************************************************C
C                                                   C
C   THE ABOVE LINE IS SUPPOSED TO GENERATE          C
C   INTEGER OVERFLOWS. THEREFORE, ON VMS YOU MUST   C
C   COMPILE THIS FILE WITH /CHECK=NOOVER            C
C                                                   C
C***************************************************C
        I = 16384/IRANGE
        J = IABS(ISEED)/I
        ZRND = MOD(J,IRANGE)
        RETURN
        END
        SUBROUTINE MACHDV
        IMPLICIT INTEGER(A-Z)
        CHARACTER*20 INFMTX
        COMMON /XINFMT/ INFMTX 
        COMMON /CHAN/ INPCH,OUTCH,DBCH,ZRECL
C***************************************************C
C                                                   C
C       THE FOLLOWING 4 NUMBERS ARE FOR THE IBM-PC  C
C       AND MICROSOFT FORTRAN                       C
C                                                   C
C       FOR VAX/VMS  OR  MIPS F77 TRY 5 6 2 20      C
C       FOR F2C CONVERSIONS TRY 5 6 2 78            C
C                                                   C
C       SEE ALSO TEXTCNV.FOR                        C
C                                                   C
C***************************************************C
        INPCH = 5
        OUTCH = 6
        DBCH = 2
C       NONE OF THE ABOVE CAN BE 11, AS THAT IS USED FOR THE SAVE FILE
        ZRECL = 78
C       RECORD LENGTH FOR DIRECT ACCESS OF DTEXT.DAT        
C***************************************************C
C                                                   C
C       THE FOLLOWING WORKS FOR MOST COMPUTERS      C
C       AND F2C. SOME MACHINES MAY NEED TO HAVE     C
C       IT CHANGED TO                               C
C                                                   C
C       INFMTX='('' >''              )'
C                                                   C
C       WHILE ON SOME OTHER YOU MAY GET THE         C
C       DESIRED EFFECT BY SOME TOTALLY DIFFERENT    C
C       METHOD                                      C
C                                                   C
C***************************************************C
        INFMTX='('' >'',$            )'
C       PLEASE NOTE THAT A DOUBLE QUOTE ('') IN A STRING IS REALLY
C       A SINGLE QUOTE (')
        RETURN
        END
