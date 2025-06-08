/*  File:     list.c
    Author:   Robin Boswell
    Purpose:  Lists
*/ 

static char *SccsId = "@(#)list.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";


#include "mdep.h"
#include "cn_externs.h"

List new_listelement()
{
     List list = (List) ALLOC(sizeof(ListCell));
     list -> tail = (List)0;
     list -> head = (Object *)0;     
     return(list);
}

Object *new_object()
{
     return((Object *) ALLOC(sizeof(Object)));
}

List last(list)
List list;
{
     List temp;
     while (list){
	  temp = list;
	  list = list -> tail;
     }
     return(temp);
}


void free_list(list)
List list;
{
     if (list) {
	  free_object(HEAD(list));
	  free_list(TAIL(list));
	  FREE(list);
     }
}

void free_object(object)
Object *object;
{
     if (object){
	  switch (object->otype) {
	  case 'A':                    
	       free_attribute((Attribute *) object->value);
	       break;
	  default:
	       break;
	  }
	  FREE(object);
     }
}


