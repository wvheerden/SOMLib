/*  File:     robin.c
    Author:   Tim Niblett
    Purpose:  Efficent memory allocation fo rexamples
*/ 

static char *SccsId = "%Z%%M% %I% %G% MLT"; 

/* Memory allocation for ListCells */

#include <stdio.h>
#include "cn_header.h"

#define LIST_SIZE 10000

typedef struct EListElement THING;

typedef struct HOLDER {
	THING el;
	struct HOLDER *next;
} HOLDER;

HOLDER *freelist = 0;
int count = 0;

HOLDER first[LIST_SIZE];

HOLDER *thelist = first;


THING *new_elist()
{
	register HOLDER *tmp = freelist;
	register int i;

	if (tmp) {
		freelist = freelist->next;
		return(&(tmp->el));
	}

	if (count < LIST_SIZE) {
		return(&(thelist[count++].el));
	}

	thelist = (HOLDER *)ALLOC(sizeof(HOLDER)*LIST_SIZE);
	count = 0;
	for (i = 0, tmp = thelist; i < LIST_SIZE; i++, tmp++) {
		tmp->next = 0;
	} 
	return(&(thelist[count++].el));
}

/* This assumes that the address of a HOLDER is equal
 * to the address of the THING, which is its first element
 * There is some more formal way to do this in ANSII C and
 * C++
 */
void free_thing(elist)
void *elist;
{
	register HOLDER *tmp = (HOLDER *)elist;

	tmp->next = freelist;
	freelist = tmp;
}
