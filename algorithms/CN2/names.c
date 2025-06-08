/*  File:     names.c
    Author:   Tim Niblett
    Purpose:  Handle attributes
                                  */ 

static char *SccsId = "@(#)names.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"

#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "cn_externs.h"


/* -------------------------------- */

/* Hashsize should be a power of 2 */
#define HASHSIZE	128

/* -------------------------------- */

/* Exported Globals */

/* -------------------------------- */


/* -------------------------------- */

static Atom *hashtable[HASHSIZE];

/* -------------------------------- */

USHORT hash(string)
register char *string;
{
	register USHORT h = 0;

	while (*string)
		h += *string++;
	return(h & (HASHSIZE-1));
}


Atom *intern(string)
register char *string;
{
	register USHORT h;
	register Atom *p;

	h = hash(string);
	p =  hashtable[h];
	while (p != NULL)
		if (strcmp(string, p -> name) == 0)
			return(p);
		else
			p = p -> link;

	p = (Atom *) ALLOC((unsigned long)sizeof(Atom));
	
	p -> name = (char *) ALLOC((unsigned long)(strlen(string) + 1)); 
	strcpy(p -> name, string); 
	p -> link = hashtable[h];
	hashtable[h] = p;
	return(p);
}

/* Like intern, but is intended for use on already-hashed strings */
/* so won't create a new atom if the string isn't found           */
Atom *string_to_atom(string)
register char *string;
{
	register USHORT h;
	register Atom *p;

	h = hash(string);
	p =  hashtable[h];
	while (p != NULL)
		if (strcmp(string, p -> name) == 0)
			return(p);
		else
			p = p -> link;

        return((Atom *)0);
}


void hash_init()
{
	register USHORT i;

	for(i = 0; i < HASHSIZE ; i++)
		hashtable[i] = NULL;
}

/* ---------------------------------------- */


/* Determine the index of an attribute value:
   Write the answer into the integer pointed to by value */
BOOL value_id(a, attr, value)
Atom *a;
SHORT attr;
int *value;
{
	List p;
	register int i, n;
        List Att_Ptr = attribute_list;
	Attribute *temp_attribute;

        /* temp_attribute has been introduced in order to get
	   saber to accept the code.  The original version,
	   which cc grudgingly accepts, but saber doesn't, made use of

                Att_Ptr -> head -> value -> index

                      		                                     */
	
	while (Att_Ptr){    /* Find attribute */
	     temp_attribute = (Attribute *) Att_Ptr -> head -> value;
	     if ((temp_attribute -> index) == attr)
	       break;
             Att_Ptr = Att_Ptr -> tail;
	}
        if (! Att_Ptr){
	     fprintf(stderr, "ERROR: No att number %d\n", (int) attr);
	     exit(1);
	}
        n = temp_attribute -> n_values;
        p = temp_attribute -> avalues;

	                    /* Find value */

	for (i = 0; i < n; i++, p = p -> tail)
	  if ( (p -> head -> value) == a){
	       *value = i;
	       return(TRUE);
	  }
	
	if (strcmp(a->name, UK_STRING) == 0){
	     *value = UK_INT;
	     return(UK_INT);
	}
	else {
	     fprintf(stderr, "ERROR: %s is a bad attribute value for att. %s\n", 
		     a -> name, (temp_attribute -> aname) -> name);
	     return(FALSE);
	}
	
}



/* Return an attribute given its name */
Attribute *string_to_attribute(string)
char *string;
{
     Atom *p;
     List Att_Ptr = attribute_list;     
     
     if (p = string_to_atom(string)){
	  while (Att_Ptr){   
	       if (((Attribute *) Att_Ptr -> head -> value) -> aname == p)
		 return((Attribute *) Att_Ptr -> head -> value);
	       Att_Ptr = Att_Ptr -> tail;
	  }
     }
     fprintf(stderr, "WARNING: Unable to find attribute called `%s'\n",
	     string);
     return((Attribute *) 0);
     
}     
