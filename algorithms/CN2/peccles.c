/*  File:     peccles.c
    Author:   Robin Boswell
    Purpose:  Evaluation functions
*/ 

static char *SccsId = "@(#)peccles.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"


#include "cn_externs.h"
#include <math.h>

/*         The Laplacian Evaluation Function                        */
/* In the ORDERED case, we consider the class having the maximum    */
/* number of examples; in the UN_ORDERED case, we consider a        */
/* specified class (current_class), whether it is maximal or not    */

/* Second order correction to be applied to ranking based on
   entropy                                                          */
#define EC_FACTOR (10000.0)

int evaluate_rank(node)
Node *node;
{
     int i;
     int particular_class;
     double maximum_count = (double) -1;
     double particular_count;
     register double number_of_examples = (double) 0;
     double count, p;
     double neg_entropy = 0.0;

     if (ORDERED && ENTROPIC(errest_flag)) {
	  for (i=0; i < number_of_classes; ++i){
	       number_of_examples += node->quotquae[i].quot;
	  }
	  if (number_of_examples == 0)
	    return(USELESS);
	  for (i=0; i < number_of_classes; ++i){
	       p = node->quotquae[i].quot / number_of_examples;
	       if (p > 0.0)
		 neg_entropy += p * log2(p);
	  }
     }

     /* N.B. Even when we're using ENTROPY, we still
	need to determine particular_class, for the
	BETTER/WORSE THAN DEFAULT calculation    */
     if (ORDERED) {
	  for (i=0; i < number_of_classes; ++i){
	       if ((count = node->quotquae[i].quot) > maximum_count) {
		    maximum_count = count;
		    particular_class = i;
	       }
	       number_of_examples +=count;
	  }
	  if (number_of_examples == 0)
	    return(USELESS);
	  particular_count = maximum_count;
     }

     else {
	  for (i=0; i < number_of_classes; ++i){
	       number_of_examples += node->quotquae[i].quot;
	  }
	  if (number_of_examples == 0)
	    return(USELESS);
	  particular_count = node->quotquae[current_class].quot;
	  particular_class = current_class;
     }

     /*
     number_of_examples = total examples covered by this complex/node
     particular_count = maximum_count = number of examples in the most common class in this complex/node
     particular_class = class index of the most common class in this complex/node
     */

     switch (errest_flag) {
     case LAPLACIAN:
	  node->rank->primus = (particular_count + 1.0) /
	    (number_of_examples + number_of_classes);
	  break;
     case NAIVE:
	  node->rank->primus = particular_count /
	    number_of_examples;
	  break;
     case ENTROPY:
	  node->rank->primus = neg_entropy;
	  break;
     case ENTROPY2:
	  node->rank->primus = neg_entropy +
	    particular_count / EC_FACTOR;
	  break;
	  
     }
	 
     if (particular_count / number_of_examples >
	 global_distribution[particular_class] / global_number_of_examples)
       return(BETTER_THAN_DEFAULT);
     else
       return(WORSE_THAN_DEFAULT);

}



double dist_eval_rank(distribution, total_weight)
double *distribution;
double total_weight;
{
     int i;
     double maximum_count = (double) -1;
     double count, p;
     double neg_entropy = 0.0;
     
     if (ORDERED && ENTROPIC(errest_flag)) {
	  for (i=0; i < number_of_classes; ++i){
	       p = distribution[i] / total_weight;
	       if (p > 0.0)
		 neg_entropy += p * log2(p);
	  }
     }
     
     else if (ORDERED) {
	  for    (i=0; i < number_of_classes; ++i){
	       if ((count = distribution[i]) > maximum_count) 
		 maximum_count = count;
	  }
     }
     else
       maximum_count = distribution[current_class];

     /*
     maximum_count = weight of training examples in the maximally occurring class
     total_weight = total weight of all training examples (each example seems to have a weight of 1 unless there are "unknown" or "don't care" examples)
     */
     
     switch (errest_flag) {
     case LAPLACIAN:
	  return((maximum_count + 1.0) /
		 (total_weight + number_of_classes));
	  break;
     case NAIVE:
	  return(maximum_count / total_weight);
	  break;
     case ENTROPY:
	  return(neg_entropy);
	  break;
     case ENTROPY2:
	  return(neg_entropy + maximum_count / EC_FACTOR);
	  break;	  
     }



}



