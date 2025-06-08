/*  File:     cn.c
    Author:   Robin Boswell
    Purpose:  CN
*/ 

static char *SccsId = "@(#)cn.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"

int star_size;
float threshold;

double   *global_distribution;
double    global_number_of_examples;
Node     *global_best_node;
int       current_class;

List rule_list, *rule_ptr;
Quotquae *dogs;
int initial_majority_class;

/* To clarify poor documentation:
   Creates an empty star and an empty rule list.
   Repeatedly:
   * Define a best complex that is null
   * Create an empty initial star
   * Find the best complex for the current set of examples
   * Remove the examples covered by the best complex from the set of examples
   until the training set is empty.
   It appears that the condition mentioned in the original CN2 papers that tests whether the best complex
   is not null before creating the rule, as well as to terminate the creation of rules, as mentioned in
   the original CN2 paper is not tested). */

List ordered_cn(example_list)
EList example_list;
{
     Quotquae *classified_examples;
     Star star;
     
     classified_examples = classify_examples(example_list);

     rule_list = new_listelement();
     rule_ptr = &rule_list;
          
     while (! empty_array(classified_examples)) {
	  /* Define a new global best complex */
	  global_best_node =  new_node();
          global_best_node->quotquae = classified_examples; 	  
	  record_global_distribution(classified_examples);
	  initial_majority_class = majority_class(classified_examples);
	  /* Create an initial star, containing only an empty condition (one that covers every example) */
	  star = initial_star(classified_examples);
	  /* Find the best complex for the remaining examples */
	  get_best_rule(star, classified_examples);
	  /* Remove examples covered by the best complex found */
	  filter(classified_examples);
	  /* Add the best rule to the rule list (rule's class is set to the majority class covered by that rule) */
	  add_rule_to_list();
     }
     (*rule_ptr) = (List)0;
     return(rule_list);
}



List unordered_cn(example_list)
EList example_list;
{
     Quotquae *classified_examples;
     Star star;
     Node *initial_best_node;
     BOOL some_rule_found, give_up;

     classified_examples = classify_examples(example_list);
     dogs = (Quotquae *)ALLOC(sizeof(Quotquae));
     
     rule_list = new_listelement();
     rule_ptr = &rule_list;
     
     /* Only do this once */
     record_global_distribution(classified_examples);
     
     for (current_class = 0; current_class < number_of_classes; ++current_class){
	  if (TRACE_CLASS){
	       fprintf(stdout, "Inducing for class `%s'\n",
		       val_string(IDclass -> avalues, current_class));
	  }

    /* We're inducing for current_class (say "dogs").
       Copy the dogs somewhere else.
       Find rules which cover dogs (and remove the dogs covered).
       Then put the dogs back, and go on the next class.    */
	  some_rule_found = FALSE;
	  give_up = FALSE;
	  store_dogs(dogs, classified_examples, current_class);	  
	  while (!  (all_dogs_gone(classified_examples, current_class)
		  || give_up)) {
	       initial_best_node = global_best_node =  new_node();

	       /* No longer re-evaluate this each time round       */
	       /* record_global_distribution(classified_examples); */
	       global_best_node->quotquae = classified_examples;
	       star = initial_star(classified_examples);
	       get_best_rule(star, classified_examples);

	       fprintf(stderr, "\n"); /* Niblett debugging */
	       

	       /* If no significant rule has been found, then we don't 
		   add a default rule at this point                   */
	       if (global_best_node != initial_best_node){
		    filter(classified_examples);
		    some_rule_found = TRUE;
		    add_rule_to_list();
	       }
	       else    /* Structured alternative to "break" */
		 give_up = TRUE;
	  }
	  if (TRACE_RULE && ! some_rule_found){
	       fprintf(stdout, "No significant rules for this class\n");
	  }
	  replace_dogs(dogs, classified_examples, current_class);
     }


     current_class = majority_class(classified_examples);
     add_default_rule();
     (*rule_ptr) = (List)0;

     /* Unlike the ordered case, we can't calculate easily add the
	distribution values as the rules are calculated, so we
	do it now, instead.                                   */
     
     add_distributions(example_list, rule_list);
     return(rule_list);
}


