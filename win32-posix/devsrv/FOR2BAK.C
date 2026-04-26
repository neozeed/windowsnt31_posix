#include <stdio.h>
/*
 * For2bak:  Converts a string's fore slashes to back slashes.  MSS
 */

void for2bak(char * str) 
{
	char *ptr;

	while (*str) {
		if (ptr = strchr(str, ":"))
			str = ptr+1;
		if(*str == '/')
			*str = '\\';
		str++;
	}			
}
