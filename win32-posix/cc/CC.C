/*
      File : cc.c

      Author : C S Palkar

      Function : Front end for 'cc' to be POSIX complient

      Details : The 'cc' command will be invoked it options
                scaned for validity and an equivalent command
                constructed for the native C compiler, this
                command is passed to a deamon OR if possible
                execed.

      Date : 17 June 93
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PNULL(p)          (p*)NULL
#define RNULL             PNULL(rev_cell)
#define NNULL             PNULL(nat_cell)
#define GNULL             PNULL(gnu_cell)
#define SNULL             PNULL(char)

#define OPT_TAG           '-'       /* Option tag */
#define EQU               '='       /* EQU */
#define NL                "\n"      /* EOL */
#define OP_CHAR           '/'      /* native opt tag */
#define SP_CHAR           ' '       /* native arg sep */
#define CNULL             '\0'      /* string terminator */

#define VAR_SEP           ':'      /* Inc var Path seperator */
#define PT_SEP            "/"      /* Path seperator */
#define CWD               "cwd"     /* Delmiter for path list */

#define ST_LIST           "["       /* Trial list start */
#define SP_LIST           "|"       /* Trial list end */
#define ED_LIST           "]"       /* Trial list end */

#define LIB_PATH          "LIB"     /* Lib path env var */
#define NO_LINK           "c"       /* Opt for no lnk */

#define LIB_PPATH         "LIB"     /* Lib path */
#define INC_PATH          "POSIX_INC"     /* Env var for inc path */
#define LIBST             "lib"     /* Lib name */
#define LEXT              ".a"      /* Lib name */
#define HOST_CC           "cl386"   /* Host 'C' complier */
#define TMP_ENV           "TMP"     /* Env var for tmp dir */
#define TMP_DIR           "/tmp"    /* Default tmp dir */
#define option(a)   ((a) == OPT_TAG )

#ifdef DEAMON
#define   D_TMP           "tmp.cc"      /* Input of deamon */
#define   D_IN            "devsem.ini"  /* Input of deamon */
#define   D_OUT           "devsem.out"  /* Output of deamon */
#define   D_ERR           "devsem.err"  /* Error of deamon */
#endif

typedef enum { FALSE , TRUE , JOIN } boolean;

typedef enum                 /* trail list flag */
{
   NO,                  /* No trail list */
   REV,                 /* Reserved list */
   OPEN,                /* Open     list */
   PPATH,                /* Lib paths     */
   LIBS                 /* Lib type      */
} t_info;

typedef struct               /* Trail list name and it native equivalent */
{
   char const *gnu_name;
   char const *nat_name;
} rev_cell , rev_list[];

typedef struct nat_dummy
{
   char const *nat_name;           /* Native option name */
   struct nat_dummy *after_ptr;    /* After pos for order */
   rev_cell *tran_list;            /* Ptr to list of reserved opts */
} nat_cell, nat_list[];

typedef struct 
{
   char const *opt_name;        /* Option name */
   t_info     trail_info;       /* Trail flag */
   rev_cell   *rev_lst;         /* Ptr to trail info */
   char const *opn_lst;         /* Disc list for Usage */
   nat_cell   *nat_ptr;         /* Ptr to equiv native option */
} gnu_cell, gnu_list[];

#if DEAMON
typedef struct
{
   char tmp_file[256];
   char out_file[256];
   FILE *de_in;
   FILE *de_out;
   FILE *de_err;
} dm_struct;
#endif

typedef struct dummy
{
   struct dummy *nxt;
   char *token;
   boolean optn;
} cmd_cell, *cmd_ptr;

/*
	Tables which will help translation
*/
rev_list m_rev_lst =
{
	{ SNULL , SNULL }
};

