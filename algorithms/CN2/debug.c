/*  File:     debug.c
    Author:   Robin Boswell
    Purpose:  debug
*/ 

static char *SccsId = "@(#)debug.c 5.1 9/25/91 MLT"; 

#include <stdio.h>
#include "mdep.h"

#include "cn_externs.h"

/* extern char *malloc(); */

void *raballoc(size)
unsigned size;
{
     char *ptr;
     if (ptr = (char *) malloc(size))
       return(ptr);
     else {
	  fprintf(stdout, "Out of memory!!\n");
	  exit(-1);
       }
}


