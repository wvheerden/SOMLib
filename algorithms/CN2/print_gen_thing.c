/*  File:     print_thing.c
    Author:   Robin Boswell
    Purpose:  Print things
    */

static char *SccsId = "@(#)print_gen_thing.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"

#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#ifdef MAC
#include <storage.h>
#endif

#include "cn_externs.h"
#define TAB 5

/* -------------------------------- */

void tab(stream, n)
FILE *stream;
SHORT n;
{
     register SHORT i = n;
     
     for ( ; i ; --i )
       fprintf(stream, "    ");
}

/* -------------------------------- */
/* Tree-printing routines deleted   */
/* -------------------------------- */




void print_elist(stream, elist)
FILE *stream;
EList elist;
{
     while (elist){
	  print_el(stream, *elist);
	  elist = elist -> next;
     }
}

	  
void print_el(stream, el)
FILE *stream;
struct EListElement el;
{
     Value *values =  el.values;
     fprintf(stream, "Weight = %.2f\n", el.weight);
     print_values(stream, values);
     fprintf(stream, "\n\n");
}

void print_values(stream, values)
FILE *stream;
Value *values;
{
     int i;
     for (i=0; i < number_of_attributes; ++i){
	  print_value(stream, i, values[i]);
     }
}

void print_value(stream, i, value)
FILE *stream;
int i;
Value value;
{
     Type type = ATT_TYPE(nth_attribute(i));
     switch (type) {
     case ORDERED_TYPE:
	  if (O_DC(value.o))
	    fprintf(stream, "%d) DON'T CARE ",i);
	  else if (O_UNK(value.o))
	    fprintf(stream, "%d) UNKNOWN ",i);
	  else
	    fprintf(stream, "%d) %.2f ",i, value.o);
	  break;
     case DISCRETE_TYPE:
	  fprintf(stream, "%d) `%s' ", i, att_val_string(i, value.d));  
     }
}

/* ============================================================ */

void print_attribute_list(stream, att_list)
FILE *stream;
List att_list;
{
     while (att_list){
	  print_attribute(stream, (Attribute *) att_list -> head -> value);
	  att_list = att_list -> tail;
     }
}



void print_attribute(stream, att)
FILE *stream;
Attribute *att;
{
     fprintf(stream, "Attribute:    %s\n", att -> aname -> name);
     fprintf(stream, "Number:       %d\n", ATT_NO(att)); 
     fprintf(stream, "Type:         %c\n", (char ) ATT_TYPE(att));
     fprintf(stream, "No of values: %d\n", N_VALUES(att));
     if (ATT_TYPE(att) == DISCRETE_TYPE){
	  fprintf(stream, "Values: \n");
	  print_attribute_values(stream, att);
	  fprintf(stream, "\n");	  
	  print_attribute_bin_action(stream, att);
       }
     fprintf(stream, "\n\n");
}

void print_attribute_values(stream, att)
FILE *stream;
Attribute *att;
{
     List val_list = att -> avalues;
     while (val_list){
	  fprintf(stream, " %s ",
		    ((Atom *) (val_list -> head -> value)) -> name);
	  val_list = val_list -> tail;
     }
}

void print_attribute_bin_action(stream, att)
FILE *stream;
Attribute *att;
{
     fprintf(stream, "Split type: ");
     switch (att -> bin_action){
     case TWOWAY:
	  fprintf(stream, " Binary\n");
	  break;
     case MULTIPLE:
	  fprintf(stream, " Multiple\n");
	  break;
     case DEFAULT:
	  fprintf(stream, " Default (ERROR!)\n");
     }
}

	  





     
void print_input_type(stream, input_type)
FILE *stream;
InputType input_type;
{
     switch (input_type){
     case ATTRIBUTES_AND_EXAMPLES:
	  fprintf(stream, "Attributes and Examples\n");
	  break;
     case ATTRIBUTES:
	  fprintf(stream, "Attributes\n");
	  break;	  
     case EXAMPLES:
	  fprintf(stream, "Examples\n");
	  break;
     case TREE:
	  fprintf(stream, "Tree\n");
	  break;
     case ERROR:
	  fprintf(stream, "Unrecognised\n");
	  break;	  
  }
}




void print_attval_list(stream, att_num, nlist)
FILE *stream;
int att_num;
List nlist;
{
     while (nlist){
	  fprintf(stream, "%s ",
		  att_val_string(att_num, *(int *) nlist -> head ->value));
	  nlist = nlist -> tail;
     }
     fprintf(stream, "\n");
}
     
  
	     

void print_int_list(stream, nlist)
FILE *stream;
List nlist;
{
     while (nlist){
	  fprintf(stream, "%d ", *(int *) nlist -> head ->value);
	  nlist = nlist -> tail;
     }
     fprintf(stream, "\n");
}

     
