/* Small function designed to be called from Fortran as a   */
/* substitute for the DOS / VAX function called GETTIM. It  */
/* is called as						    */

/*		CALL GETTIM( IHOUR, IMIN, ISEC)		    */

/* where IHOUR, IMIN, and ISEC are all integer*4 variables  */
/* which are set by this routine.  The time which is	    */
/* returned is the GMT time of day. -- Rick Slater, NRL     */

//#include <sys/time.h>
#include <time.h>


void gettim_ ( long *ihr, long *imin, long *isec) {

#if 0
/* Use the BSD gettimeofday() kernel service.               */
struct timeval tp;
struct timezone tzp;

gettimeofday( &tp, &tzp );
#endif

/* the structure member tp.tv_sec contains seconds since    */
/* 1/1/70 as a long integer.  Convert it to hours mod 24,   */
/* minutes, and seconds, to get the current GMT time.       */

*ihr = 1;//tp.tv_sec / 3600L;   /* don't do mod 24 quite yet */
*imin = 3;//( tp.tv_sec - (*ihr) * 3600L ) / 60L;
*isec =5;// tp.tv_sec % 60L;
*ihr =3;// (*ihr) % 24L;
}
