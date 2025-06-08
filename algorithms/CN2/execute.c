/*  File:     execute.c
    Author:   Robin Boswell
    Purpose:  Apply rules to examples
*/ 

static char *SccsId = "@(#)execute.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"


Quotquae *dogs;

BOOL evaluate_rules()
{
     BOOL done = FALSE;
     
     if (DATA_RULES && DATA_EXAMPLES) {
	  while (!done) {
	       fprintf(stdout, "EVAL> ");
	       fflush(stdout);
	       switch(select_char("aci\nhq?")){
	       case 'a':
		    fprintf(stdout, "all\n");
		    execute_rules();
		    break;
	       case 'c':
		    fprintf(stdout, "class\n");		    
		    fprintf(stdout, "Option %c not currently available\n", 'c');
		    break;
	       case 'i':
		    fprintf(stdout, "individual\n");		    
		    execute_individual();
		    break;
	       case 'h':
	       case '?':
		    fprintf(stdout, "help\n");
		    help_execute();
		    break;
	       default:
		    fprintf(stdout, "\n");
		    done = TRUE;
		    break;
	       }
	  }
	  return(TRUE);
     }
     else {
	  if (DATA_RULES)
	    fprintf(stdout, "No examples to test\n");
	  else if (DATA_EXAMPLES)
	    fprintf(stdout, "No rules to execute\n");
	  else
	    fprintf(stdout, "No examples and no rules!\n");
	  return(FALSE);
       }
}


void execute_rules()
{
     double **scores;

     fprintf(stdout, "Executing rules...\n");
     scores = execute(example_list, global_rule_list);
     if (global_rule_parameters.algorithm & A_ORDERED)
       print_cn_scores(stdout, scores, 0.0, global_rule_list);
     else
       print_cn_scores(stdout, scores,
		       default_acc(global_rule_list, example_list), global_rule_list);
     free(scores);
}

void execute_individual()
{
     double weight_covered;
     double **scores = new_cn_scores(2);
     int predicted_class, true_class, covering;
     int class_number = ATT_NO(IDclass);       
     List rules = global_rule_list;
     EList examples;
     Rule *rule;
     int count = 1;
     
     if (global_rule_parameters.algorithm & A_ORDERED){
	  fprintf(stdout, "Individual rule evaluation is currently available\n");
	  fprintf(stdout, "only for unordered rules\n");
	  return;
     }

     while (rules){
	  rule = rules->head->value;
	  scores[0][0] = scores[0][1]
	    = scores[1][0] = scores[1][1] = 0.0;

	  examples = example_list;
	  while (examples){
	       weight_covered = 0.0;
	       covering = x_covered(examples, rule->selector,
				    &weight_covered);
	       true_class = E_DDVAL(class_number, examples);
	       predicted_class = rule->class;
	       switch (covering){
	       case UNKNOWN_COVERING:
	       case PARTIAL_COVERING:
		    if (predicted_class == true_class) {
			 scores[0][0] += weight_covered;
			 scores[0][1] += examples->weight - weight_covered;
		    }
		    else {
			 scores[1][0] += weight_covered;
			 scores[1][1] += examples->weight - weight_covered;
		    }
		    break;
	       case NO_COVERING:
		    if (predicted_class == true_class)
		      scores[0][1] += examples->weight;
		    else
		      scores[1][1] += examples->weight;
		    break;
	       case TOTAL_COVERING:
		    if (predicted_class == true_class)
		      scores[0][0] += examples->weight;
		    else
		      scores[1][0] += examples->weight;
		    break;
	       }
	       examples = examples -> next;
	  }

	  fprintf(stdout, " ------------ Rule %d ------------\n\n", count++);
	  print_rule(stdout, TRUE, rule);
	  fprintf(stdout, "\n");
	  print_i_scores(stdout, predicted_class, scores);
	  rules = rules->tail;
     }
     free(scores);
}


double **execute(examples, rule_list)
EList examples;
List rule_list;
{
     double **scores = new_cn_scores(N_VALUES(IDclass));
     
     if (global_rule_parameters.algorithm & A_ORDERED)
       general_whoosh(examples, rule_list, scores);
     else
       general_whoosh(examples, rule_list, scores);       
     return(scores);
}


BOOL ordered_whoosh(examples, rule_list, scores)
EList examples;
List rule_list;
double **scores;
{
     Rule *rule;
     Quotquae *classified_examples;

     classified_examples = classify_examples(examples);
     
     while (rule_list){
	  rule = rule_list->head->value;
	  current_class = rule->class;
	  x_filter(classified_examples, rule, scores);
	  rule_list = rule_list->tail;
     }
}


