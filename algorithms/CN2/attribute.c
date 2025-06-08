/*  File:     attribute.c
    Author:   Robin Boswell
    Purpose:  Lists
*/ 

static char *SccsId = "@(#)attribute.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include <stdio.h>
#include "mdep.h"
#include "cn_externs.h"

#define NTH_ATTRIBUTE_ERROR "ERROR: Attempting to select attribute %d\n"

Attribute **attribute_array;

Attribute *new_attribute(attr, type, ntype, n_values, values, att_num)
Atom *attr;
Type type;
numeric_type ntype;
SHORT n_values;
List values;
int att_num;
{
	register Attribute *p;

	p = (Attribute *)ALLOC((unsigned long)(sizeof(Attribute)));
	
	p -> index = att_num;
	p -> aname = attr;
	p->  prerequs = (int *)0;	
	p -> atype = type;
	p -> ntype = ntype;	
	p -> n_values = n_values;
	p -> avalues = values;
	
	return(p);
}


void free_attribute(attribute)
Attribute *attribute;
{
     free_list(attribute -> avalues);
     FREE(attribute);
}


/* Return the nth attribute */
/*
Attribute *nth_attribute(i)
int i;
{

     return(attribute_array[i]);
}                                   */

char *nth_attribute_name(i)
int i;
{
     return(nth_attribute(i) -> aname -> name);
}




/* Return the string associated with the ith value of the
   nth attribute (assumes it's discrete)                 */
char *att_val_string(att_num, val_num)
int att_num;
int val_num;
{
     if (D_DC(val_num))
       return("DONT_CARE");
     else if (D_UNK(val_num))
       return("UNKNOWN");
     else {
	  List avals = nth_attribute(att_num) -> avalues;
	  int i = 0;
	  while (avals){
	       if (i++ == val_num)
		 return(((Atom *) avals -> head -> value) -> name);
	       avals = avals -> tail;
	  }
	  return((char *)0);
     }
}


     
/* Return the string associated with the ith value in a list
   (assumes it's discrete)                 */
char *val_string(avals, val_num)
List avals;
int val_num;
{
     int i = 0;
     while (avals){
	  if (i++ == val_num)
	    return(((Atom *) avals -> head -> value) -> name);
	  avals = avals -> tail;
     }
     return((char *)0);
}

     

List
remove_attribute(att, a_list)
Attribute *att;
List a_list;
{
     List new_list;
     List *new_ptr;
     if (ATT_TYPE(att) == ORDERED_TYPE)
       return(a_list);
     else if (BIN_ACT(att) == TWOWAY)
       return(a_list);       
     else {
	  new_list = new_listelement();
	  new_ptr = &new_list;
	  while (a_list){
	       if (att != (Attribute *) a_list->head->value){
		    (*new_ptr) -> head = new_object();		    
		    (*new_ptr) -> head -> value =
		      (Attribute *) a_list->head->value;
		    (*new_ptr) -> tail = new_listelement();
		    new_ptr = &((*new_ptr) -> tail);
	       }
	       a_list = a_list -> tail;
	  }
	  (*new_ptr) = (List)0;
     }
     return(new_list);  
}





BOOL over_used(attribute, history)
Attribute *attribute;
List history;
{
     if (ATT_TYPE(attribute) == ORDERED_TYPE
	 || BIN_ACT(attribute) == TWOWAY)
       return(0);
     
     while  (history) {
	  if (((Splodge *) history -> head -> value) -> att_index ==
	      attribute -> index)
	    return(1);
	  else
	    history = history -> tail;
	 }
     return(0);
}


BOOL remaining_values(attribute, history, lptr)
Attribute *attribute;
List history;
List *lptr;
{
     while  (history) {
	  if (((Splodge *) history -> head -> value) -> att_index ==
	      attribute -> index){
	       *lptr = (((Splodge *) history -> head -> value) -> uses).list;
	       return(1);
	  }
	  else
	    history = history -> tail;
     }
     (*lptr) = (List)0;
     return(0);
}
	  
void setup_attribute_array()
{
     List aptr = attribute_list;
     
     int index = 0;
     
     attribute_array = (Attribute **)ALLOC(number_of_attributes *
					   sizeof(Attribute *));

     while (aptr){
	  attribute_array[index++] = (Attribute *)aptr->head->value;
	  aptr = TAIL(aptr);
     }
     
}

/* Can we specialise attno:
     i) Is it already used up?
     ii) Have its prerequisites been tested?
                                                 */
BOOL acceptable(attno, node)
int attno;
Node *node;
{
     int *p;
     
     if (TOTALLY_INSTANTIATED(node->selector[attno].setp))
       return(FALSE);
     
     if (! (p = PREREQUS(nth_attribute(attno))))
       return(TRUE);

     while (*p != (-1)){
	  if (! INSTANTIATED(node->selector[*p++].setp))
	    return(FALSE);
     }

     return(TRUE);
}

