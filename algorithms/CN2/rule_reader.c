/*  File:     rule_reader.c
    Author:   Robin Boswell
    Purpose:  Rule reading utils
*/ 

static char *SccsId = "@(#)rule_reader.c 5.1 9/25/91 MLT";

#include <strings.h>
#include <string.h>
#include "mdep.h"
#include "cn_externs.h"

List *value_ptr, value_list;
List *rule_ptr;
Rule *current_rule;

void init_rule_reader()
{
     clockin(global_rule_parameters.time_stamp);
     global_rule_list = (List)0;
     rule_ptr = &global_rule_list; 
     
}

void add_rule()
{
     *rule_ptr = new_listelement();
     ((*rule_ptr)->head) = new_object();
     current_rule =
       (((*rule_ptr)->head)-> value = (Rule *)ALLOC(sizeof(Rule)));
     current_rule -> selector = new_selector();
     (*rule_ptr)-> tail = (List)0;
     rule_ptr = &((*rule_ptr) -> tail);
}


void rule_par_sread(field, value)
char *field, *value;
{
     if (strcmp(field, "Examples") == 0)
       strcpy(global_rule_parameters.example_file, value);
     else if (strcmp(field, "Error_Estimate") == 0) {
	  if (strcmp(value, "LAPLACIAN") == 0)
	    global_rule_parameters.errest = LAPLACIAN;
	  else if (strcmp(value, "NAIVE") == 0)
	    global_rule_parameters.errest = NAIVE;
	  else if (strcmp(value, "ENTROPY") == 0)
	    global_rule_parameters.errest = ENTROPY;	    
     }
     else if (strcmp(field, "Algorithm") == 0){
	  if (strcmp(value, "ORDERED") == 0)
	    global_rule_parameters.algorithm = A_ORDERED;
	  else
	    global_rule_parameters.algorithm = A_UNORDERED; 
     }
}


void rule_par_nread(field, value)
char *field;
int value;
{
     if (strcmp(field, "Star") == 0)
       global_rule_parameters.star_size = value;       
}

void rule_par_fread(field, value)
char *field;
float value;
{
     if (strcmp(field, "Threshold") == 0)
       global_rule_parameters.threshold = value;
}

/* ------------------------------------------------------------ */

void init_value_list()
{
     value_list = (List)0;
     value_ptr = &value_list;
}

void add_att_val(string)
char *string;
{

     Object *object;

     *value_ptr = new_listelement();
     
     object = ((*value_ptr) -> head) = new_object();
#ifdef DEBUG_INPUT		    
     fprintf(stdout, "%s ", string);
#endif		    
     object-> value = intern(string);
     object -> otype = ATOM_TYPE;
     (*value_ptr) -> tail = (List)0;
     value_ptr = &((*value_ptr) -> tail);
}