BOOL general_whoosh(examples, rule_list, scores)
EList examples;
List rule_list;
double **scores;
{
     double *decisions = (double *)ALLOC(number_of_classes *
					 sizeof(double));
     double weight_covered = 0.0; /* For sabertool */
     double weight_left;
     
     BOOL some_match;
     
     List rules;
     int class_number = ATT_NO(IDclass);
     int covering, predicted_class, true_class;
     Rule *rule;

     while (examples){
	  zero(decisions);
	  some_match = FALSE;
	  weight_left = E_WEIGHT(examples);
	  rules = rule_list;

	  /* If ORDERED, stop executing rules once
	     you've covered the example. */
	  
	  while (rules && ((! ORDERED) || weight_left > 0.0) ) {
	       rule = rules->head->value;
	       if (trivial_selector(rule->selector)){
		    if (! some_match) {
			 vector_add(decisions, rule->distribution, 1.0);
		    }
	       }
	       else {
		    covering = x_covered(examples, rule->selector,
					 &weight_covered);
		    switch (covering){
		    case UNKNOWN_COVERING:
		    case PARTIAL_COVERING:
			 vector_add(decisions, rule->distribution,
				    weight_covered / E_WEIGHT(examples));
			 weight_left -= weight_covered / E_WEIGHT(examples);
                         some_match = TRUE;
		    case NO_COVERING:
			 break;
		    case TOTAL_COVERING:
			 vector_add(decisions, rule->distribution, 1.0);
                         some_match = TRUE;
			 weight_left = 0.0;
			 break;
		    }
	       }
	       rules = rules -> tail;
	  }
	  predicted_class = max_class(decisions);
	  true_class = E_DDVAL(class_number, examples);	  
	  scores[true_class][predicted_class] += E_WEIGHT(examples);
	  examples = examples -> next;
     }
}




/* Performs the role of filter(), but in execution rather than
   in learning mode. Also augments `score' according to the
   examples that are filtered out.    Should eventually be able 
   to combine the code into one function, with the odd switch 
   statement for unknowns, but prefer to delay this until I know 
   what I'm doing.
                                                          */
void x_filter(classified_examples, rule, scores)
Quotquae *classified_examples;
Rule *rule;
double **scores;
{
     int i;
     EList elist, *eptr;
     double weight_covered;
     int covering, true_class;

     for (i=0; i < number_of_classes; ++i){
	  elist = classified_examples[i].quae;
	  eptr = &classified_examples[i].quae;

          while (elist) {
	       if (E_WEIGHT(elist) > 0.0) {	       
		    covering = x_covered(elist, rule->selector,
					 &weight_covered);
		    switch (covering){
		    case UNKNOWN_COVERING:
			 /* Carry on down... */
		    case PARTIAL_COVERING:
			 E_WEIGHT(elist) = E_WEIGHT(elist) - weight_covered;
			 /* Carry on down... */
		    case NO_COVERING:
			 (*eptr) = elist;
			 eptr = &(elist->next);
			 break;
		    case TOTAL_COVERING:
			 true_class = E_DVAL(IDclass, elist);
			 scores[true_class][current_class] += E_WEIGHT(elist);
			 break;
		    }
	       }
	       
	       elist = elist->next;	       
	  }
	  (*eptr) = (EList)0;	
     }
}


int x_covered(elist, selector, weight_covered)
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
		 /*   weight = weight / N_VALUES(attribute); */
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




vector_add(out, in, ratio)
double *out, *in, ratio;
{
     int i;
     if (ratio == 1.0)
       for (i=0; i< number_of_classes; ++i){
	    out[i] += in[i];
       }
     else
       for (i=0; i< number_of_classes; ++i){
	    out[i] += (in[i] * ratio);
       }       
}


int max_class(class_vals)
double *class_vals;
{
     double max_val = -1.0;
     int i, max = -1;
     
     for (i = 0; i < number_of_classes; ++i){
	  if (class_vals[i] > max_val){
	       max = i;
	       max_val = class_vals[i];
	  }
     }
     return(max);
}

zero(class_vals)
double *class_vals;
{
     int i;
     
     for (i = 0; i < number_of_classes; ++i)
	  class_vals[i] = 0.0;
}

     
double default_acc(rule_list, examples)
List rule_list;
EList examples;
{
     Rule *rule = (Rule *) last(rule_list)->head->value;
     int class = rule->class;
     double weight_class = 0.0;
     double weight_all = 0.0;     

     while (examples){
	  weight_all += E_WEIGHT(examples);
	  if (E_DVAL(IDclass, examples) == class)
	    weight_class += E_WEIGHT(examples);
	  examples = examples -> next;
     }

     return(100 * weight_class / weight_all);
}

help_execute()
{
     fprintf(stdout, "Options:\n");   
     fprintf(stdout, "   a(ll): Evaluate the current rule set.\n");
     fprintf(stdout,
	     "   i(ndividual): Give statistics for each individual rule\n");
	     fprintf(stdout, "   <RET>: Return to CN> prompt\n");
}

