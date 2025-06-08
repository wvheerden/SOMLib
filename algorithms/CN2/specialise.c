/*  File:     specialise.c
    Author:   Robin Boswell
    Purpose:  Specialise

    Change Log:

      3/20/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Removed register declaration of h_ranks/l_ranks within
          routine specialise_ordered_att()
*/ 

static char *SccsId = "@(#)specialise.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"
#define GREATER_THAN 0
#define LESS_THAN 1

int epitome_compare();
int SOA_compare();

/* Create all nodes corresponding to specialisations of att_no,
   and toss them on the heap                                  */

/* To clarify poor documentation:
   Generate specialisations of a given complex using each possible value of a given attribute. Specialise
   the complex with each attribute that doesn't change (reduce) the number of examples covered by the
   complex. The latter condition seems to be an optimisation, so that useless attribute value tests
   aren't added to newstar (but could possibly alter the final outcomes - for example, when a lot of
   non-changing tests are generated, which would be added to newstar in the original algorithm). */

specialise_discrete_att(node, attribute, att_no)
Node *node;
Attribute *attribute;
int att_no;
{             
     int i;
     Node *lower_node;
     
     for (i=0; i < N_VALUES(attribute); ++i){
	  lower_node = new_node();
	  copy_selector(lower_node, node);

	  if (!lower_node->selector[att_no].discriminant)
	    lower_node->selector[att_no].discriminant = new_discriminant(attribute);
	  
          /* Specialise the given complex */
	  lower_node->selector[att_no].discriminant->attval = i;
	  lower_node->selector[att_no].setp = TOTAL_INSTANTIATION;

	  /* Only process specialised complex if the new condition changes examples the complex classifies */
	  if (filter_discrete_examples(lower_node, node, att_no, i))
	    /* Takes specialised complex, updates best, and adds it to newstar */
	    assess(lower_node);
	  else
	    free_node(lower_node);
     }
     return(1);
}

/* To clarify poor documentation:
   Specialises the complex with a given ordered (i.e. continuous) attribute test. */

