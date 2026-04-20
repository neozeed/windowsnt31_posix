/* snpcal.f -- translated by f2c (version 20200916).
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

/*     SNOOPY CALENDAR PROGRAM FOR PDP-11 FORTRAN */
/*     TAKEN FROM (NON-WORKING) IBM FORTRAN+BAL VERSION */
/*     MODIFICATIONS BY T. M. KENNEDY 29-DEC-84 */

/*     COMPONENTS NEEDED ARE: */
/*       SNPCAL.FOR (THIS FILE) */
/*       SNPPIC.FOR - PICTURE DATA INTERPRETER */
/* 	   -or- */
/* 	NULPIC.FOR - NULL PICTURE NON-INTERPRETER */
/*       SNPCAL.DAT - DATA FILE FOR PICTURES */

/*     OUTPUT PRODUCED: */
/*       SNPCAL.OUT - PRINTER IMAGE OF THE DESIRED CALENDAR */

/*     HOW TO COMPILE AND LINK IT: */
/*       FORT/F77 SNPCAL.FOR/NOCK/NOTR */
/*       FORT/F77 SNPPIC.FOR/NOCK/NOTR */
/*       LINK/F77 SNPCAL,SNPCAL */

/*     THIS PROGRAM IS DESIGNED TO BE COMPILED UNDER THE PDP-11 FORTRAN-77 */
/*     COMPILER VERSION 5.0-14 OR LATER. HOWEVER, IT DOES NOT UTILIZE ANY */
/*     FORTRAN-77 EXTENSIONS, THEREFORE YOU SHULD BE ABLE TO COMPILE IT */
/*     WITH ANY ANSI 66 FORTRAN-IV, SIMPLY BY CHANGING THE OPEN STATEMENTS. */
/*     COMMENTED-OUT CODE FOR THE DEC RT-11 FORTRAN-IV COMPILER IS PROVIDED. */

/*     ****************************************************************** */
/*     *                                                                * */
/*     * PRINTS CALENDAR, ONE MONTH PER PAGE WITH PICTURES OPTIONAL.    * */
/*     *                                                                * */
/*     * BEGINNING MONTH AND YEAR, ENDING MONTH AND YEAR MUST BE PRO-   * */
/*     * VIDED IN 4(I6)  FORMAT ON A CARD IMMEDIATELY FOLLOWING         * */
/*     * CARD 98 OF DECK.                                               * */
/*     *                                                                * */
/*     * IF GRID LINES ARE DESIRED, A 1 MUST APPEAR IN COLUMN 30 OF     * */
/*     * ABOVE CARD.  A BLANK OR ZERO WILL SUPPRESS GRID LINES.         * */
/*     *                                                                * */
/*     * ALL PICTURE DATA DECKS MUST BE TERMINATED WITH CODE -2.        * */
/*     * CONSECUTIVE -2*S WILL RESULT IN NO PICTURE BEING PRINTED       * */
/*     * FOR THAT MONTH.                                                * */
/*     *                                                                * */
/*     * PICTURE FORMAT CODES --                                        * */
/*     *    -1    END OF LINE                                           * */
/*     *    -2    END OF PICTURE                                        * */
/*     *    -3    LIST CARDS, ONE PER LINE, FORMAT 13A6                 * */
/*     *    -4    LIST CARDS, TWO PER LINE, FORMAT 11A6/11A6            * */
/*     *    -5    LIST CARDS, TWO PER LINE, FORMAT 12A6/10A6            * */
/*     *                                                                * */
/*     ****************************************************************** */
/* Main program */ int MAIN__(void)
{
    /* Format strings */
    static char fmt_1[] = "(13a6)";
    static char fmt_2[] = "(11a6)";
    static char fmt_3[] = "(10a6)";
    static char fmt_4[] = "(12i6)";
    static char fmt_5[] = "(22a6)";

    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), f_clos(cllist *), s_rsfe(cilist *), do_fio(
	    integer *, char *, ftnlen), e_rsfe(void), s_wsfe(cilist *), 
	    e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, n, id, ii, mf, jm, ml, iy1, iy2, iy3, iy4;
    static doublereal cal[1320]	/* was [60][22] */, one;
    static integer iyr;
    static doublereal anam[22];
    static integer iday;
    static doublereal anum[100]	/* was [2][10][5] */;
    static integer numb, idow, nods[12], lnsw;
    static doublereal alin1, alin2, alin3, alin4, blank;
    static integer month;
    static doublereal amonth[1092]	/* was [12][7][13] */;
    extern /* Subroutine */ int snppic_(void);
    static integer lstday, mthlst, iyrlst, lpyrsw;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 2, 0, fmt_1, 0 };
    static cilist io___6 = { 0, 2, 0, fmt_2, 0 };
    static cilist io___8 = { 0, 2, 0, fmt_3, 0 };
    static cilist io___10 = { 0, 2, 0, fmt_4, 0 };
    static cilist io___12 = { 0, 2, 0, fmt_1, 0 };
    static cilist io___19 = { 0, 2, 0, fmt_4, 0 };
    static cilist io___42 = { 0, 7, 0, fmt_5, 0 };