nat_list nat_lst =
{
	{ "P"    , NNULL , RNULL  },      /* 0 */
	{ "Zd"   , NNULL , RNULL  },      /* 1 */
	{ "c"    , NNULL , RNULL  },      /* 2 */
	{ "Fa"   , NNULL , RNULL  },      /* 3 */
	{ "Fs"   , NNULL , RNULL  },      /* 4 */
	{ "E"    , NNULL , RNULL  },      /* 5 */
	{ "Za"   , NNULL , RNULL  },      /* 6 */
	{ "Ox"   , NNULL , RNULL  },      /* 7 */
	{ "w"    , NNULL , RNULL  },      /* 8 */
	{ "DLL"  , NNULL , RNULL  },      /* 9 */
	{ "W0"   , NNULL , RNULL  },      /* 10 */
	{ "W1"   , NNULL , RNULL  },      /* 11 */
	{ "W2"   , NNULL , RNULL  },      /* 12 */
	{ "link" , NNULL , RNULL  },      /* 13 */
	{ "Fpc"  , NNULL , RNULL  },      /* 14 */
	{ "Gc"   , NNULL , RNULL  },      /* 15 */
	{ "C"    , NNULL , RNULL  },      /* 16 */
	{ "I"    , NNULL , RNULL  },      /* 17 */
	{ "X"    , NNULL , RNULL  },      /* 18 */
	{ "D"    , NNULL , RNULL  },      /* 19 */
	{ "U"    , NNULL , RNULL  },      /* 20 */
        { "Fe"   , NNULL , RNULL  },      /* 21 */
	{ SNULL , NNULL , RNULL  }
};