BOOL leq_node(node1, node2)
Node *node1, *node2;
{
     if (node1->rank->primus < node2->rank->primus)
       return(TRUE);
     else if (node1->rank->primus == node2->rank->primus &&
	  node1->rank->secundus <= node2->rank->secundus)
       return(TRUE);
     else
       return(FALSE);
}

BOOL worse_node(node1, node2)
Node *node1, *node2;
{
     if (node1->rank->primus < node2->rank->primus)
       return(TRUE);
     else if (node1->rank->primus == node2->rank->primus &&
	  node1->rank->secundus < node2->rank->secundus)
       return(TRUE);
     else
       return(FALSE);
}

BOOL better_node(node1, node2)
Node *node1, *node2;
{
     if (node1->rank->primus > node2->rank->primus)
       return(TRUE);
     else if (node1->rank->primus == node2->rank->primus &&
	  node1->rank->secundus > node2->rank->secundus)
       return(TRUE);
     else
       return(FALSE);
}

BOOL better_rank(rank1, rank2)
Rank *rank1, *rank2;
{
     if (rank1->primus > rank2->primus)
       return(TRUE);
     else if (rank1->primus == rank2->primus &&
	  rank1->secundus > rank2->secundus)
       return(TRUE);
     else
       return(FALSE);
}

/* The maximum potential rank is that obtained by
   setting all but the maximal count to zero  */
/* To clarify poor documentation: This finds the best possible quality measure that could be scored by a complex */
potential_rank(node, potential)
Node *node;
Rank *potential;
{
     int i;
     double maximum_count = (double) -1;
     double count;

     switch(global_rule_parameters.errest) {
     case LAPLACIAN:
	  for (i=0; i < number_of_classes; ++i)
	    if ((count = node->quotquae[i].quot) > maximum_count) 
	      maximum_count = count;           // maximum_count = count = number of examples in the most common class in this complex/node
	  potential->primus = (maximum_count + 1.0) /
	    (maximum_count + number_of_classes);
	  break;
     case NAIVE:
	  potential->primus = 1.0;
	  break;
     case ENTROPY:
	  potential->primus = 0.0;	  
	  break;
     }
     
     potential->secundus = (FLOAT) -1;     
     return(TRUE);
}
     
// computes likelihood ratio statistic, and compares it to the threshold

BOOL significant_p(node, significance)
Node *node;
double *significance;
{
     int i;
     double examples_at_node, ratio, distance;

     examples_at_node = 0.0;
     distance = 0.0;
     
     for (i = 0; i < number_of_classes; ++i)
       examples_at_node += node->quotquae[i].quot;
     ratio = examples_at_node / global_number_of_examples;

/*
     global_distribution[i] * ratio   = ei   (expected)
     
     node->quotquae[i].quot           = fi    (observed)

     Calculate sum of fi * log fi / ei
                                                          */
     for (i = 0; i < number_of_classes; ++i)
       if ((node->quotquae[i].quot > 0.0) && (global_distribution[i] > 0.0))
	 distance += node->quotquae[i].quot *
	   log(node->quotquae[i].quot /( global_distribution[i] * ratio));

     *significance = 2 * distance;
     
     if (*significance > threshold)
       return(TRUE);
     else
       return(FALSE);

}

BOOL integerp(x)
double x;
{
     if (x == floor(x))
       return(TRUE);
     else
       return(FALSE);
}


/* For unordered rules, if max_class_flag is set,
   check that the class predicted has maximum count */
BOOL max_class_p(node)
Node *node;
{
     int i;
     double class_count;
     
     if (ORDERED || ! max_class_flag)
       return(TRUE);

     class_count = node->quotquae[current_class].quot;
     
     for (i=0; i < number_of_classes; ++i)
       if (i != current_class &&
	   node->quotquae[i].quot > class_count)
	 return(FALSE);
     return(TRUE);
     
}
