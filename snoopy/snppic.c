/* snppic.f -- translated by f2c (version 20200916).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer iset;
} _BLNK__;

#define _BLNK__1 _BLNK__

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int snppic_(void)
{
    /* Initialized data */

    static struct {
	char e_1[4];
	integer e_2;
	} equiv_11 = { "    ", 0 };

#define iblnk (*(integer *)&equiv_11)


    /* Format strings */
    static char fmt_1000[] = "(25(i2,a1))";
    static char fmt_2000[] = "(133a1)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_rsfe(cilist *), do_fio(integer *, char *, ftnlen), e_rsfe(void),
	     s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k, l, ichr[50], inum[50], iline[133];

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 2, 0, fmt_1000, 0 };
    static cilist io___9 = { 0, 7, 0, fmt_2000, 0 };


/*     THIS SUBROUTINE WILL ANALYZE THE INPUT DATA AND PRINT A PICTURE */
/*     YOU CAN EXPECT TO GET 1 WARNING MESSAGE DURING COMPILATION */
    for (i__ = 1; i__ <= 133; ++i__) {
/* L4: */
	iline[i__ - 1] = iblnk;
    }
/* L5: */
    k = 1;
L10:
    s_rsfe(&io___5);
    i__1 = _BLNK__1.iset;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&inum[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ichr[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_rsfe();
    i__1 = _BLNK__1.iset;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (inum[i__ - 1] != -1) {
	    goto L100;
	}
/*     HERE WE WRITE A LINE TO THE PRINTER AND GO BUILD ANOTHER */
	for (l = k; l <= 133; ++l) {
/* L15: */
	    iline[l - 1] = ichr[i__ - 1];
	}
	s_wsfe(&io___9);
	for (k = 1; k <= 133; ++k) {
	    do_fio(&c__1, (char *)&iline[k - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
	iline[0] = iblnk;
	for (k = 2; k <= 133; ++k) {
/* L20: */
	    iline[k - 1] = ichr[i__ - 1];
	}
	k = 1;
/* error      I=I+1 */
L100:
	if (inum[i__ - 1] == -2) {
	    goto L200;
	}
	if (inum[i__ - 1] == 0) {
	    goto L40;
	}
	i__2 = inum[i__ - 1];
	for (j = 1; j <= i__2; ++j) {
	    iline[k - 1] = ichr[i__ - 1];
	    ++k;
/* L30: */
	}
L40:
	;
    }
    goto L10;
/*     HERE WE EXIT THE PICTURE AND RETURN TO THE CALLING PROGRAM */
L200:
    return 0;
/*     FORMAT STATEMENTS */
} /* snppic_ */

#undef iblnk