gnu_list gnu_lst =
{
	{ "P"           , NO , RNULL , SNULL ,  nat_lst },
	{ "traditional" , NO , RNULL , SNULL ,  NNULL },
	{ "go"          , NO , RNULL , SNULL ,  nat_lst + 1 },
	{ "f"           , NO , RNULL , SNULL ,  NNULL },
	{ "t"           , NO , RNULL , SNULL ,  NNULL },
	{ "c"           , NO , RNULL , SNULL ,  nat_lst + 2 },
	{ "o"           , OPEN , RNULL , "<file>" ,  nat_lst + 21 },
	{ "S"           , NO , RNULL , SNULL ,  nat_lst + 4 },
	{ "E"           , NO , RNULL , SNULL ,  nat_lst + 5 },
	{ "v"           , NO , RNULL , SNULL ,  NNULL },
	{ "pipe"        , NO , RNULL , SNULL ,  NNULL },
	{ "B"           , OPEN , RNULL , "<path-prefix>" ,  NNULL },
	{ "b"           , NO , RNULL , SNULL ,  NNULL },
	{ "ansi"        , NO , RNULL , SNULL ,  nat_lst + 6 },
	{ "pedantic"    , NO , RNULL , SNULL ,  NNULL },
	{ "O"           , NO , RNULL , SNULL ,  nat_lst + 7 },
	{ "g"           , NO , RNULL , SNULL ,  nat_lst + 1 },
	{ "w"           , NO , RNULL , SNULL ,  nat_lst + 8 },
	{ "static"      , NO , RNULL , SNULL ,  nat_lst + 10 },
	{ "Wimplicit"   , NO , RNULL , SNULL ,  nat_lst + 12 },
	{ "Wrettype"    , NO , RNULL , SNULL ,  nat_lst + 12 },
	{ "Wunused"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wswitch"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wcomment"    , NO , RNULL , SNULL ,  NNULL },
	{ "Wtrigraph"   , NO , RNULL , SNULL ,  NNULL },
	{ "Wall"        , NO , RNULL , SNULL ,  nat_lst + 11 },
	{ "Wshadow"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wid="        , NO , RNULL , SNULL ,  NNULL },
	{ "Wpointer-arith", NO , RNULL , SNULL ,  NNULL },
	{ "Wcast-qual", NO , RNULL , SNULL ,  NNULL },
	{ "Wwrite-strings", NO , RNULL , SNULL ,  NNULL },
	{ "p"             , NO , RNULL , SNULL ,  NNULL },
	{ "pg"            , NO , RNULL , SNULL ,  NNULL },
	{ "l"            , LIBS , RNULL , "<libname>" ,  nat_lst + 13 },
	{ "L"            , PPATH , RNULL , "<libpath>" ,  nat_lst },
	{ "nostdlib"     , NO , RNULL , SNULL ,  NNULL },
	{ "mmachinspec" , NO , RNULL , SNULL , NULL },
	{ "msoft-float" , NO , RNULL , SNULL , nat_lst + 14 },
	{ "mshort" , NO , RNULL , SNULL , NULL },
	{ "mnobitfield" , NO , RNULL , SNULL , NULL },
	{ "mbitfield" , NO , RNULL , SNULL , NULL },
	{ "mrtd" , NO , RNULL , SNULL , nat_lst + 15 },
	{ "munix" , NO , RNULL , SNULL , NULL },
	{ "mgnu" , NO , RNULL , SNULL , NULL },
	{ "mg" , NO , RNULL , SNULL , NULL },
	{ "mno-epilogue" , NO , RNULL , SNULL , NULL },
	{ "C" , NO , RNULL , SNULL , nat_lst + 16 },
	{ "I" , OPEN , RNULL , "<include-path>" , nat_lst + 17 },
	{ "nostatic" , NO , RNULL , SNULL , nat_lst + 18 },
	{ "MM" , NO , RNULL , SNULL , NNULL },
	{ "M" , NO , RNULL , SNULL , NNULL },
	{ "D" , OPEN , RNULL , "<macro>" , nat_lst + 19 },
	{ "U" , OPEN , RNULL , "<macro>" , nat_lst + 20 },
	{ SNULL , OPEN , RNULL , SNULL , NNULL }
};

cmd_cell head_cell , *head_ptr , *end_ptr;
cmd_cell lib_cell , *lib_ptr , *lend_ptr;
cmd_cell path_cell , *path_ptr , *pend_ptr;

int chk_lnk = 1; /* Wether no link has been encountered */
int no_link = 0; /* Set when -c option is encountered */
int no_path = 1; /* No link path added */

char *link_opts[] = /* Default linker options */
{
   "link",
   "subsystem:posix",
   "entry:__PosixProcessStartup",
   SNULL
};

char *def_lib[] = /* Default library */
{
   "libcpsx.lib",
   "psxdll.lib",
   "ntdll.lib",
   "psxrtl.lib",
   "-nodefaultlib:libc.lib",
   "-nodefaultlib:oldnames.lib",
   "-nodefaultlib:kernel32.lib",
   SNULL
};

/*
       Function : display_rev_lst()

       Discription : To display reserved word(s) with option

       Called by : usage()
*/
void
#ifdef __STDC__
display_rev_lst( rev_list *rev_lst )
#else
display_rev_lst( rev_lst )
rev_cell *rev_lst;
#endif
{
   fputs(ST_LIST,stderr);

   while ( rev_lst->gnu_name != ( char const * ) NULL )
   {
      fputs(rev_lst->gnu_name,stderr);
      fputs(SP_LIST,stderr);
      fputs(NL,stderr);
      rev_lst++;
   }
}

/*

   Function : print_list()

   Discription : Initialise linked list

   Called by : main()

*/

void
#ifdef __STDC__
print_list( cmd_ptr ptr , FILE * fp )
#else
print_list( ptr , fp )
cmd_ptr ptr;
FILE *fp;
#endif
{
   cmd_ptr tmp;

   tmp = ptr;
   
   do
   {
      if ( ptr->optn != FALSE )
         fputc( OP_CHAR , fp );
      fputs(ptr->token,fp);
      if ( ptr->optn == JOIN )
      {
         ptr = ptr->nxt;
         fputs(ptr->token,fp);
      }
      fputs( NL , fp );
      ptr = ptr->nxt;
   }
   while ( ptr != tmp );
}


#ifdef DEAMON
/*
       Function : deamon()

       Discription : To identify if deamon() is there and open associated
                     files.

       Called by : main()
*/
dm_struct
#ifdef __STDC__
*deamon(char const *temp_env,
        char const *temp_path,
        char const *de_in,
        char const *de_out,
        char const *de_err)
#else
*deamon(temp_env, temp_path, de_in, de_out, de_err,de_tmp)
char const *temp_env;
char const *temp_path;
char const *de_in;
char const *de_out;
char const *de_err;
#endif
{
   static dm_struct dm_st;
   char *tmp_dir, t_buff[256];
   struct stat s_buff;
   int fd;

   if (( tmp_dir = getenv(temp_env)) == ( char * ) NULL )
      return(( dm_struct * ) NULL );

   strcpy( t_buff , tmp_dir );
   strcat( strcat ( t_buff , PT_SEP ) , de_in );
   strcpy( dm_st.out_file , t_buff );

   while ( stat(t_buff,&s_buff) == 0 )  /* Wait for DEAMON to get free */
     sleep(2);

   strcpy( t_buff , tmp_dir );
   strcat( strcat ( t_buff , PT_SEP ) , de_tmp );
   strcpy( dm_st.tmp_file , t_buff );

   if (( fd = creat( t_buff , ( mode_t ) 0777 )) != -1 )
   {
      close(fd);
      if (( dm_st.de_in = fopen( t_buff, "w" )) != ( FILE * ) NULL )
         return( &dm_st );
   }
   return(( dm_struct * ) NULL );

#if 0
   if (( dm_st.de_in = fopen( t_buff , "w" )) == ( FILE * ) NULL )
      return(( dm_struct * ) NULL );

   strcpy( t_buff , tmp_dir );
   strcat( strcat ( t_buff , PT_SEP ) , de_out );

   if (( dm_st.de_out = fopen( t_buff , "r" )) == ( FILE * ) NULL )
      return(( dm_struct * ) NULL );

   strcpy( t_buff , tmp_dir );
   strcat( strcat ( t_buff , PT_SEP ) , de_err );

   if (( dm_st.de_err = fopen( t_buff , "r" )) == ( FILE * ) NULL )
      return(( dm_struct * ) NULL );

   return( &dm_st );
#endif
}

/*
       Function : disp_deamon()

       Discription : To display messages retunred by deamon

       Called by : main()
*/
int
#ifdef __STDC__
disp_deamon(FILE *fderr)
#else
disp_deamon(fderr)
FILE *fderr;
#endif
{
   return 0;
}

/*
       Function : wait_deamon()

       Discription : To wait for deamon to finish job

       Called by : main()
*/
int
#ifdef __STDC__
wait_deamon(char *fdin)
#else
wait_deamon(fdin)
char *fdin;
#endif
{
   FILE *fd;

   while ((fd=fopen(fdin,"r")) != ( FILE *) NULL )
   {
      fclose(fd);
      sleep(1);
   }
   return 0;
}

/*
       Function : writ_deamon()

       Discription : To write to deamon I/P file the new command

       Called by : main()
*/
int
#ifdef __STDC__
writ_deamon(cmd_cell *head_ptr, FILE *fdout)
#else
writ_deamon(head_ptr, fdout)
cmd_cell *head_ptr;
FILE *fdout;
#endif
{
   char buff[64];
   size_t i;

   if ( !no_path && !no_link )
   {
      fputs(LIB_PPATH,fdout);
      fputs( NL , fdout );
      print_list( path_ptr , fdout );
   }

   fprintf(fdout,"%s\n",CWD);
   i = ( size_t ) sizeof( buff );
   if ( getcwd( buff , i ) == CNULL )
      return 0;

   fprintf(fdout,"%s\n",buff);
   print_list( head_ptr , fdout );

   if ( !no_link )
   {
      int i;
      for ( i = 0 ; link_opts[i] != SNULL ; i++ )
      {
         fputc( OP_CHAR , fdout );
         fputs(link_opts[i],fdout);
         fputs( NL , fdout );
      }
      for ( i = 0 ; def_lib[i] != SNULL ; i++ )
      {
         fputs(def_lib[i],fdout);
         fputs( NL , fdout );
      }
      if ( lib_ptr != ( cmd_ptr ) NULL )
         print_list( lib_ptr , fdout );
   }      

   fclose( fdout );
   return 1;
}
#else
/*
       Function : exec_cmd()

       Discription : To exec the new command

       Called by : main()
*/
int
#ifdef __STDC__
exec_cmd(cmd_cell *head_ptr)
#else
exec_cmd(head_ptr)
cmd_cell *head_ptr;
#endif
{
   return 0;
}
#endif

/*
       Function : usage()

       Discription : To identify if if USAGE of command is correct

       Called by : main()
*/
int
#ifdef __STDC__
usage(int argc, char *argv)
#else
usage(argc,argv)
   int argc;
   char *argv;
#endif
{
   gnu_cell *gnu_ptr;
   int new_opt;

   new_opt = TRUE;
   gnu_ptr = gnu_lst;

   if ( argc > 1 )
      return 0;

   fprintf(stderr,"\nUseage : %s ",argv);

   while ( gnu_ptr->opt_name != ( char const * ) NULL )
   {
      if ( new_opt == TRUE )
      {
         fputc(OPT_TAG,stderr);
         new_opt = FALSE;
      }
      fputs(gnu_ptr->opt_name,stderr);
      switch ( gnu_ptr->trail_info )
      {
         case NO   : new_opt = TRUE;
                break;
         case REV  : display_rev_lst( gnu_ptr->rev_lst );
                new_opt = TRUE;
                break;
         case LIBS  :
         case PPATH :
         case OPEN : fputs(gnu_ptr->opn_lst,stderr);
                new_opt = TRUE;
                break;
         default   : fprintf(stderr,"ERROR : Internal error \n");
                break;
      }
      fputc(SP_CHAR,stderr);
      gnu_ptr++;
   }
   fputs(NL,stderr);
   return 1;
}

/*

   Function : init_list()

   Discription : Initialise linked list

   Called by : main()

*/

cmd_ptr
#ifdef __STDC__
init_list( cmd_ptr cell , char * str )
#else
init_list( cell , str )
cmd_ptr cell;
char *str;
#endif
{
   cell->token = str;
   cell->optn = FALSE;
   cell->nxt = cell;
   return( cell );
}

/*

   Function : del_list()

   Discription : Delete list

   Called by : main()

*/

void
#ifdef __STDC__
del_list( cmd_ptr ptr )
#else
del_list( ptr )
cmd_ptr ptr;
#endif
{
   cmd_ptr tmp, tmp2;

   if ( ptr == ptr->nxt )
      return;

   tmp = ptr;
   ptr = ptr->nxt;
   
   do
   {
      tmp2 = ptr->nxt;
      free( ptr );
      ptr = tmp2;
   }
   while ( ptr != tmp );
}


/*

   Function : new_cell()

   Discription : Create new node

   Called by : main()

*/

cmd_ptr
#ifdef __STDC__
new_cell( char *str, boolean optn)
#else
new_cell( str , optn)
char *str;
boolean optn;
#endif
{
   cmd_ptr ptr;

   if (( ptr = (cmd_ptr)malloc(sizeof(cmd_cell))) == (cmd_ptr) NULL )
      return (( cmd_ptr ) NULL );
   ptr->token = str;
   ptr->optn  = optn;
   return ptr;
}

/*

   Function : add_list()

   Discription : Add at current pos

   Called by : main()

*/

cmd_ptr
#ifdef __STDC__
add_list( cmd_ptr ptr , cmd_ptr node )
#else
add_list( ptr , node )
cmd_ptr ptr, node;
#endif
{
   node->nxt = ptr->nxt;
   ptr->nxt = node;
   return node;
}

/*

   Function : equiv_name()

   Discription : Searchs for equivalent name for native
            and returns pointer to base.

   Called by : process_opt()

*/

char
#ifdef __STDC__
*equiv_name( rev_cell *ptr , char *str )
#else
*equiv_name( ptr , str )
rev_cell *ptr; 
char *str;
#endif
{
   while ( ptr->gnu_name != ( char const * ) NULL )
      if ( strcmp(ptr->gnu_name,str) == 0 )
         return ( char * ) ptr->nat_name;
      else
         ptr++;

   return ( char * ) NULL;
}

/*

   Function : process_opt()

   Discription : Check if equivalent option exists

   Called by : main()

*/

int
#ifdef __STDC__
process_opt( char *ch_ptr , gnu_cell *gnu_ptr , int *arg_cnt , char **argv )
#else
process_opt( ch_ptr , gnu_ptr , arg_cnt , argv )
char *ch_ptr;
gnu_cell *gnu_ptr;
int *arg_cnt;
char **argv;
#endif
{
   char *tmp_ptr;
   cmd_ptr cell_ptr;
   boolean b;

   if ( gnu_ptr->trail_info == PPATH )
   {
      if ( *( ch_ptr + 1 ) != CNULL )
         ch_ptr++;
      else
         ch_ptr = argv[++*arg_cnt];

        if ( no_path )
        {
           no_path = 0;
           pend_ptr = path_ptr = init_list( &path_cell , ch_ptr );
        }
        else
        {
            if (( cell_ptr = new_cell(ch_ptr, FALSE )) == ( cmd_ptr ) NULL )
            {
               fprintf(stderr,"ERROR : No mem!\n");
               return 0;
            }
            pend_ptr = add_list( pend_ptr , cell_ptr );
        }
        return 1;
    }

   if ( gnu_ptr->trail_info == LIBS )
   {
      if ( *( ch_ptr + 1 ) != CNULL )
         ch_ptr++;
      else
         ch_ptr = argv[++*arg_cnt];
       if (( tmp_ptr = (char *)malloc(strlen(ch_ptr) + 6)) == SNULL )
       {
          fprintf(stderr,"ERROR : No mem!\n");
          return 0;
       }
       strcat(strcat(strcpy(tmp_ptr,LIBST),ch_ptr),LEXT);
       ch_ptr = tmp_ptr;

       if ( lib_ptr == ( cmd_ptr ) NULL )
       {
          lend_ptr=lib_ptr=init_list( &lib_cell,tmp_ptr );
          return 1;
       }

       if (( cell_ptr = new_cell(ch_ptr, FALSE )) == ( cmd_ptr ) NULL )
       {
          fprintf(stderr,"ERROR : No mem!\n");
          return 0;
       }
       else
       {
          lend_ptr = add_list( lend_ptr , cell_ptr );
          return 1;
       }
   }

   b = gnu_ptr->trail_info == OPEN ? JOIN : TRUE;

   if (( cell_ptr = new_cell(gnu_ptr->nat_ptr->nat_name , b )) == ( cmd_ptr ) NULL )
   {
      fprintf(stderr,"ERROR : No mem!\n");
      return 0;
   }

   end_ptr = add_list( end_ptr , cell_ptr );

   if ( gnu_ptr->trail_info == NO )
      return strlen(ch_ptr) == strlen(gnu_ptr->opt_name);

   if ( *( ch_ptr + 1 ) != CNULL )
      ch_ptr++;
   else
      ch_ptr = argv[++*arg_cnt];

   if ( gnu_ptr->trail_info != OPEN )
      if (( ch_ptr = equiv_name(gnu_ptr->rev_lst,ch_ptr)) != ( char * ) NULL )
         return 0;

   if (( cell_ptr = new_cell(ch_ptr, FALSE )) == ( cmd_ptr ) NULL )
   {
      fprintf(stderr,"ERROR : No mem!\n");
      return 0;
   }
   else
   {
      end_ptr = add_list( end_ptr , cell_ptr );
      return 1;
   }
}

/*

   Function : do_include_path()

   Discription : To add include paths passed by env

   Called by : main()

*/
int
#ifdef __STDC__
do_include_path( char *inc_path )
#else
do_include_path( inc_path )
char *inc_path;
#endif
{
   char *tmp_ptr,*path;
   cmd_ptr cell_ptr;
   boolean exit_flg;

   if (( path = ( char * ) malloc( strlen(inc_path) + 1 )) == SNULL )
   {
      fprintf(stderr,"ERROR : No mem!\n");
      return 0;
   }

   strcpy(path,inc_path);
   tmp_ptr = path;
   exit_flg = !strlen(path);

   while ( !exit_flg )
   {
      while ( *tmp_ptr != VAR_SEP && *tmp_ptr != '\0' )
          tmp_ptr++;
  
      exit_flg = *tmp_ptr == '\0';

      *tmp_ptr = '\0';

      if ( tmp_ptr > path )
      {

         if (( cell_ptr = new_cell("I", JOIN )) == ( cmd_ptr ) NULL )
         {
            fprintf(stderr,"ERROR : No mem!\n");
            return 0;
         }
      
         end_ptr = add_list( end_ptr , cell_ptr );
         
         if (( cell_ptr = new_cell(path, FALSE )) == ( cmd_ptr ) NULL )
         {
            fprintf(stderr,"ERROR : No mem!\n");
            return 0;
         }
      
         end_ptr = add_list( end_ptr , cell_ptr );
      }
	   
      tmp_ptr++;
      path = tmp_ptr;

   }
   return 1;
}


/*

   Function : in_opt_list()

   Discription : Identify option and return ptr to table entry

   Called by : main()

*/

gnu_cell 
#ifdef __STDC__
*in_opt_list( char *ch_ptr )
#else
*in_opt_list( ch_ptr )
char *ch_ptr;
#endif
{
   gnu_cell *gnu_ptr;
   char *tmp_ptr;

   gnu_ptr = gnu_lst;

   while (( tmp_ptr = ( char * )gnu_ptr->opt_name ) != SNULL )
   {
      if ( strncmp(ch_ptr,tmp_ptr,strlen(tmp_ptr)) == 0 )
      {
         if ( chk_lnk && strcmp(tmp_ptr,NO_LINK) == 0 )
         {
            chk_lnk = 0;
            no_link = 1;
         }
         return gnu_ptr->nat_ptr == NNULL ? GNULL : gnu_ptr ;
      }
      else
         gnu_ptr++;
   }
   return GNULL;
}

int
#ifdef __STDC__
main(int argc, char **argv)
#else
main(argc,argv)
   int argc;
   char ** argv;
#endif
{
#ifdef DEAMON
   dm_struct *dm_ptr;
#endif
   char *arg_ptr, *ch_ptr;
   cmd_ptr tmp_ptr;
   gnu_cell *gnu_ptr;
   int i;

   if ( usage(argc,argv[0]))
      return 0;

#if DEAMON
   if((dm_ptr=deamon(TMP_ENV,TMP_DIR,D_IN,D_OUT,D_ERR,D_TMP))==(dm_struct*)NULL)
   {
      fprintf(stderr,"Cannot execute %s deamon missing\n",*argv[0]);
      return 0;
   }
#endif

   end_ptr = head_ptr = init_list( &head_cell , HOST_CC );

   if (( arg_ptr = getenv(INC_PATH)) != SNULL )
      do_include_path(arg_ptr);

   lib_ptr = ( cmd_ptr ) NULL;
   i = 0;

   while ( ++i < argc )
   {
      arg_ptr = *( argv + i );

      if ( !option(*arg_ptr))
      {
         if (( tmp_ptr = new_cell(arg_ptr,FALSE)) == ( cmd_ptr ) NULL )
         {
            fprintf(stderr,"Insufficient memory EXITING!\n");
            return 0;
         }
         end_ptr = add_list( end_ptr , tmp_ptr );
      }   
      else
      {
         ch_ptr = arg_ptr;
         ch_ptr++;

         while ( *ch_ptr != ( char )NULL )
         {
            if (( gnu_ptr = in_opt_list(ch_ptr)) != ( gnu_cell * ) NULL )
               if ( process_opt(ch_ptr,gnu_ptr,&i,argv))
                  break;
            ch_ptr++;
         }
      }
   }

#if DEAMON
   if ( !writ_deamon( head_ptr , dm_ptr->de_in ))
   {
      fprintf(stderr,"Unable to communicate with DEAMON. EXITING!\n");
      return 0;
   }
   rename( dm_ptr->tmp_file, dm_ptr->out_file );
   wait_deamon( dm_ptr->out_file );
   disp_deamon( dm_ptr->de_err );
#else
   exec_cmd( head_ptr );
#endif
   del_list( head_ptr );
   return 0;
}
