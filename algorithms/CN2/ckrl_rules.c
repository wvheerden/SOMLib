/*  File:     ckrl_rules.c
    Author:   Robin Boswell
    Purpose:  Write rules in CKRL
*/ 

static char *SccsId = "@(#)ckrl_rules.c 5.2 9/27/91 MLT"; 


#include <string.h>
#include <stdio.h>
#include <math.h>  /* Why? */
#include "mdep.h"
#include "cn_externs.h"


#define MAX_DEPTH (50)    /* Max depth of tree */

typedef enum {
     LE = 0,
     GT = 1,
     EQ = 3,
     MEM = 4
  } Relation;

typedef struct {
     int attno;
     Relation relation;
     union {
	  Ordered o;
	  Discrete d;   	  
	  List l;
     }	value;
} Branch;


Branch branches[MAX_DEPTH];
int number_of_rules;

int ckrl_rules_header(fp)
FILE *fp;
{
     number_of_rules = 0;
     print_rule_parameters(CKRL, fp);
}


int ckrl_print_rules(fp, rule_list)
FILE *fp;
List rule_list;
{
     
     while (rule_list){
	  ckrl_print_rule(fp, (Rule *) rule_list->head->value);
	  rule_list = rule_list -> tail;
     }
}



ckrl_print_rule(stream, rule)
FILE *stream;
Rule *rule;
{
     int i;
     if (global_rule_parameters.algorithm & A_ORDERED){
	  if (number_of_rules == 0){
	       fprintf(stream, "defrule rule%d\n", 1);
	       fprintf(stream, "if (\n");     		 
	  }
	  else if (! trivial_selector(rule->selector))
	    fprintf(stream, "else if (\n");
	  else
	    fprintf(stream, "else \n");
     }
     else {
	  fprintf(stream, "defrule rule%d\n", number_of_rules + 1);
	  fprintf(stream, "if (\n");     
     }

     /* This bit taken from the rule-printing routine
	in cn_print_thing.c */
     if (print_selector_ckrl(stream, rule->selector)){
	  print_ckrl_nominal(stream, "then   (?x.%s = ",  IDclass -> aname -> name);
	  print_ckrl_nominal(stream, "%s", 
		  val_string(IDclass -> avalues, rule->class));

	  if (global_rule_parameters.algorithm & A_ORDERED)	  
	    fprintf(stream, ")\n\n");
	  else
	    fprintf(stream, ", ?x.covered_by_rule = true);\n\n");	    
     }
     else {
	  if (global_rule_parameters.algorithm & A_ORDERED)   {
	       print_ckrl_nominal(stream, " (?x.%s =",  IDclass -> aname -> name);    
	       print_ckrl_nominal(stream, " %s);\n\n",
				  val_string(IDclass -> avalues, rule->class));
	  }
	  else {
	       fprintf(stream, "   ?x.covered_by_rule eq false\n)\n");
	       print_ckrl_nominal(stream, "then   (?x.%s =",  IDclass -> aname -> name);	  
	       print_ckrl_nominal(stream, " %s);\n\n",
				  val_string(IDclass -> avalues, rule->class));
	  }
     }
     ++number_of_rules;
}