specialise_ordered_att(node, attribute, att_no)
Node *node;
Attribute *attribute;
int att_no;
{
     register int i;
     int j, v, n, uk;
     int max_bounds = star_size / 2;
     float bound, previous_bound;
     Node *lower_node;
     EList ex;
     unsigned short instant;
     Discriminant *disc, *discl;
     
     double l_ranks[3];
     double h_ranks[3];
     
     SOA_pair *ptr, *gl_ptr, *gu_ptr, *good_lower_bounds, *good_upper_bounds;
     BOOL seek_lower = FALSE;
     BOOL seek_upper = FALSE;     
     Epitome *epitome =
       (Epitome *) ALLOC(number_of_examples * sizeof(Epitome));
     Epitome *epitome2 =
       (Epitome *) ALLOC(number_of_examples * sizeof(Epitome));
     
     double h_weight = 0.0;
     double l_weight = 0.0;
     
     double *h_distribution = (double *)ALLOC(number_of_classes * sizeof(double));
     double *l_distribution = (double *)ALLOC(number_of_classes * sizeof(double));

     attribute = attribute;  /* To keep saber_tool quiet */

     if (!node->selector[att_no].discriminant)
       node->selector[att_no].discriminant = new_discriminant(attribute);       
     disc = node->selector[att_no].discriminant;
     
     if (node->selector[att_no].setp == 0)
       disc->bounds->instantiation = 0;

     instant = disc->bounds->instantiation;

     /* In order to locate local maxima, we keep track of three  */
     /* successive values of rank.                               */
     /*                                                          */
     /* The idea is to pick the best few local maxima, NOT just  */
     /* the best few scores.                                     */

     for (i=0; i<3; ++i)
       l_ranks[i] = h_ranks[i] = -1.0;
     
     /* Load examples into the epitome, which will then be sorted according to the attribute value we're building conditions for */
     /* h_distribution stores the counts of weights for each class (weight seems to be 1 if no examples are marked "unknown" or "don't care") */
     /* h_weight stores counts of weights for all classes */

     v=0; uk = 0;
     for (i=0; i < number_of_classes; ++i){
	  h_distribution[i] = 0.0;
	  l_distribution[i] = 0.0;	  
	  ex = node->quotquae[i].quae;
	  while (ex) {
	       Ordered val = E_OOVAL(att_no, ex);
	       double w;

	       if (O_DC(val)){
		/*    h_distribution[i] += (w= E_WEIGHT(ex) / 2);
		    l_distribution[i] += w;		    
		    h_weight += E_WEIGHT(ex); */

		    h_distribution[i] += (w = E_WEIGHT(ex));
		    l_distribution[i] += w;		    
		    h_weight += (2 * w); 
	       }
	       else if (O_UNK(val)){
		    epitome2[uk].class = i;
		    epitome2[uk++].weight = E_WEIGHT(ex);
		    h_weight += E_WEIGHT(ex);		      
	       }
	       else {
		    epitome[v].attval = val;
		    epitome[v].class = i;
		    h_distribution[i] += (epitome[v].weight = E_WEIGHT(ex));
		    h_weight += epitome[v++].weight;
	       }
	       
	       ex = E_NEXT(ex);
	  }
     }

     /* Distribute unknowns by making appropriate small */
     /* additions to the weights of examples with the same class  */
     for (i=0; i < uk; ++i){
	  double bit, w;
	  int c = epitome2[i].class;
	  if (h_distribution[c]){
	       bit = epitome2[i].weight / h_distribution[c];
	       for (j = 0; j < v; ++j)
		 if (epitome[j].class == c)
		   epitome[c].weight += bit;
	  }
	  else { /* Treat as don't care */
	       h_distribution[c] += (w= epitome2[i].weight / 2);
	       l_distribution[c] += w;
	  }
     }

     FREE(epitome2);

     /* Check whether we've already got a lower or upper bound condition (may have been added in a previous specialisation) */

     if (! LOWER_BOUND_SET_P(instant))
       seek_lower = TRUE;
     if (! UPPER_BOUND_SET_P(instant))
       seek_upper = TRUE;
     
     gl_ptr = good_lower_bounds = (SOA_pair *)ALLOC(v * sizeof(SOA_pair));
     gu_ptr = good_upper_bounds = (SOA_pair *)ALLOC(v * sizeof(SOA_pair));

     /* Sort the examples according to att_val */
     qsort(epitome, v, sizeof(Epitome), epitome_compare);

     previous_bound = 0.0; /* Actually redundant, but keeps saber happy */
                           /* Why on earth is this commented, and the actual functionality isn't? */

     /* Find values of bound corresponding to local maxima of rank */
     /* Store them in good_lower_bounds and good_upper_bounds      */
     /* (as appropriate)                                           */

     for (i=0; i < (v-1); ++i){
	  /* Update h_distribution, h_weight, l_distribution and l_weight so that they are representative of each successive candidate split */
	  if (seek_lower) {
	       h_distribution[epitome[i].class] -= epitome[i].weight;
	       h_weight -= epitome[i].weight;
	  }
	  if (seek_upper) {
	       l_distribution[epitome[i].class] += epitome[i].weight;
	       l_weight += epitome[i].weight;
	  }
	  if (epitome[i].attval == epitome[i+1].attval)
	    continue;

	  /* We consider each candidate boundary in turn */
	  /* The current boundary is half way between the current data example's attribute value, and the next example's attribute value */
	  /* We are searching candidate boundaries in order, which is why we sort the attribute values sequentially */
	  bound = (epitome[i].attval + epitome[i+1].attval) / 2;

	  /* Note, you only discover a score was a local max/min */
	  /* the next time round (hence "previous_bound").       */
	  if (seek_lower) {
	       /* Get the accuracy of the split made according to the current candidate boundary, assuming a "greater than" split */
	       /* We are searching for a local maximum in accuracy score (i.e. higher than previous split and next split) */
	       /* If we find one, good_lower_bounds (a.k.a. gl_ptr) stores the candidate boundary */
	       h_ranks[2] = dist_eval_rank(h_distribution, h_weight);
	       if (h_ranks[1] >= h_ranks[0] &&
		   h_ranks[1] > h_ranks[2] && i > 0){
		    gl_ptr->bound = previous_bound;
		    (gl_ptr++)->score = h_ranks[1];	
	       }
	       
	       h_ranks[0] = h_ranks[1];
	       h_ranks[1] = h_ranks[2];
	  }
	  if (seek_upper) {
	       /* Get the accuracy of the split made according to the current candidate boundary, assuming a "less than" split */
	       /* We are searching for a local maximum in accuracy score (i.e. higher than previous split and next split) */
	       /* If we find one, good_upper_bounds (a.k.a. gu_ptr) stores the candidate boundary */
	       l_ranks[2] = dist_eval_rank(l_distribution, l_weight);
	       if (l_ranks[1] >= l_ranks[0] &&
		   l_ranks[1] > l_ranks[2] && i > 0){
		    gu_ptr->bound = previous_bound;
		    (gu_ptr++)->score = l_ranks[1];
	       }
	       
	       l_ranks[0] = l_ranks[1];
	       l_ranks[1] = l_ranks[2];
	  }
	  previous_bound = bound;
     }

     /* Check if the final value was maximal... */
     if (seek_lower && h_ranks[1] > h_ranks[0]){
	  gl_ptr->bound= previous_bound;
	  (gl_ptr++)->score = h_ranks[1];
     }
     if (seek_upper && l_ranks[1] > l_ranks[0]){
	  gu_ptr->bound = previous_bound;
	  (gu_ptr++)->score = l_ranks[1];	  
     }

     /* If there are lots of good bounds, then sort them, so that  */
     /* we can go on to pick the best.  Otherwise there's no need, */
     /* as we'll be using them all anyway.                         */
     /* Sort according to accuracy heuristic */
     
     if (seek_lower && (n = gl_ptr - good_lower_bounds) > max_bounds)
       qsort(good_lower_bounds, n, sizeof(SOA_pair), SOA_compare);
     
     if (seek_upper && (n = gu_ptr - good_upper_bounds) > max_bounds)
       qsort(good_upper_bounds, n, sizeof(SOA_pair), SOA_compare);

	 
     /* Pick the best of the bounds, create the corresponding */
     /* specialised nodes, and throw them on the heap         */

     /* Create a new condition for each of the candidate "greater than" boundaries (up to a specified maximum), and add them to star */

     for (i = 0, ptr = good_lower_bounds; i < max_bounds && ptr < gl_ptr;
	  ++ptr, ++i){

	  lower_node = new_node();
	  copy_selector(lower_node, node);

	  if (! (discl = lower_node->selector[att_no].discriminant))
	     discl = lower_node->selector[att_no].discriminant =
	       new_discriminant(attribute);
	  
	  discl->bounds->lower = ptr->bound;
	  discl->bounds->instantiation = (instant | LOWER_BOUND);	  

	  if (UPPER_BOUND_SET_P(instant))
	    lower_node->selector[att_no].setp = TOTAL_INSTANTIATION;
	  else
	    lower_node->selector[att_no].setp = INSTANTIATION;
	  if (filter_ordered_examples(lower_node, node, att_no,
				      ptr->bound, GREATER_THAN))
	    assess(lower_node);
	  else
	    free_node(lower_node);
     }

     /* Create a new condition for each of the candidate "less than" boundaries (up to a specified maximum), and add them to star */

     for (i = 0, ptr = good_upper_bounds; i < max_bounds && ptr < gu_ptr;
	  ++ptr, ++i){

	  lower_node = new_node();
	  copy_selector(lower_node, node);

	  if (! (discl = lower_node->selector[att_no].discriminant))
	     discl = lower_node->selector[att_no].discriminant =
	       new_discriminant(attribute);
	  
	  discl->bounds->upper = ptr->bound;
	  discl->bounds->instantiation = (instant | UPPER_BOUND);
	  if (LOWER_BOUND_SET_P(instant))
	    lower_node->selector[att_no].setp = TOTAL_INSTANTIATION;
	  else
	    lower_node->selector[att_no].setp = INSTANTIATION; 
	  if (filter_ordered_examples(lower_node, node, att_no,
				      ptr->bound, LESS_THAN))
	    assess(lower_node);
	  else
	    free_node(lower_node);
     }

     FREE(epitome);
     FREE(h_distribution);
     FREE(l_distribution);
     FREE(good_upper_bounds);
     FREE(good_lower_bounds);
     
     return(1);
}



