/*  File:     cn_print_thing.c
    Author:   Robin Boswell
    Purpose:  Print CN2 things
*/

static char *SccsId = "@(#)cn_print_thing.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include <stdio.h>
#include "mdep.h"
#include "cn_externs.h"

void print_star(stream, star)
FILE *stream;
Star star;
{
     int i;
     for (i=0; i< star_size; ++i) {
	  
       if (star[i]) {
	    fprintf(stream, "Node %d:\n", i);
	    print_node(stream, star[i]);
       }
       else
	 fprintf(stream, "Node %d is null!\n", i);
    }
     
}

     
void print_node(stream, node)
FILE *stream;
Node *node;
{
     fprintf(stream, "Complex:\n");
     if (! print_selector(stream, node->selector))
       fprintf(stream, "TRUE\n");
     print_rank(stream, node->rank);
     fprintf(stream, "Cover:\n   ");
     print_quots(stream, node->quotquae);

}

void print_rank(stream, rank)
FILE *stream;
Rank *rank;
{
     fprintf(stream, "Rank: %.2f \n", rank->primus);
}


void print_quotquaeoth(stream, quotquae)
FILE *stream;
Quotquae *quotquae;
{
     int number_of_classes = N_VALUES(IDclass);
     int i;
     
     for    (i=0; i < number_of_classes; ++i){
	  fprintf(stream, "# examples in class %d: %.2f\n", i, quotquae[i].quot);
	  /* fprintf(stream, "Examples are\n");	  
	     print_elist(stream, quotquae[i].quae); */
     }
     
}

void print_quots(stream, quotquae)
FILE *stream;
Quotquae *quotquae;
{
     int number_of_classes = N_VALUES(IDclass);
     int i;

     fprintf(stream, "[");
     for    (i=0; i < number_of_classes; ++i){
	  if (i > 0)
	    fprintf(stream, ",");
	  fprintf(stream, "%.2f", quotquae[i].quot);
     }
     fprintf(stream, "]\n");
     
}


BOOL print_selector(stream, selector)
FILE *stream;
Selector *selector;
{
     int i;
     BOOL previous = FALSE;

     if (trivial_selector(selector)){
	  return(FALSE);
     }

     fprintf(stream, "IF    ");
     for (i=0; i < number_of_attributes; ++i){
	     if (selector[i].setp == 0)
	       continue;
	     if (previous)
	       fprintf(stream, "  AND ");
	     switch (ATT_TYPE(nth_attribute(i))) {
	       case DISCRETE_TYPE:
	         fprintf(stream, "%s = ", nth_attribute_name(i));
	         fprintf(stream, "%s\n",
		       att_val_string(i, selector[i].discriminant->attval));
	         break;
	       case ORDERED_TYPE:
	         switch(selector[i].discriminant->bounds->instantiation) {
	           case LOWER_BOUND:
		           fprintf(stream, "%s > ", nth_attribute_name(i));
		           fprintf(stream, "%.2f\n",selector[i].discriminant->bounds->lower);
		           break;
	           case UPPER_BOUND:
		           fprintf(stream, "%s < ", nth_attribute_name(i));
		           fprintf(stream, "%.2f\n",selector[i].discriminant->bounds->upper);
		           break;
	           case DOUBLE_BOUND:
		           fprintf(stream, "%.2f",selector[i].discriminant->bounds->lower);
		           fprintf(stream, " < %s < ", nth_attribute_name(i));
		           fprintf(stream, "%.2f\n",selector[i].discriminant->bounds->upper);
		           break;
	         }
	         break;
	     }
	     previous = TRUE;
     }
     return(TRUE);
}



void print_rule_file(stream, rule_list)
FILE *stream;
List rule_list;
{
     fprintf(stream, "**RULE FILE**\n");
     print_rule_parameters(CN2, stream);
     print_rule_list(stream, rule_list, MACHINE);
}



void print_rule_list(stream, rule_list, mode)
FILE *stream;
List rule_list;
int mode;
{
     BOOL first;
     fprintf(stream, "\n");
     switch (mode){
     case HUMAN:
	  if (global_rule_parameters.algorithm & A_ORDERED) {
	       fprintf(stream, "     *-----------------------*\n");
	       fprintf(stream, "     |   ORDERED RULE LIST   |\n");
	       fprintf(stream, "     *-----------------------*\n\n");
	  }
	  else {
	       fprintf(stream, "     *------------------------*\n");
	       fprintf(stream, "     |  UN-ORDERED RULE LIST  |\n");
	       fprintf(stream, "     *------------------------*\n\n");
	  }
	  break;
     case MACHINE:
	  if (global_rule_parameters.algorithm & A_ORDERED)
	    fprintf(stream, "*ORDERED-RULE-LIST*\n\n");
	  else
	    fprintf(stream, "*UNORDERED-RULE-LIST*\n\n");
	  break;
     }

     first = TRUE;
     while (rule_list){
	  print_rule(stream, first, (Rule *) rule_list->head->value);
	  first = FALSE;
	  rule_list = rule_list -> tail;
     }
}


