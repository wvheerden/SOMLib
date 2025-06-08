/*  File:     heap.c
    Author:   Claude Sammut, corrected and modified by RAB.
    Purpose:  Heaps

    Change Log:

      2/16/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Renamed function remove() to remove_item(), as "remove"
        conflicted with <stdio.h> definition on IRIX. Changed
        all references to reflect new name.
          Affected routines: remove()
                             free_heap()
                             heap_to_star()
                             toss_onto_heap() 
*/ 

static char *SccsId = "@(#)heap.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include <stdio.h>
#include "cn_externs.h"


void free_heap()
{
     Node *node;
     while (node = remove_item(HEAP_PTR))
       free_node(node);
}

	
/* To clarify poor documentation:
   This returns false if star is empty, otherwise it copies items from the priority queue to star and returns true. */  

BOOL heap_to_star(star)
Star star;
{
     Node *node;
     BOOL success = FALSE;
     
     int i;
     for (i=0; i<star_size; ++i){
	  if (node = remove_item(HEAP_PTR)) {
	       success = TRUE;
	       star[i] = node;
	  }
	  else
	    star[i] = (Node *)0;
     }
     return(success);
}


/* create an empty priority queue Q. */

pqueue *create_heap()
{
     int i;
     pqueue *Q = (pqueue *) ALLOC (sizeof(pqueue));
     Q -> item  = (Node **) ALLOC ((star_size + 1) * sizeof(Node *));
     for (i=0; i <= star_size; ++i)
       Q->item[i] = (Node *)0;
     Q -> last = 0;
     return(Q);
}

/* Determine if a priority queue is empty */
/*
int is_empty(Q)
pqueue *Q;
{
	return(Q -> last = 0);
}                                    */


/*
Adjust: Convert the semiheap H rooted at position root into a heap.
Recursively trickle the item at position root down to its proper
position by swapping it with its larger child (if the child is larger
than the item).  If (2 * root) > H.last then the item is at a leaf and
nothing needs to be done.
*/


adjust(H, root)
pqueue *H;
int root;
{
	int child;
	Node *temp;
 
	/* stop if root is leaf */

	if (2 * root > H -> last)
		return;

	/* child is the index of the left child of the root */

	child = 2 * root;

	/* child is the index of the larger child of the root */

	if (child + 1 <= H -> last)
	        if (leq_node(H -> item[child + 1], H -> item[child]))
			child++;

	/* swap if the item at position root is smaller than the */
	/* larger child */

	if (leq_node(H -> item[child], H -> item[root]))
	{
		temp = H -> item[root];
		H -> item[root] = H -> item[child];
		H -> item[child] = temp;

		/* adjust the new subtree */

		adjust(H, child);
	}
}


/*
Remove_item: Delete and retrieve from priority queue Q the item with the
smallest priority value. The operation fails if the prority queue is
empty.  The returned value indicates whether the operation succeeded.
Swap the last item in the heap to the root and call adjust to trickle
it down to its proper position.
*/

Node *remove_item(Q)
pqueue *Q;
{
        Node *node;
	
	if (Q -> last == 0)
		return((Node *)0);

	node = Q -> item[1];
	Q -> item[1] = Q -> item[Q -> last];
	(Q -> last)--;
	adjust(Q, 1);
	return(node);
}


/*
Insert newitem into priority queue Q. The operation fails if the
priority queue is full (contains maxqueue items). The flag success
indicates the operation succeeded.  Insert the new item after the last
item in the heap and trickle it up to its proper position.

Modified so that if queue is full, we look to see if the
new item is better than the worst item, and if it is, remove the
worst item and add the new item.  RAB.
*/

/* To clarify poor documentation:
   Adds a new condition to newstar. If newstar is full, remove the worst condition from star. Here, worst
   is defined as  */

int toss_onto_heap(Q, new_node)
pqueue *Q;
Node *new_node;
{
	int parent, place;
	Node *temp, *worst_node;
	int i;

	/* If the new node has an identical selector to one already
	   on the heap, do nothing and return 0.
	   Need only test nodes with equal rank.                 */
	for (i=0; i<= star_size; ++i){
	     if (Q->item[i]) {
		  if (new_node->rank->primus ==
		      Q->item[i]->rank->primus) {
		       if (equal_selector(new_node->selector,
					  Q->item[i]->selector)) {
			    return(0);
			}
		  }
	     }
	}
	
	/* If newstar is full */
	if (Q -> last == star_size){
	     /* Find the worst node in newstar */
	     worst_node = Q->item[1];
	     /* If the new node is better (has a higher quality measure) than the worst node, remove the
                worst node (if the best node thus far is removed, it still remains the best node found
                thus far) */
	     if (better_node(new_node, worst_node)){
		  remove_item(Q);
		  if (worst_node != global_best_node) /* Maybe the better nodes */
		    free_node(worst_node);            /* aren't significant     */
	     }
	     else
	       return(0);
	}

	/* place the new item at the end of the heap (newstar) */
	Q -> item[++(Q -> last)] = new_node;

	/* trickle it up to its proper position. */
	/* Then make sure that newstar is sorted again. */
	place = Q -> last;

	for (parent = place/2; parent > 0; parent = place/2)
	{
	        if (worse_node(Q->item[parent], Q -> item[place]))
		    break;

		temp = Q -> item[parent];
		Q -> item[parent] = Q -> item[place];
		Q -> item[place] = temp;
		place = parent;
	}
	return(1);
}

	     
void print_queue(Q)
pqueue *Q;
{
     int i;

     for (i=1; i <= Q->last; ++i){
	  fprintf(stdout, "%d: %.2f\n", i, Q->item[i]->rank->primus);
     }
}

	  
	  
