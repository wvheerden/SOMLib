/*  File:     example.c
    Author:   Robin Boswell
    Purpose:  Operate on examples and example-lists
    */ 

static char *SccsId = "@(#)example.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"


extern struct EListElement *new_elist();


EList new_elistelement()
{
/*     EList elist = (EList) ALLOC(sizeof(struct EListElement)); */
     EList elist = (EList) new_elist();
     E_WEIGHT(elist) = 1;
     E_VALUES(elist) = (Value *) ALLOC(number_of_attributes * sizeof(Value));
     return(elist);
}

/* Create an elistelement but DON'T allocate space for the att-vals.
   This function should be used when copying an input-example
   (so the weight and successor may change, but the vals won't) */
EList new_ecopy()
{
/*     EList elist = (EList) ALLOC(sizeof(struct EListElement)); */
     EList elist = (EList) new_elist();     
     E_WEIGHT(elist) = 1;
     return(elist);
}


/* This is a partner for new_ecopy() -  i.e. new_ecopy()
   followed by free_elist() leaves you where you started. */
void free_elist(elist)
register EList elist;
{
     register EList p;
     while (p = elist){
	  elist = E_NEXT(elist);
	  free_thing(p);
     }
}

void really_free_elist(elist)
EList elist;
{
     if (elist) {
	  FREE(elist->values);
	  really_free_elist(E_NEXT(elist));
	  free_thing(elist);
     }
}


/* True if all the examples are in the same class */
BOOLEAN terminal(elist)
EList elist;
{
     Value value;

     if (elist)
       switch (ATT_TYPE(IDclass)){
       case DISCRETE_TYPE:
	    value.d = E_DVAL(IDclass, elist);
	    break;
       case ORDERED_TYPE:
	    value.o = E_OVAL(IDclass, elist);
	    break;
       }
     else
       return(TRUE);

     while (elist){
       switch (ATT_TYPE(IDclass)){
       case DISCRETE_TYPE:
	    if (E_DVAL(IDclass, elist) != value.d)
	      return(FALSE);	      
	    break;
       case ORDERED_TYPE:
	    if (E_OVAL(IDclass, elist) != value.o)
	      return(FALSE);	      	      
	    break;
       }
       elist = elist -> next;
     }
     return(TRUE);
}
