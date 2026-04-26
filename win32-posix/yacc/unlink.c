#if 0
#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _POSIX_SOURCE /* DF_MSS */
#include <errno.h>
#else
#include <sys/errno.h>
#endif

#include <fts.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#else

int Xunlink(const char *p){
return unlink(p);}
#endif

