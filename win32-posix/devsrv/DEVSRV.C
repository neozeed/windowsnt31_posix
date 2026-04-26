#if 0
#include "d:\nt\public\sdk\inc\crt\sys\types.h"
#include "d:\nt\public\sdk\inc\crt\sys\stat.h"
#include "d:\ntnew\mstools\h\sys\types.h"
#include "d:\ntnew\mstools\h\sys\stat.h"
#endif
#include <sys\types.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <errno.h>
#if 0
#include <unistd.h>
#endif
#include <stdio.h>
#include <process.h>
#include <direct.h>
#include <stdlib.h>


char
        *csp_ptr,
	args[100][81],
	*argp[100],
	command[81],
	*cPtr,
	dir[81],
	directory[81],
	exe[81],
	lib[256],
	fn[50][81],
	new[81],
	old[81],
	oldLibEnv[256],
	curLibEnv[256],
	tmp[81];
int
	i,
	j,
	len,
	x,
	y,
	z;

main()
{
	if(cPtr = getenv("TMP"))	
		strcpy(directory, cPtr);

	strcat(directory, "\\devsem.ini");
	remove(directory);
	for (;;)
		check_status ();
}

char *mystrstr(char *str,char *pat)
{
    struct stat buff;
#if 0
    if ( _stat( str , & buff ) == -1 )
       return ( char * ) NULL;
    if ( buff.st_mode & _S_IFDIR )
       return ( char * ) NULL;
#endif
    if ( strcmp( str + strlen(str) - strlen(pat) ,  pat ))
       return ( char * ) NULL;
    return str + strlen(str) - strlen(pat);
}

check_status()
{
FILE 	
	*in, 
	*out;

	while(!(in = fopen(directory, "r")))
		_sleep(5);
	
	curLibEnv[0] = 0;
	fscanf(in, "%s", exe);
	if(!strcmp(exe, "LIB"))
		{
		fscanf(in, "%s", lib);
		fscanf(in, "%s", exe);

		if(!strncmp(lib, "//", 2)) //Change drive letter format
			{
			strcpy(tmp, &(lib[3]));
			lib[0] = lib[2];
			lib[1] = ':';
			lib[2] = 0;
			strcat(lib, tmp);
			for2bak(lib);
			}

		if(cPtr = getenv("LIB"))	
			strcpy(oldLibEnv, cPtr);

		strcpy(curLibEnv, "LIB=");
		strcat(curLibEnv, lib); 
		putenv(curLibEnv);
		}
	else
		{
		if(cPtr = getenv("POSIX_LIB"))	
			strcpy(lib, cPtr);

		if(cPtr = getenv("LIB"))	
			strcpy(oldLibEnv, cPtr);

		strcpy(curLibEnv, "LIB=");
		strcat(curLibEnv, lib); 
		putenv(curLibEnv);
		}

	if(!strcmp(exe, "cwd"))
		{
		fscanf(in, "%s", tmp);
		if(!strncmp(tmp, "//", 2)) //Change drive letter format
			{
			dir[0] = tmp[2];
			dir[1] = ':';
			dir[2] = 0;
			strcat(dir, &(tmp[3]));
			}
		else
			strcpy(dir, tmp);

		for2bak(dir);

		i = _chdir(dir);
		i = errno;
		}

	x=0;
	y=0;
	for (i=0; i < 100 && fscanf(in, "%s", args[i]) && !feof(in); i++)
		{

		if(!strncmp(args[i], "//", 2)) //Change drive letter format
			{
			strcpy(args[i+1], &(args[i][3]));
			args[i][0] = args[i][2];
			args[i][1] = ':';
			args[i][2] = 0;
			strcat(args[i], args[i+1]);
			for2bak(args[i]);
			}

		if(strstr(args[i], "//", 2))
			{
			if(!strncmp(args[i], "/I", 2)) //Change drv letter fmt
				{
				strcpy(args[i+1], &(args[i][5]));
				args[i][0] = '/';
				args[i][1] = 'I';
				args[i][2] = args[i][4];
				args[i][3] = ':';
				args[i][4] = 0;
				strcat(args[i], args[i+1]);
				for2bak(&(args[i][1]));
				}
			}

		if(mystrstr(args[i], ".lib")) //Adjust .lib paths
			for2bak(args[i]);

		if(strstr(args[i], "/Fe")) //Record .exe file
			{
			j = 0;
			for(z=3; args[i][z] != 0; z++)
				{
				if(args[i][z] == '/')
					args[i][z] = '\\';

				exe[j++] = args[i][z];
				}
			exe[j] = 0;
			}

		if(csp_ptr = mystrstr(args[i], ".c")) //Record all .c files
			{
                        int t;

#if 0
                        printf("Found a .c -> %s\n",args[i]);
                        printf("RET of mystrstr -> %s\n",csp_ptr);
#endif
                        t = 0;

			/* for2bak(args[i]); */
                        while (*( csp_ptr - 1 ) != '/' && csp_ptr > args[i]) 
			   {
                           t++;
                           csp_ptr--;
			   }

                        strncpy(fn[x] , csp_ptr , t );
                        fn[x++][ t ] = 0;
			for2bak(args[i]);
#if 0
                        printf("Without a .c -> %s\n",fn[x-1]);
#endif
			}

		if(csp_ptr = mystrstr(args[i], ".a")) //Record all .a files
			{
                        int t;

                        t = 0;
			/*for2bak(args[i]);*/

                        while (*( csp_ptr - 1 ) != '/' && csp_ptr > args[i]) 
			   {
                           t++;
                           csp_ptr--;
			   }

                        strncpy(fn[y] , csp_ptr , t );
                        fn[y++][ t ] = 0;
			if(csp_ptr = strstr(args[i], ":"))
				for2bak(csp_ptr+1);
			else
				for2bak(args[i]);
			}

		argp[i] = args[i];

		}
	argp[i] = (char *)NULL;

	strcpy(command, args[0]);
	i = _spawnvp(_P_WAIT, command, argp);
	i = errno;

	strcpy(new, exe); //Rename output.exe to output
	strcpy(old, exe);
	strcat(old, ".exe");
	remove(new);
	rename(old, new);

if(!strcmp(args[0], "lib32"))
	{
	strcpy(new, fn[0]); //Rename a.exe to a
	strcpy(old, fn[0]);
	strcat(old, ".exe");
	remove(new);
	rename(old, new);
#if 0
	for(i=0; i < x; i++) //Rename .obj to .o
		{
		strcpy(new, fn[i]);
		strcpy(old, fn[i]);
		strcat(new, ".o");
		strcat(old, ".obj");
		remove(new);
		rename(old, new);
		}
#endif
	for(i=0; i < y; i++) //Rename .lib to .a
		{
		strcpy(new, fn[i]);
		strcpy(old, fn[i]);
		strcat(new, ".a");
		strcat(old, ".lib");
		remove(new);
		rename(old, new);
		}
	}
else
	for(i=0; i < x; i++) //Rename .obj to .o
		{
		strcpy(new, fn[i]);
		strcpy(old, fn[i]);
		strcat(new, ".o");
		strcat(old, ".obj");
#if 0
                printf("%s->%s\n",old,new);
#endif
		remove(new);
		rename(old, new);
		}

	fclose(in);
	remove(directory);

	strcpy(curLibEnv, "LIB=");
	strcat(curLibEnv, oldLibEnv); 
	putenv(curLibEnv);
}