copy_selector(node2, node)
Node *node2, *node;
{
     register int i;
     register Attribute *att;
     register Selector *selector1 = node->selector;
     register Selector *selector2 = node2->selector;     
     
     for (i=0; i < number_of_attributes; ++i, ++selector1, ++selector2){
	  if (! INSTANTIATED(selector1->setp))
	    continue;
	  switch (ATT_TYPE(att = nth_attribute(i))){
	  case DISCRETE_TYPE:
	       if (!selector2->discriminant)
		 selector2->discriminant = new_discriminant(att);
	       selector2->discriminant->attval =
		 selector1->discriminant->attval;
	       break;
	  case ORDERED_TYPE:
	       if (!selector2->discriminant)
		 selector2->discriminant = new_discriminant(att);   
	       if (LOWER_BOUND_SET_P(selector1->discriminant->
				     bounds->instantiation))
		    selector2->discriminant->bounds->lower =
		      selector1->discriminant->bounds->lower;
	       if (UPPER_BOUND_SET_P(selector1->discriminant->
				     bounds->instantiation))
		    selector2->discriminant->bounds->upper =
		      selector1->discriminant->bounds->upper;
	       selector2->discriminant->bounds->instantiation =
		      selector1->discriminant->bounds->instantiation;
	       break;
	  }
	  selector2->setp = selector1->setp;
     }
}