print_rule(stream, first, rule)
FILE *stream;
BOOL first;
Rule *rule;
{
     if (!first){
	  if (global_rule_parameters.algorithm & A_ORDERED)
	    fprintf(stream, "ELSE\n");
	  else
	    fprintf(stream, "\n");
     }

     if (print_selector(stream, rule->selector))
       fprintf(stream, "THEN  %s = %s  ",
	       IDclass -> aname -> name,
	       val_string(IDclass -> avalues, rule->class));
     else
       fprintf(stream, "(DEFAULT) %s = %s  ",
	       IDclass -> aname -> name,
	       val_string(IDclass -> avalues, rule->class));

     if (rule->distribution)
       print_distribution(stream, rule->distribution);
     else
       fprintf(stream, "\n");
}




void print_distribution(stream, distribution)
FILE *stream;
double *distribution;
{
     int i;
     
     fprintf(stream, "[");     
     for (i=0; i < number_of_classes; ++i) {
	  if (i > 0 && i < number_of_classes)
	    fprintf(stream, " ");
	  if (integerp(distribution[i]))
	    fprintf(stream, "%d", (int) distribution[i]);
	  else
	    fprintf(stream, "%.2f", distribution[i]);	    
     }

     fprintf(stream, "]");          
     fprintf(stream, "\n");
}

void print_epitome(stream, epitome, v)
FILE *stream;
Epitome *epitome;
int v;
{
     int i;
     for (i=0; i < v; ++i) 
	fprintf(stream, "%.2f   %d  %.2f\n",
		epitome[i].attval, epitome[i].class, epitome[i].weight);

}


void print_greeting()
{
     fprintf(stdout, "            ********************************\n");
     fprintf(stdout, "            *                              *\n");
     fprintf(stdout, "            *        Welcome to CN2!       *\n");
     fprintf(stdout, "            *                              *\n");
     fprintf(stdout, "            ********************************\n\n");
}

extern void print_cn_scores(stream, scores, def_acc, rule_list)
FILE *stream;
double **scores;
double def_acc;
List rule_list;
{
     int row, col;
     int class_values = N_VALUES(IDclass);
     register double val;
     double total, total_correct;
     double *row_totals = (double *)ALLOC(class_values * sizeof(double));
     BOOL intp = TRUE;

     // begin added
     int i, cond_count;
     double cond_accumulator, ave_non_default_rule_length, ave_rule_length;
     Selector* sel;
     int rule_count;
     // end added

     total = total_correct = 0.0;

     for (row = 0; row < class_values && intp; ++row)
       for (col = 0; col < class_values && intp; ++col)
	 if (! integerp(scores[row][col]))
	   intp = FALSE;


     fprintf(stream, "%s \n", "        PREDICTED");
     fprintf(stream, "ACTUAL     ");
     for (col = 0; col < class_values; ++col){
	  fprintf(stream, "%-7.7s ", val_string(IDclass -> avalues, col));
     }
     fprintf(stream, "%-8.8s \n", "Accuracy");

     for (row = 0; row < class_values; ++row){
	  row_totals[row] = 0.0;
	  fprintf(stream, "%8.8s ", val_string(IDclass -> avalues, row));
	  for (col = 0; col < class_values; ++col){
	       val = scores[row][col];
	       total += val;
	       row_totals[row] += val;
	       if (intp)
		 fprintf(stream, "%5d   ", (int) scores[row][col]);
	       else
		 fprintf(stream, "%6.2f  ", scores[row][col]);
	  }
	  total_correct += scores[row][row];
	  if (row_totals[row] > 0.0) {
	       val = 100 * scores[row][row] / row_totals[row];
	       fprintf(stream, "  %5.1f %%\n", val);
	  }
	  else
	    fprintf(stream, " ---\n");
     }

     val = 100 * total_correct / total;
     fprintf(stream, "Overall accuracy: %.*f %%\n", DBL_DIG, val);
     if (! (global_rule_parameters.algorithm & A_ORDERED))
       fprintf(stream, "Default accuracy: %.*f %%\n\n", DBL_DIG, def_acc);

     // begin added
     rule_count = 0;
     cond_accumulator = 0.0;

     while (rule_list) {
       rule_count++;
       // get rule count (include default rule)
       sel = ((Rule *) rule_list->head->value)->selector;
       if (!trivial_selector(sel)) {
         cond_count = 0;
         for (i = 0; i < number_of_attributes; i++) {
           if (sel[i].setp != 0) {
             cond_count++;
           }
         }
         cond_accumulator += (double) cond_count;
       }
       rule_list = rule_list->tail;
     }
     if (rule_count == 1) {
       ave_non_default_rule_length = 0.0;
       ave_rule_length = 1.0;
     } else {
       ave_non_default_rule_length = (cond_accumulator / (((double) rule_count) - 1.0));
       ave_rule_length = ((cond_accumulator + 1) / ((double) rule_count));
     }
     fprintf(stream, "Rule count (including default): %d\n", rule_count);                              // rule count (including default rule)
     fprintf(stream, "Non-default condition count: %.*f\n", DBL_DIG, cond_accumulator);                // condition count (excluding default rule)
     fprintf(stream, "Default-inclusive condition count: %.*f\n", DBL_DIG, cond_accumulator + 1);      // condition count (including default rule)
     fprintf(stream, "Average non-default rule length: %.*f\n", DBL_DIG, ave_non_default_rule_length); // average rule length (excluding default rule)
     fprintf(stream, "Average overall rule length: %.*f\n", DBL_DIG, ave_rule_length);                 // average rule length (including default rule)
     // end added

     FREE(row_totals);
}


