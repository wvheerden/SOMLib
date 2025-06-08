/*  File:     create.c
    Author:   Robin Boswell
    Purpose:  Create new objects
*/ 

static char *SccsId = "@(#)create.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"
int nodecounter;


/* Create new star  */
Star new_star()
{
     Star star;
     int i;
     star = (Star) ALLOC(star_size * sizeof(Node *));     
     for (i=0; i < star_size; ++i)
       star[i] = (Node *)0;     
     return(star);
}



Quotquae *new_quotquae()
{
     Quotquae *quotquae;
     register Quotquae *q;
     register int i;
     
     q = quotquae = (Quotquae *) ALLOC(number_of_classes * sizeof(Quotquae));
     for (i=0; i < number_of_classes; ++i){
	  q->quot = (double) 0;
	  q->quae = (EList) 0;
	  ++q;
     }
     return(quotquae);
}

/* No longer assign new discriminants at this point */
Selector *new_selector()
{
     Selector *selector;
     register Selector *s;
     register int i;

     s = selector = (Selector *) ALLOC(number_of_attributes * sizeof(Selector));
     for (i=0; i < number_of_attributes; ++i) {
	  (*s).discriminant = (Discriminant *)0;
	  (*s++).setp = (unsigned short) 0;
     }
     return(selector);
}


Discriminant *new_discriminant(attribute)
Attribute *attribute;
{
     Discriminant *discriminant;
     discriminant = (Discriminant *) ALLOC(sizeof(Discriminant));

     switch ATT_TYPE(attribute){
     case DISCRETE_TYPE:
	  break;
     case ORDERED_TYPE:
	  discriminant->bounds = (Bounds *)ALLOC(sizeof(Bounds));	  
	  break;
     }

     return(discriminant);
}

     
Rank *new_rank()
{
     Rank *rank = (Rank *)ALLOC(sizeof(Rank));
     rank->primus = (FLOAT) -1;
     rank->secundus = (FLOAT) -1;
     return(rank);
}

     
/* Create new node */
Node *new_node()
{
     Node *node;

     node = (Node *) ALLOC(sizeof(Node));

     node->quotquae = new_quotquae();
     node->selector = new_selector();
     node->rank = new_rank();
#ifdef NODE_COUNT
     fprintf(stdout, "Creating Node %d!\n", nodecounter++);
#endif     
     
     return(node);
}

free_node(node)
Node *node;
{
     free_quotquae(node->quotquae);
     free_selector(node->selector);
     FREE(node->rank);
     FREE(node);
#ifdef NODE_COUNT
     fprintf(stdout, "Freed node  %d!\n", nodecounter--);
#endif     
     
}

free_node_not_exs(node)
Node *node;
{
     free_selector(node->selector);
     FREE(node->rank);
     FREE(node);
}


free_quotquae(quotquae)
Quotquae *quotquae;
{
     register int i;
     register Quotquae *q = quotquae;
       
     for (i=0; i < number_of_classes; ++i, ++q)
	  free_elist(q->quae);
     FREE(quotquae);
}

/*	  Now defined in example.c
free_elist(elist)
EList elist;
{
     EList temp;
     
     while (elist) {
	  temp = elist->next;
	  FREE(elist);
	  elist = temp;
     }
}              */

free_selector(selector)
Selector *selector;
{
     register int i;
     register Selector *s = selector;
     
     for (i=0 ; i < number_of_attributes; ++i, ++s)
       if (s->discriminant)
	 free_discriminant(s->discriminant, nth_attribute(i));
     FREE(selector);
}


free_discriminant(discriminant, attribute)
Discriminant *discriminant;
Attribute *attribute;
{
     switch ATT_TYPE(attribute){
     case DISCRETE_TYPE:
	  break;
     case ORDERED_TYPE:
	  FREE(discriminant->bounds);
	  break;
     }
     
     FREE(discriminant);
}


     
Star initial_star(classified_examples)
Quotquae *classified_examples;
{
     Star star;
     star = new_star();
     star[0] = new_node();
     star[0]->quotquae = classified_examples;
     evaluate_rank(star[0]);
     return(star);
}


Quotquae *classify_examples(example_list)
EList example_list;
{
     int class_number;
     Quotquae *quotquae;
     EList **e_ptr;
     int i;     

     quotquae =  new_quotquae();
     e_ptr = (EList **) ALLOC(number_of_classes * sizeof(EList *));

     for (i = 0; i < number_of_classes; ++i)
       e_ptr[i] = &(quotquae[i].quae);
     
     while (example_list) {
	  class_number = E_DVAL(IDclass, example_list); 
	  {
	       EList new_example = new_ecopy();
	       new_example -> weight = example_list -> weight;
	       new_example -> values = example_list -> values;
	       (*(e_ptr[class_number])) = new_example;
	       e_ptr[class_number] = &(new_example->next);
	  }
	  quotquae[class_number].quot += example_list -> weight;
	  example_list = E_NEXT(example_list);
     }
     for (i = 0; i < number_of_classes; ++i)
       *(e_ptr[i]) = (EList)0;
     FREE(e_ptr);
     return(quotquae);
}


/* Like scores in ID, except that we don't need an 'unclassified'
   column (because there is always a default, so everything gets
   classified).                                               */

double **new_cn_scores(n)
int n;
{
     int row, col;
     
     double **scores = (double **)ALLOC(n * sizeof(double *));

     for (row = 0; row < n; ++row){
	  scores[row] = (double *)ALLOC(n * sizeof(double));
	  for (col = 0; col < n; ++col)
	    scores[row][col] = 0.0;
     }
     return(scores);
}