/*  Filter examples from node to lower_node according 
    to attribute test.  Return TRUE if some examples are
    rejected, FALSE if they all pass.
       Don't Cares can be expanded immediately (just divide weight
    by number of attvals).  Unknowns are placed in a separate list
    as they are encountered, until all the examples have been processed,
    and the frequency of occurrence of the chosen att_val has been
    determined.  The unknowns are then moved across to lower_node's
    example list, their weights being reduced according to the
    above frequency.
                                                           */
BOOL filter_discrete_examples(lower_node, node, att_no, att_val)
Node *lower_node, *node;
int att_no;
Discrete att_val;
{
     EList elist, new_example;
     EList *e_ptr, *u_ptr;
     register int i;
     register Quotquae *quotq, *quotql;
     BOOL change_flag = FALSE;
     Attribute *attribute = nth_attribute(att_no);
     int no_of_values = N_VALUES(attribute);
     EList unknowns = (EList)0;
     double unchosen_weight, chosen_weight, weight_ratio;
     Discrete dval;
     
     for (i = 0, quotq = node->quotquae, quotql = lower_node->quotquae;
	  i < number_of_classes;
	  ++i, ++quotq, ++ quotql){
	  
	  elist = quotq->quae;	  
	  e_ptr = &(quotql->quae);
	  u_ptr = &unknowns;
	  unchosen_weight = 0.0;
	  while (elist) {
	       dval = E_DDVAL(att_no, elist);
	       if (D_DC(dval)){
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += (new_example -> weight);
	       }
	       else if (D_UNK(dval)){
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight/ no_of_values;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += new_example -> weight/no_of_values;
               /*		    
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight;
		    new_example -> values = elist -> values;
		    (*u_ptr) = new_example;
		    u_ptr = &(new_example->next);   */
	       }
	       /* if there's a match between the current training example attribute value and the node/complex attribute test */
	       else if (dval == att_val) {
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += new_example -> weight;
	       }
	       else {
		    unchosen_weight += elist -> weight;
		    change_flag = TRUE;
	       }
	       elist = E_NEXT(elist);		    	       
	  }
	  (*u_ptr) = (EList)0;

	  if ((chosen_weight = quotql->quot) == 0.0 &&
	      unchosen_weight == 0)
	    weight_ratio = (1 / no_of_values);
	  else
	    weight_ratio = chosen_weight /
	      (chosen_weight + unchosen_weight);

	  while (unknowns){
	       unknowns -> weight = unknowns -> weight * weight_ratio;
	       (*e_ptr) = unknowns;
	       e_ptr = &(unknowns->next);	       
	       quotql->quot += unknowns -> weight;	       
	       unknowns = E_NEXT(unknowns);
	  }
	  (*e_ptr) = (EList)0;
     }

     /* Return TRUE if
	i) Some examples were filtered out;
	ii) There are some examples left;
	                                      */
     if (change_flag){
	  for (i=0, quotql = lower_node->quotquae;
	       i < number_of_classes;
	       ++i, ++quotql){
	       if (quotql->quot >= 1.0)
		 return(TRUE);
	  }
	  return(FALSE);
     }
     
     return(FALSE);
}     