extern void print_i_scores(stream, class, scores)
FILE *stream;
int class;
double **scores;
{
     int row, col;     
     register double val;
     double total, total_correct;
     double *row_totals = (double *)ALLOC(2 * sizeof(double));
     BOOL intp = TRUE;     
     total = total_correct = 0.0;

     for (row = 0; row < 2; ++row)
       for (col = 0; col < 2; ++col)
	 if (! integerp(scores[row][col]))
	   intp = FALSE;

     fprintf(stream, "%s \n", "                FIRED?");
     fprintf(stream, "ACTUAL CLASS ");

     fprintf(stream, "Yes     ");
     fprintf(stream, "No     ");

     fprintf(stream, "%-8.8s \n", "Accuracy");     
     
     for (row = 0; row < 2; ++row){
	  row_totals[row] = 0.0;
	  if (row == 0)
	    fprintf(stream, "%10.10s ", val_string(IDclass -> avalues, class));
	  else
	    fprintf(stream, "Not %6.6s ", val_string(IDclass -> avalues, class));
	  for (col = 0; col < 2; ++col){
	       val = scores[row][col];
	       total += val;
	       row_totals[row] += val;
	       if (intp)
		 fprintf(stream, "%5d   ", (int) scores[row][col]);	     
	       else
		 fprintf(stream, "%6.2f  ", scores[row][col]);
	  }
	  total_correct += scores[row][row];
	  if (row_totals[row] > 0.0) {
	       val = 100 * scores[row][row] / row_totals[row];
	       fprintf(stream, "  %5.1f %%\n", val);
	  }
	  else
	    fprintf(stream, " ---\n");
     }

     val = 100 * total_correct / total;
     fprintf(stream, "Overall accuracy: %.1f %%\n\n", val);     
     FREE(row_totals);
}


BOOL trivial_selector(selector)
Selector *selector;
{
     int i;
     
     for (i=0; i < number_of_attributes; ++i){
	  if (INSTANTIATED(selector[i].setp)) {
	       return(FALSE);
	  }
     }
     return(TRUE);
}


void print_rule_parameters(language, stream)
Language language;
FILE *stream;
{
     switch (language){
     case CKRL:
	  fprintf(stream, "{\n");	  	  
	  break;
     case CN2:
	  fprintf(stream, "@\n");	  
	  break;
     }

     fprintf(stream, "Time: %s\n", global_rule_parameters.time_stamp);
     fprintf(stream, "Examples: %s\n", global_rule_parameters.example_file);

     if (global_rule_parameters.algorithm & A_ORDERED)
       fprintf(stream, "Algorithm: ORDERED\n");
     else
       fprintf(stream, "Algorithm: UNORDERED\n");

     switch (global_rule_parameters.errest){
     case LAPLACIAN:
	  fprintf(stream, "Error_Estimate: LAPLACIAN\n");	  
	  break;
     case NAIVE:
	  fprintf(stream, "Error_Estimate: NAIVE\n");	  	  
	  break;
     case ENTROPY:
	  fprintf(stream, "Error_Estimate: ENTROPY\n");	  
	  break;
     }
     
     fprintf(stream, "Threshold: %.2f\n", global_rule_parameters.threshold);
     fprintf(stream, "Star: %d\n", global_rule_parameters.star_size);

     switch (language){
     case CKRL:
	  fprintf(stream, "}\n");	  	  
	  break;
     case CN2:
	  fprintf(stream, "@\n");	  
	  break;
     }
}


