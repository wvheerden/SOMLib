/*  File:     att_order.c
    Author:   Robin Boswell
    Purpose:  Deal with attribute ordering
*/ 

static char *SccsId = "@(#)att_order.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"

static int **array;
static int *buffer;
static int array_index;

BOOL initialise_order_array()
{
     int row;
     
     array = (int **)ALLOC(number_of_attributes * sizeof(int *));
     for (row = 0; row < number_of_attributes; ++row)
       array[row] = (int *)ALLOC(2 * sizeof(int));
     array_index = 0;
     buffer = (int *)ALLOC(number_of_attributes * sizeof(int));     
     return(TRUE);
}

BOOL transform_order_array()
{
     int attno, p_attno, j, k, buffer_index;
     int *p;
     BOOL dup;

     for (attno = 0; attno  < number_of_attributes; ++attno){

	  buffer_index = 0;

	  for (j = 0; j < array_index; ++j){
	       dup = FALSE;
	       if (array[j][1] == attno){
		    p_attno = array[j][0];
		    for (k = 0; k < buffer_index; ++k)
		      if (buffer[k] == p_attno){
			   dup = TRUE;
			   break;
		      }
		    if (!dup)
		      buffer[buffer_index++] = p_attno;
	       }
	  }
	  
	  if (buffer_index > 0){
	       Attribute *att = nth_attribute(attno);
	       
	       buffer[buffer_index++] = (-1);
	       p = (int *)ALLOC(buffer_index * sizeof(int));
	       buffer_cpy(p, buffer);
	       att->prerequs = p;
	  }
     }
     
     FREE(array);
     FREE(buffer);
     
     return(TRUE);
}

BOOL insert_order_array(string1, string2)
char *string1, *string2;
{
     Attribute *att;

     if (att = string_to_attribute(string1)){
	  array[array_index][0] = ATT_NO(att); 
     }
     else
       att_string_error(string1);

     if (att = string_to_attribute(string2)){
	  array[array_index][1] = ATT_NO(att); 
     }
     else
       att_string_error(string2);
     
     ++array_index;
     return(TRUE);     
}

att_string_error(string)
char  *string;
{
     fprintf(stdout, "ERROR:  No such attribute  -  %s\n",  string);
     fprintf(stdout, "Line number  %ld\n", ln);
     errflag = TRUE;
}



buffer_cpy(b1, b2)
int *b1, *b2;
{
     while (*b2 != (-1))
       *b1++ = *b2++;
     *b1 = (-1);
}


BOOL p_member(n, array)
int n;
int *array;
{
     while (*array != -1)
       if (*array++ == n)
	 return(TRUE);
     return(FALSE);
}

int p_length(array)
int *array;
{
     int n = 0;
     
     while (*array++ != -1)
       ++n;
     return(n);
}