BOOL filter_ordered_examples(lower_node, node, att_no, bound, inequality)
Node *lower_node, *node;
int att_no, inequality;
FLOAT bound;
{
     register EList elist;
     EList  new_example;     
     EList *e_ptr, *u_ptr;
     register int i;
     register Quotquae *quotq, *quotql;     
     BOOL change_flag = FALSE;
     double unchosen_weight, chosen_weight, weight_ratio;
     EList unknowns = (EList)0;
     register Ordered oval;

     for (i = 0, quotq = node->quotquae, quotql = lower_node->quotquae;
	  i < number_of_classes;
	  ++i, ++quotq, ++ quotql){
	  

	  elist = quotq->quae;	  
	  e_ptr = &(quotql->quae);
	  u_ptr = &unknowns;
	  unchosen_weight = 0.0;
	  while (elist) {
	       oval = E_OOVAL(att_no, elist);
	       if (O_DC(oval)){
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += new_example -> weight;
	       }
	       else if (O_UNK(oval)){
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight / 2;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += new_example -> weight / 2;
	       }
	       else if ((inequality == GREATER_THAN && oval > bound)
			||
			(inequality == LESS_THAN && oval < bound)) {
		    new_example = new_ecopy();
		    new_example -> weight = elist -> weight;
		    new_example -> values = elist -> values;
		    (*e_ptr) = new_example;
		    e_ptr = &(new_example->next);
		    quotql->quot += new_example -> weight;
	       }
	       else {
		    unchosen_weight += elist -> weight;
		    change_flag = TRUE;
	       }
	       elist = E_NEXT(elist);		    	       
	  }
	  (*u_ptr) = (EList)0;	  

	  if ((chosen_weight = quotql->quot) == 0.0 &&
	      unchosen_weight == 0)
	    weight_ratio = 0.5;  /* Two values - half in each */
	  else
	    weight_ratio = chosen_weight /
	      (chosen_weight + unchosen_weight);

	  while (unknowns){
	       unknowns -> weight = unknowns -> weight * weight_ratio;
	       (*e_ptr) = unknowns;
	       e_ptr = &(unknowns->next);	       
	       quotql->quot += unknowns -> weight;	       
	       unknowns = E_NEXT(unknowns);
	  }
	  (*e_ptr) = (EList)0;	  
     }

     /* Return TRUE if
	i) Some examples were filtered out;
	ii) There are some examples left;
	                                      */
     if (change_flag){
	  for (i=0, quotql = lower_node->quotquae;
	       i < number_of_classes;
	       ++i, ++quotql){
	       if (quotql->quot >= 1.0)
		 return(TRUE);
	  }
	  return(FALSE);
     }
     
     return(FALSE);
}     

/* The reason for the node_status variable is that the test for
   being better than default is most efficiently carried out at
   the same time as the rank is evaluated, but the result of the
   test is not used until later                                 */

/* To clarify poor documentation:
   Takes a node that has already been specialised. Evaluates whether the node is the best node found thus
   far, and stores it in global_best_node if this is the case. Then attempts to add the specialised
   complex to newstar, while maintaining the size of newstar (possibly removing the worst complex if
   newstar is already full). */

