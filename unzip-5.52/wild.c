
#define UNZIP_INTERNAL

#include "unzip.h"
#include "crypt.h"
#include "ttyio.h"
#define NAME_MAX 128
#include <dirent.h>
//#include "izqdos.h"
//#include "unzvers.h"

#ifndef SFX
char _prog_name[] = "UnZip";
#else
char _prog_name[] = "??Special Flag for unzipsfx hack  ??";
#endif

char *LastDir(char *ws)
{
    char *p;
    char *q = ws;
    struct stat s;

    for(p = ws; *p; p++)
    {
        if(*p == '_')
        {
            char c;

            p++;
            c = *p;
            *p = 0;
            if(stat(ws, &s) == 0 && S_ISDIR(s.st_mode))
            {
                q = p;
            }
            *p = c;
        }
    }
    return q;
}


/**********************/
/* Function do_wild() */   /* for porting: dir separator; match(ignore_case) */
/**********************/

char *do_wild(__G__ wildspec)
    __GDEF
    ZCONST char *wildspec;  /* only used first time on a given dir */
{
    static DIR *wild_dir = (DIR *)NULL;
    static ZCONST char *wildname;
    static char *dirname, matchname[FILNAMSIZ];
    static int notfirstcall=FALSE, have_dirname, dirnamelen;
    struct dirent *file;
    char basedir[40];

    /* Even when we're just returning wildspec, we *always* do so in
     * matchname[]--calling routine is allowed to append four characters
     * to the returned string, and wildspec may be a pointer to argv[].
     */
    if (!notfirstcall) {    /* first call:  must initialize everything */
        char *ws = NULL, *us = NULL;

        notfirstcall = TRUE;

        /* break the wildspec into a directory part and a wildcard filename */

        ws = (char *) iswild(wildspec);

        if(ws == NULL)
        {
            strncpy(matchname, wildspec, FILNAMSIZ);
            matchname[FILNAMSIZ-1] = '\0';
            return matchname;
        }

        us = LastDir(wildspec);

        if(us == wildspec)
        {
            dirname = basedir;
            Xgetcwd(basedir, sizeof(basedir)-1);
            dirnamelen = strlen(basedir);
            have_dirname = FALSE;
            wildname = wildspec;
        } else {
            wildname = us;     /* point at character after '/' */
            dirnamelen = wildname - wildspec;
            if ((dirname = (char *)malloc(dirnamelen+1)) == (char *)NULL) {
                Info(slide, 0x201, ((char *)slide,
                  "warning:  cannot allocate wildcard buffers\n"));
                strncpy(matchname, wildspec, FILNAMSIZ);
                matchname[FILNAMSIZ-1] = '\0';
                return matchname;   /* but maybe filespec was not a wildcard */
            }
            strncpy(dirname, wildspec, dirnamelen);
            dirname[dirnamelen] = '\0';   /* terminate for strcpy below */
            have_dirname = TRUE;
        }

        if ((wild_dir = opendir(dirname)) != (DIR *)NULL) {
            while ((file = readdir(wild_dir)) != (struct dirent *)NULL) {
                if (match(file->d_name, wildname, 0 WISEP)) { /* 0=case sens.*/
                    if (have_dirname) {
                        strcpy(matchname, dirname);
                        strcpy(matchname+dirnamelen, file->d_name);
                    } else
                        strcpy(matchname, file->d_name);
                    return matchname;
                }
            }
            /* if we get to here directory is exhausted, so close it */
            closedir(wild_dir);
            wild_dir = (DIR *)NULL;
        }

        /* return the raw wildspec in case that works (e.g., directory not
         * searchable, but filespec was not wild and file is readable) */
        strncpy(matchname, wildspec, FILNAMSIZ);
        matchname[FILNAMSIZ-1] = '\0';
        return matchname;
    }

    /* last time through, might have failed opendir but returned raw wildspec */
    if (wild_dir == (DIR *)NULL) {
        notfirstcall = FALSE; /* nothing left to try--reset for new wildspec */
        if (have_dirname)
            free(dirname);
        return (char *)NULL;
    }

    /* If we've gotten this far, we've read and matched at least one entry
     * successfully (in a previous call), so dirname has been copied into
     * matchname already.
     */
    while ((file = readdir(wild_dir)) != (struct dirent *)NULL) {
        if (match(file->d_name, wildname, 0 WISEP)) {   /* 0 == case sens. */
            if (have_dirname) {
                /* strcpy(matchname, dirname); */
                strcpy(matchname+dirnamelen, file->d_name);
            } else
                strcpy(matchname, file->d_name);
            return matchname;
        }
    }

    closedir(wild_dir);     /* have read at least one entry; nothing left */
    wild_dir = (DIR *)NULL;
    notfirstcall = FALSE;   /* reset for new wildspec */
    if (have_dirname)
        free(dirname);
    return (char *)NULL;

} /* end function do_wild() */
