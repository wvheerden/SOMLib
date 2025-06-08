/*  File:     filter.c
    Author:   Robin Boswell
    Purpose:  Filter out examples covered.
*/ 

static char *SccsId = "@(#)filter.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"


/* Remove all examples that are covered by the best selector    */
/* In UNORDERED mode, do NOT remove examples that are covered   */
/* but are not in the right class (currrent_class)              */

filter(classified_examples)
Quotquae *classified_examples;
{
     int i;
     EList elist, el_covered, *eptr;
     double weight_covered;
     int covering;

     EList *ptr = (EList *) ALLOC (number_of_classes *
				   sizeof(EList));
     for (i=0; i< number_of_classes; ++i)
       ptr[i] = global_best_node->quotquae[i].quae;
		     
     for (i=0; i < number_of_classes; ++i){
	  elist = classified_examples[i].quae;
	  eptr = &classified_examples[i].quae;
	  classified_examples[i].quot = 0.0;

          while (elist) {
	       if (ORDERED || i == current_class)
		 covering = covered(elist, global_best_node->selector,
				    &weight_covered);
	       else {
		    covering = NO_COVERING;
	       }
	       
	       switch (covering){
	       case UNKNOWN_COVERING:
		    /* look_up_example(elist, i, ptr, &weight_covered); */
		    /* Carry on down... */
	       case PARTIAL_COVERING:
		    E_WEIGHT(elist) = E_WEIGHT(elist) - weight_covered;
		    /* Carry on down... */
	       case NO_COVERING:
		    (*eptr) = elist;
		    eptr = &(elist->next);
		    classified_examples[i].quot +=
		      E_WEIGHT(elist);
		    elist = elist->next;	 		    
		    break;
	       case TOTAL_COVERING:
		    el_covered = elist;
		    elist = elist->next;
		    free_thing(el_covered); 
		      /* Free the element that was covered */
		    break;
	       }
	  }
	  (*eptr) = (EList)0;	
     }
}


/*
  If any attribute test definitely failed then
  return NO_COVERING (it doesn't matter if other atts have unknowns).
  Else, if any unknowns present, return UNKNOWN_COVERING.
     (In this case, must look up example in best_node's quotquae).  
  Else, if any DC's present, return PARTIAL_COVERING, and put the
  weight covered into *weight_covered.
  Else, return TOTAL_COVERING (And example will be filtered out). */

int covered(elist, selector, weight_covered)
EList elist;
Selector *selector;
double *weight_covered;
{
     int att_no;
     Attribute *attribute;
     double weight = E_WEIGHT(elist);
     BOOL unknown = FALSE;
     BOOL partial = FALSE;
     int dval;
     Ordered oval;
     unsigned short instant;
     
     
     for (att_no=0; att_no < number_of_attributes; ++att_no){
	  attribute = nth_attribute(att_no);
	  if (attribute == IDclass)
	    continue;
	  if (! selector[att_no].setp)
	    continue;
	  switch ATT_TYPE(attribute){
	  case DISCRETE_TYPE:
	       dval = E_DDVAL(att_no, elist);
	       if (D_DC(dval)) {
		    partial = TRUE;
		/*    weight = weight / N_VALUES(attribute); */
	       }
	       else if (D_UNK(dval)) {
		    unknown = TRUE;
		    weight = weight / N_VALUES(attribute);
	       }
	       else if (dval !=selector[att_no].discriminant->attval)
		 return(NO_COVERING);
	       break;
	  case ORDERED_TYPE:
	       oval = E_OOVAL(att_no, elist);
	       instant = selector[att_no].discriminant->bounds->instantiation;
	       if (O_DC(oval)){
		    partial = TRUE;
		    /* Don't reduce weight */
	       }
	       else if (O_UNK(oval)) {
		    unknown = TRUE;
		    if (LOWER_BOUND_SET_P(instant)
			&&
			UPPER_BOUND_SET_P(instant))
		      weight = weight / 4;
		    else
		      weight = weight / 2; /* We know at least one is set */
	       }
	       else {
		    if (LOWER_BOUND_SET_P(instant) &&
			oval <= selector[att_no].discriminant->bounds->lower)
		      return(NO_COVERING);
		     if (UPPER_BOUND_SET_P(instant) &&
			 oval >= selector[att_no].discriminant->bounds->upper)
		       return(NO_COVERING);
	       }
	       break;
	  }
     }
     *weight_covered = weight;     

     if (unknown)
       return(UNKNOWN_COVERING);
     else if (partial)
       return(PARTIAL_COVERING);
     else return(TOTAL_COVERING);
}

     

look_up_example(elist, i, ptr, weight_covered)
EList elist;
int i;
EList *ptr;
double *weight_covered;
{
     EList covered_list = ptr[i];
     while (covered_list){
	  if (equal_values(elist, covered_list)){
	       *weight_covered = covered_list->weight;
	       ptr[i] = covered_list->next;
	       return;
	    }
	  covered_list = covered_list->next;
     }
     /*
     fprintf(stderr, "look_up_example: covered_example not found\n");
                                                                 */
     *weight_covered = 0.0;
     return;
}


BOOL equal_values(elist1, elist2)
EList elist1, elist2;
{
     int i;
     for (i=0; i < number_of_attributes; ++i) {
	  switch (ATT_TYPE(nth_attribute(i))){
	  case DISCRETE_TYPE:
	       if (E_DDVAL(i, elist1) != E_DDVAL(i, elist2))
		 return(FALSE);
	       break;
	  case ORDERED_TYPE:
	       if (E_OOVAL(i, elist1) != E_OOVAL(i, elist2))
		 return(FALSE);	       
	       break;
	  }
     }
     return(TRUE);
}

     