assess(node)
Node *node;
{
     Rank potential;
     int node_status;
     double significance;

   /* Insert the value of rank into the
      node structure, and record the result
      of other tests in node_status */
     
     node_status = evaluate_rank(node); 

     if (node_status == USELESS) {
	  free_node(node);
	  return(0);
     }
     
     /* The current node replaces the best node if it
	has a better rank, is statistically significant,
	gives a better rule than the default, and (only for un-ordered
	rules, and if max-class flag is set) if the max class count
	of examples covered is for the class predicted.  */

     /* To clarify poor documentation:
        better_rank checks whether the new node (complex) has a higher quality measure than the best node.
        significant_p checks whether the new node (complex) has a significance higher than the threshold.
        BETTER_THAN DEFAULT: Checks whether the new node (complex) is better (in terms of accuracy) than a
                             complex that predicts the most common class in the training set. This is done
                             by checking if the naive error estimate of the new complex is greater than
                             (number of examples of complex's predicted class in data set) / (total examples in data set).
        max_class_p is only relevant for unordered rules. */

     if (better_rank(node->rank, global_best_node->rank) &&
	 significant_p(node, &significance) &&
	 node_status == BETTER_THAN_DEFAULT &&
	 max_class_p(node)) {
     	       /* Here we should free the global best 
		  node if it's not on the heap.  */
	  global_best_node = node;
	  if (TRACE_BEST_UPDATE) {
	       fprintf(stdout, "New Best Node is\n");
	       print_node(stdout, global_best_node);
	       fprintf(stdout, "Significance: %.2f\n\n", significance);    
	  }
     }

     
     /* Only toss the current node onto the heap if it
	might turn into a winner.
	   If it falls off when you toss it on, and it isn't 
	global best, then zap it.                             */
     /* To clarify poor documentation: potential_rank and better_rank figure out if we've found a perfect complex yet.
        If we have, we don't need to add the newly specialised node. Very strange and inefficient way of doing this, I think. */
     /* To clarify poor documentation: The heap (actually star) is a priority queue. The node will not be added if the heap
        is full and it is the worst node. If the node is added and the heap is full, the worst node is removed. */

     potential_rank(node, &potential);
     if (better_rank(&potential, global_best_node->rank)) {
	  if ((! toss_onto_heap(HEAP_PTR, node)) &&
	      (node != global_best_node))
	    free_node(node);
     }

     else {
	  if (TRACE_USELESS) {
	       fprintf(stdout, "Dropping complex because its rank can never ");
	       fprintf(stdout, "reach the global best:\n");
	       print_selector(stdout, node->selector);
	  }
	  if (node != global_best_node)
	    free_node(node);
     }
     
     return(1);
}



int epitome_compare(ptr1, ptr2)
register Epitome *ptr1;
register Epitome *ptr2;
{
     if (ptr1->attval < ptr2->attval)
       return(-1);
     else if (ptr1->attval == ptr2->attval)
       return(0);
     else
       return(1);
}

/* We want items with high score values to go to the front */
int SOA_compare(ptr1, ptr2)
SOA_pair *ptr1;
SOA_pair *ptr2;
{
     if (ptr1->score < ptr2->score)
       return(1);
     else if (ptr1->score == ptr2->score)
       return(0);
     else
       return(-1);
}



BOOL equal_selector(selector1, selector2)
Selector *selector1, *selector2;
{
     int i;
     unsigned short ins;

     for (i=0; i < number_of_attributes; ++i){
	  if (selector1[i].setp != selector2[i].setp)
	    return(FALSE);
	  if (! INSTANTIATED(selector1[i].setp))
	    continue;
	  switch (ATT_TYPE(nth_attribute(i))){
	  case DISCRETE_TYPE:
	       if (selector1[i].discriminant->attval !=
		   selector2[i].discriminant->attval)
		 return(FALSE);
	       break;
	  case ORDERED_TYPE:
	       if ((ins = selector1[i].discriminant->bounds->instantiation) !=
		   selector2[i].discriminant->bounds->instantiation)
		 return(FALSE);
	       if (LOWER_BOUND_SET_P(ins))
		 if (selector1[i].discriminant->bounds->lower !=
		     selector2[i].discriminant->bounds->lower)
		   return(FALSE);
	       if (UPPER_BOUND_SET_P(ins))
		 if (selector1[i].discriminant->bounds->upper !=
		     selector2[i].discriminant->bounds->upper)
		   return(FALSE);
	       break;
	  }
     }
     return(TRUE);
}