/* To clarify poor documentation:
   Repeatedly takes each condition in star, and specialise the condition. Continue until no further
   specialisations are found (i.e. star is empty). */

get_best_rule(star, classified_exs)
Star star;
Quotquae *classified_exs;
{
     int i;
     Node *node;
     
     if (TRACE_PRINT_STAR){
	  fprintf(stdout, "Current star:\n");
	  print_star(stdout, star);
     }

     maybe_print('.');
     
     for (i=0; i < star_size; ++i){
	  if (node = star[i]) {
	       if (TRACE_CURRENT_NODE) {
		    fprintf(stdout, "Specialising node with complex:\n");
		    if (!print_selector(stdout, node->selector))
		      fprintf(stdout, "TRUE\n");
	       }
	       specialise(node);  /* Throw each generalisation onto  */
          	                  /* the heap                        */
                                  /* To clarify poor documentation:
                                     The heap is a priority queue of complexes/conditions */
	  } 
     }
     
     if (heap_to_star(star))  /* If any specialisations were found, */
       get_best_rule(star, classified_exs);    /* then carry on.   */
                                               /* To clarify poor documentation:
                                                  Specialise complexes until star is empty
                                                  This is implemented using the outer while loop in the pseudocode of FindBestCondition from the papers */
     
}

/* To clarify poor documentation:
   Generate specialisations of a given complex, using every possible attribute that isn't already tested
   by the complex. Only specialise using attributes that aren't already tested in the complex. */

specialise(node)
Node *node;
{
     int i;
     for (i=0; i < number_of_attributes; ++i)
       if (acceptable(i, node))
	 specialise_att(node, i);
}

/* To clarify poor documentation:
   Specialises the complex with a given attribute test appropriately, depending on whether the attribute
   is discrete (i.e. nominal) or ordered (i.e. continuous) */
	  
specialise_att(node, att_no)
Node *node;
int att_no;
{
     Attribute *attribute = nth_attribute(att_no);
     if (attribute == IDclass)
       return(0);
     switch(ATT_TYPE(attribute)) {
     case ORDERED_TYPE:
	  specialise_ordered_att(node, attribute, att_no);	    	  
	  break;
     case DISCRETE_TYPE:
	  specialise_discrete_att(node, attribute, att_no);
	  break;
     }
     return(1);
}



record_global_distribution(classified_examples)
Quotquae *classified_examples;
{
     int i;
     global_number_of_examples = 0.0;
     /* global_best_node->quotquae = classified_examples; */
     global_distribution = (double *) ALLOC(number_of_classes *
					    sizeof(double));
     
     for (i=0; i < number_of_classes; ++i)
       global_number_of_examples +=
	 (global_distribution[i] = classified_examples[i].quot);
}


int majority_class(classified_examples)
Quotquae *classified_examples;
{
     int i, class_no;
     double max = (-1.0);
     
     for (i=0; i < number_of_classes; ++i)
       if (classified_examples[i].quot > max) {
	    max = classified_examples[i].quot;
	    class_no = i;
      }
     return(class_no);
}
     

BOOL empty_array(examples)
Quotquae *examples;
{
     int i;
     for (i=0; i< number_of_classes; ++i){
	  if (examples[i].quot > 0)
	    return(FALSE);
     }
     return(TRUE);
}

BOOL all_dogs_gone(examples, class)
Quotquae *examples;
int class;
{
     if (examples[class].quot > 0)
       return(FALSE);
     else
       return(TRUE);
}