/*     CALL OPEN (2,'SNPCAL.DAT',0,'RDO') */
    o__1.oerr = 0;
    o__1.ounit = 2;
    o__1.ofnmlen = 10;
    o__1.ofnm = "SNPCAL.DAT";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
/*     CALL OPEN (7,'SNPCAL.OUT',0,'NEW') */
    o__1.oerr = 0;
    o__1.ounit = 7;
    o__1.ofnmlen = 10;
    o__1.ofnm = "SNPCAL.OUT";
    o__1.orl = 0;
    o__1.osta = "UNKNOWN";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    cl__1.cerr = 0;
    cl__1.cunit = 7;
    cl__1.csta = "DELETE";
    f_clos(&cl__1);
/*      CLOSE (UNIT=7,DISPOSE='DELETE') */
    o__1.oerr = 0;
    o__1.ounit = 7;
    o__1.ofnmlen = 10;
    o__1.ofnm = "SNPCAL.OUT";
    o__1.orl = 0;
    o__1.osta = "NEW";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsfe(&io___1);
    for (i__ = 1; i__ <= 12; ++i__) {
	for (j = 1; j <= 7; ++j) {
	    for (k = 1; k <= 13; ++k) {
		do_fio(&c__1, (char *)&amonth[i__ + (j + k * 7) * 12 - 97], (
			ftnlen)sizeof(doublereal));
	    }
	}
    }
    e_rsfe();
    s_rsfe(&io___6);
    for (i__ = 1; i__ <= 22; ++i__) {
	do_fio(&c__1, (char *)&anam[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
    s_rsfe(&io___8);
    for (i__ = 1; i__ <= 2; ++i__) {
	for (k = 1; k <= 5; ++k) {
	    for (j = 1; j <= 10; ++j) {
		do_fio(&c__1, (char *)&anum[i__ + (j + k * 10 << 1) - 23], (
			ftnlen)sizeof(doublereal));
	    }
	}
    }
    e_rsfe();
    s_rsfe(&io___10);
    for (i__ = 1; i__ <= 12; ++i__) {
	do_fio(&c__1, (char *)&nods[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_rsfe();
    s_rsfe(&io___12);
    do_fio(&c__1, (char *)&blank, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&one, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alin1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alin2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alin3, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alin4, (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___19);
    do_fio(&c__1, (char *)&mf, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&iyr, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&mthlst, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&iyrlst, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&lnsw, (ftnlen)sizeof(integer));
    e_rsfe();
    _BLNK__1.iset = 25;
    for (i__ = 1; i__ <= 60; ++i__) {
	for (j = 1; j <= 22; ++j) {
/* L10: */
	    cal[i__ + j * 60 - 61] = blank;
	}
    }
    cal[0] = one;
    for (j = 1; j <= 22; ++j) {
/* L20: */
	cal[j * 60 - 50] = anam[j - 1];
    }
    if (lnsw != 0) {
	goto L122;
    } else {
	goto L142;
    }
L122:
    for (i__ = 20; i__ <= 60; i__ += 8) {
	for (j = 1; j <= 22; ++j) {
/* L125: */
	    cal[i__ + j * 60 - 61] = alin2;
	}
    }
    for (j = 4; j <= 19; j += 3) {
	i__ = 13;
L127:
	for (l = 1; l <= 7; ++l) {
	    cal[i__ + j * 60 - 61] = alin1;
/* L130: */
	    ++i__;
	}
	if (i__ - 55 <= 0) {
	    goto L135;
	} else {
	    goto L140;
	}
L135:
	cal[i__ + j * 60 - 61] = alin3;
	++i__;
	goto L127;
L140:
	;
    }
    for (i__ = 20; i__ <= 60; i__ += 8) {
/* L141: */
	cal[i__ - 1] = alin4;
    }
L142:
    idow = iyr - 1751 + (iyr - 1753) / 4 - (iyr - 1701) / 100 + (iyr - 1601) /
	     400;
    idow -= (idow - 1) / 7 * 7;
L55:
    if ((i__1 = iyr - iyrlst) < 0) {
	goto L60;
    } else if (i__1 == 0) {
	goto L65;
    } else {
	goto L100;
    }
L60:
    ml = 12;
    goto L70;
L65:
    ml = mthlst;
L70:
    iy1 = iyr / 1000;
    numb = iyr - iy1 * 1000;
    iy2 = numb / 100;
    numb -= iy2 * 100;
    iy3 = numb / 10;
    numb -= iy3 * 10;
    iy4 = numb;
    for (j = 1; j <= 5; ++j) {
	cal[j + 2] = anum[(iy1 + 1 + j * 10 << 1) - 21];
	cal[j + 60] = anum[(iy2 + 1 + j * 10 << 1) - 21];
	cal[j + 1200] = anum[(iy3 + 1 + j * 10 << 1) - 21];
/* L72: */
	cal[j + 1262] = anum[(iy4 + 1 + j * 10 << 1) - 21];
    }
    lpyrsw = 0;
    if (iyr - (iyr / 4 << 2) != 0) {
	goto L90;
    } else {
	goto L75;
    }
L75:
    if (iyr - iyr / 100 * 100 != 0) {
	goto L85;
    } else {
	goto L80;
    }
L80:
    if (iyr - iyr / 400 * 400 != 0) {
	goto L90;
    } else {
	goto L85;
    }
L85:
    lpyrsw = 1;
L90:
    nods[1] += lpyrsw;
    if ((i__1 = mf - 1) < 0) {
	goto L100;
    } else if (i__1 == 0) {
	goto L110;
    } else {
	goto L95;
    }
L95:
    --mf;
    i__1 = mf;
    for (month = 1; month <= i__1; ++month) {
/* L105: */
	idow += nods[month - 1];
    }
    idow -= (idow - 1) / 7 * 7;
    ++mf;
L110:
    i__1 = ml;
    for (month = mf; month <= i__1; ++month) {
	lstday = nods[month - 1];
	for (i__ = 1; i__ <= 7; ++i__) {
	    for (jm = 1; jm <= 13; ++jm) {
		j = jm + 4;
/* L115: */
		cal[i__ + j * 60 - 61] = amonth[month + (i__ + jm * 7) * 12 - 
			97];
	    }
	}
	if (idow - 1 <= 0) {
	    goto L160;
	} else {
	    goto L120;
	}
L120:
	id = idow - 1;
	j = 2;
	i__2 = id;
	for (k = 1; k <= i__2; ++k) {
	    for (i__ = 14; i__ <= 18; ++i__) {
		cal[i__ + j * 60 - 61] = blank;
/* L150: */
		cal[i__ + (j + 1) * 60 - 61] = blank;
	    }
	    j += 3;
/* L155: */
	}
L160:
	iday = 1;
	ii = 14;
L25:
	j = idow * 3 - 1;
	n = iday / 10 + 1;
	i__ = ii;
	for (k = 1; k <= 5; ++k) {
	    cal[i__ + j * 60 - 61] = anum[(n + k * 10 << 1) - 22];
/* L30: */
	    ++i__;
	}
	n = iday - n * 10 + 11;
	++j;
	i__ = ii;
	for (k = 1; k <= 5; ++k) {
	    cal[i__ + j * 60 - 61] = anum[(n + k * 10 << 1) - 21];
/* L35: */
	    ++i__;
	}
	++idow;
	if (idow - 7 <= 0) {
	    goto L45;
	} else {
	    goto L40;
	}
L40:
	idow = 1;
	ii += 8;
L45:
	++iday;
	if (iday - lstday <= 0) {
	    goto L25;
	} else {
	    goto L50;
	}
L50:
	id = idow;
L205:
	i__ = ii;
	j = id * 3 - 1;
	for (k = 1; k <= 5; ++k) {
	    cal[i__ + j * 60 - 61] = blank;
	    cal[i__ + (j + 1) * 60 - 61] = blank;
/* L210: */
	    ++i__;
	}
	if (id - 7 >= 0) {
	    goto L220;
	} else {
	    goto L215;
	}
L215:
	++id;
	goto L205;
L220:
	if (ii - 54 >= 0) {
	    goto L230;
	} else {
	    goto L225;
	}
L225:
	ii = 54;
	id = 1;
	goto L205;
L230:
	snppic_();
/*     WRITE OUTPUT TAPE 1,5,((CAL(I,J),J=1,22),I=1,60) */
	s_wsfe(&io___42);
	for (i__ = 1; i__ <= 60; ++i__) {
	    for (j = 1; j <= 22; ++j) {
		do_fio(&c__1, (char *)&cal[i__ + j * 60 - 61], (ftnlen)sizeof(
			doublereal));
	    }
	}
	e_wsfe();
/* L51: */
    }
    if (iyr - iyrlst >= 0) {
	goto L100;
    } else {
	goto L235;
    }
L235:
    nods[1] -= lpyrsw;
    ++iyr;
    mf = 1;
    goto L55;
L100:
    s_stop("", (ftnlen)0);
/* L6: */
    return 0;
} /* MAIN__ */