BOOL print_selector_ckrl(stream, selector)
FILE *stream;
Selector *selector;
{
     int i;
     BOOL previous = FALSE;

     if (trivial_selector(selector)){
	  return(FALSE);
     }
     
     fprintf(stream, "      ");
     for (i=0; i < number_of_attributes; ++i){
	  if (selector[i].setp == 0)
	    continue;
	  if (previous)
	    fprintf(stream, ",\n      ");
	  switch (ATT_TYPE(nth_attribute(i))) {
	  case DISCRETE_TYPE:
	       print_ckrl_nominal(stream, "   ?x.%s ", nth_attribute_name(i));
	       fprintf(stream, "eq %s",
		       att_val_string(i, selector[i].discriminant->attval));
	       break;
	  case ORDERED_TYPE:
	       switch(selector[i].discriminant->bounds->instantiation){
	       case LOWER_BOUND:
		    print_ckrl_nominal(stream, "   ?x.%s ", nth_attribute_name(i));
		    fprintf(stream, "gt %.2f",selector[i].discriminant->bounds->
			    lower);
		    break;
	       case UPPER_BOUND:
		    print_ckrl_nominal(stream, "   ?x.%s ", nth_attribute_name(i));
		    fprintf(stream, "lt %.2f",selector[i].discriminant->bounds->
			    upper);
		    break;
	       case DOUBLE_BOUND:
		    print_ckrl_nominal(stream, "   ?x.%s ", nth_attribute_name(i));		    
		    fprintf(stream, "gt %.2f",selector[i].discriminant->bounds->
			    lower);
		    fprintf(stream, ",\n      ");
		    print_ckrl_nominal(stream, "   ?x.%s ", nth_attribute_name(i));
		    fprintf(stream, "lt %.2f",selector[i].discriminant->bounds->
			    upper);
		    break;
	       }
	       break;
	  }
	  previous = TRUE;
     }
     fprintf(stream, "\n)\n");
     return(TRUE);
}


ckrl_print_condition(fp)
FILE *fp;
{
     Attribute *attribute; /*  = nth_attribute(branch->attno); */

     print_ckrl_nominal(fp, "   ?x.%s ", attribute->aname->name);
     /*
     switch (branch->relation){
     case LE:
	  fprintf(fp, "le ");	  
	  break;
     case GT:
	  fprintf(fp, "gt ");	  
	  break;	  
     case EQ:
	  fprintf(fp, "eq ");
	  break;	  
     case MEM:
	  fprintf(fp, "in ");	  
	  break;	  
     }

     switch(ATT_TYPE(attribute)){
     case DISCRETE_TYPE:
	  fprintf(fp, "%s", val_string(A_VALUES(attribute), branch->value.d));
	  break;
     case ORDERED_TYPE:
	  switch (ATT_NTYPE(attribute)){
	  case INTEGRAL:
	       fprintf(fp, "%d", (int) floor((double) branch->value.o));
	       break;
	  case REAL:
	       fprintf(fp, "%.2f", branch->value.o);
	       break;
	  }
	  break;
     }
     */
     
     
}

ckrl_print_conclusion(fp)
FILE *fp;
{
     /*
     SplitType s_type = SPLIT_TYPE(TREE_NODE(tree));
     
     fprintf(fp, "then (");
     print_ckrl_nominal(fp, "?x.%s = ", IDclass->aname->name);     
     
     if (s_type == CLASH  || s_type == LEAF){
	  switch (ATT_TYPE(IDclass)) {
	  case ORDERED_TYPE:
	       switch (ATT_NTYPE(IDclass)){
	       case INTEGRAL:
		    fprintf(fp, "%d",
		      (int) floor((double) SPLIT_POINT(TREE_NODE(tree)).o));
		    break;
	       case REAL:
		    fprintf(fp, "%.2f", SPLIT_POINT(TREE_NODE(tree)).o);		    
		    break;
	       }
	       break;	       
	  case DISCRETE_TYPE:
	       fprintf(fp, "%s",
		       val_string(IDclass->avalues,
				  SPLIT_POINT(TREE_NODE(tree)).d));
	       break;
	  }
     }
     else if (s_type == BLANK){
	  mess("WARNING: Can't handle NULL nodes yet.\nOutput will be invalid.");
     }  */
     

     fprintf(fp, ");\n\n");
}


ckrl_rules_footer(fp)
FILE *fp;
{
     char buffer[BUFSIZ];
     int i, block_size;
     
     root_name(data_flow.example_file, buffer);

     fprintf(fp, "\ndefblock %s-rule-list\n", buffer);
     fprintf(fp, "   ruleref (\n");
     fprintf(fp, "      ");     
     if (global_rule_parameters.algorithm & A_ORDERED)
       block_size = 1;
     else
       block_size = number_of_rules;
     
     for (i = 1; i <= block_size; ++i){
	  fprintf(fp, "rule%d", i);
	  if (i < block_size)
	    fprintf(fp, ", ");
	  else
	    fprintf(fp, "\n");	    
     }
     fprintf(fp, "   );\n\n");
     fprintf(fp, "ckrl end\n");

}