add_rule_to_list()
{
     Rule *rule;
     int i;
     
     ((*rule_ptr)->head) = new_object();
     rule =
       (((*rule_ptr)->head)-> value = (Rule *)ALLOC(sizeof(Rule)));
     
     rule -> selector =
       global_best_node->selector;
     rule -> distribution = (double *)0;
     
     if (! ORDERED) {              
	  rule -> class = current_class;
     }
     else {
	  rule -> distribution =
	    (double *) ALLOC(number_of_classes * sizeof(double));
	  
	  /* If a significant rule has been found... */
	  if (global_best_node->rank->primus > -1) {
	       rule -> class = majority_class(global_best_node->quotquae);
	       for (i=0; i < number_of_classes; ++i){
		    rule -> distribution[i] =
		      global_best_node->quotquae[i].quot;	       
	       }
	  }
	  
	  else /* No significant rule */
	    {
		 rule -> class = initial_majority_class;
		 for (i=0; i < number_of_classes; ++i){
		      rule -> distribution[i] = global_distribution[i];
		 }
	    }
     }  
	  if (TRACE_RULE) {
	       BOOL first = TRUE;
	       fprintf(stdout, "Best rule is:\n");
	       print_rule(stdout, first, rule);
	  }
	  
	  (*rule_ptr)-> tail = new_listelement();
	  rule_ptr = &((*rule_ptr) -> tail);
}
     
     


add_default_rule()
{
     Rule *rule;
     
     ((*rule_ptr)->head) = new_object();
     rule =
       (((*rule_ptr)->head)-> value = (Rule *)ALLOC(sizeof(Rule)));
     
     rule -> selector = new_selector();
     rule -> class = current_class;
     rule -> distribution = (double *)0;
     
     if (TRACE_RULE) {
	  BOOL first = FALSE;
	  fprintf(stdout, "Default rule is:\n");
	  print_rule(stdout, first, rule);
     }
     
     (*rule_ptr)-> tail = new_listelement();
     rule_ptr = &((*rule_ptr) -> tail);
}


store_dogs(to, from, class)
Quotquae *from, *to;
int class;
{
     EList *e_ptr, elist, new_example;
     
     to[0].quot = from[class].quot;
     e_ptr = &(to[0].quae);
     elist = from[class].quae;

     while (elist){
	  new_example = new_ecopy();
	  new_example -> weight = elist -> weight;
	  new_example -> values = elist -> values;
	  (*e_ptr) = new_example;
	  e_ptr = &(new_example->next);
	  elist = E_NEXT(elist);
     }
     (*e_ptr) = (EList)0;
}


replace_dogs(dogs, examples, class)
Quotquae *dogs, *examples;
int class;
{
     examples[class].quot = dogs[0].quot;
     free_elist(examples[class].quae);
     examples[class].quae = dogs[0].quae;
}



add_distributions(example_list, rule_list)
EList example_list;
List rule_list;
{
     Rule *rule;
     int i, covering;
     EList examples;
     double weight_covered = 0.0;
     int class_number = ATT_NO(IDclass);     
     
     while (rule_list){
	  rule = rule_list->head->value;
	  rule -> distribution =
	    (double *) ALLOC(number_of_classes * sizeof(double));
	  for (i=0; i < number_of_classes; ++i){
	       rule -> distribution[i] = (double) 0.0;
	  }
	  if (trivial_selector(rule->selector)){
	       for (i=0; i < number_of_classes; ++i){
		    rule -> distribution[i] = global_distribution[i];
	       }
	       rule_list = rule_list -> tail;
	       continue;  /* Could break, as the default rule should
			     be last, but it might change one day. */
	  }

	  examples = example_list;
	  while (examples){
	       int class = E_DDVAL(class_number, examples);	       

	       covering = x_covered(examples, rule->selector,
				    &weight_covered);
	       switch (covering){
	       case UNKNOWN_COVERING:
	       case PARTIAL_COVERING:
		    rule->distribution[class] += 
		      weight_covered / E_WEIGHT(examples);
		    break;
	       case NO_COVERING:
		    break;
	       case TOTAL_COVERING:
		    rule->distribution[class] += E_WEIGHT(examples);
		    break;
	       }
	       examples = examples->next;
	  }
	  rule_list = rule_list->tail;
     }
}
