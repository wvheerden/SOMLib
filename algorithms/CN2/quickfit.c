/*  File:     quickfit.c
    Author:   Tim Niblett
    Purpose:  QUICKFIT allocator
    */

static char *SccsId = "@(#)quickfit.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include <stdlib.h>

/* Export declarations   */

extern void *qfalloc();
extern void qffree();
extern int qfcheck();



  /* ------------------ */

/* HOW TO USE:
 *
 *	You should set the following parameters:
 *	SYS_CHUNK:	should be at least QFMAX * 20-30
 *		determines the size of chunks grabbed from system
 *	ALLOC:
 *		says what the underlying allocator is.
 *	QFALIGN:
 *		the most stringent alignment type on your machine
 *	QFSIZE:
 *		the type of input to the underlying allocator -- should be 32 bit
 *	
 * DEBUGGING
 *
 *	Set the #define QF_STAT for statistics on the allocator behaviour
 *	Set the #define QF_CHECK for reasonably stringent checks.
 *	QF_CHECK will tell you (usually) if an unallocated block is 
 *	freed, and when a re-used block has been trashed.
 *	To find out whether some block has been trashed use
 *	qfcheck(address), this returns 0 if OK.
 *
 * ASSUMPTIONS AND BUGS
 *
 *	The allocator will work on most machines.  It assumes that
 *	general address arithmetic is availableon your machine. No checks
 *	are made for arithmetic overflow etc.
 */
#include <stdio.h>


/* The no. of buckets */
#define QFMAX	512	
#define HDR_SZ	1
#define SYS_CHUNK	((QFSIZE)2048)
#define NULL_CHECK 0
#define QF_MAGIC	(QFSIZE)10101

  /* ---------------------- */

  /* -----------------

#define QF_STAT
#define QF_CHECK

     -----------------  */

#define SUN4


#ifdef MAC
#define ALLOC(bytes)	((void *)NewPtr((QFSIZE)(bytes)))
typedef long int QFSIZE;
typedef short QFALIGN;
#endif

#ifdef SUN4
#define ALLOC(bytes)	((char *)malloc((unsigned)(bytes)))
typedef double QFALIGN;
typedef unsigned int QFSIZE;
#endif

#ifdef SUN_3
#define ALLOC(bytes)	((char *)malloc((QFSIZE)(bytes)))
typedef short QFALIGN;
typedef unsigned int QFSIZE;
#endif

/* The Header interface*/
#define NEXT(p)	((p) -> info.u.nxt)
#define SIZE(p)		((p) -> info.u.sz)

#ifdef QF_CHECK
#define CHECK(p)	((p) -> info.magic)
#define MAGIC(p)	( CHECK( p + SIZE( p )+1) )
#define NEXT_ALL(p)	( NEXT( p + SIZE( p ) + 1) )
#define A_NEXT_ALL(p)	( p + SIZE(p) + 1)
#endif

#ifdef QF_CHECK
#define EXTRA_BLOCKS		(HDR_SZ+HDR_SZ)
#else
#define EXTRA_BLOCKS		HDR_SZ
#endif

typedef union header {
     struct {
	  union {
	       union header *nxt;
	       QFSIZE sz;
	  } u;
#ifdef QF_CHECK
	  short magic;
#endif
     } info;
     QFALIGN dummy;
} Header;

/* According to the ANSII standard the initialisation is unnecessary (so ...) */
Header *qflist[QFMAX] = {
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

static Header  *heap = NULL, *misc = NULL;
static QFSIZE heapfree;

#ifdef QF_STAT
static QFSIZE	b_used = 0,
  b_free = 0,
  n_allocs = 0,
  n_miscs = 0,
  h_allocated = 0;
#endif

#ifdef QF_CHECK
static Header *first_block = NULL;
static Header **last_next_all = &first_block;
void qfcheckreuse();
void qfchecknew();
#endif

void *qfalloc(size)
QFSIZE size;
{
     register QFSIZE blocks = (size + sizeof(Header) - 1)/sizeof(Header);
     register Header *ptr, **mptr;
     void qf_free_heap();
     void qfverify();
     QFSIZE qfchecksum();

#ifdef QF_CHECK
     if ( size <= 0 ) {
	  fprintf(stderr, "QUICKFIT: bad size passed %ld\n", (long)size);
	  return(NULL);
     }
#endif

     if ( blocks < QFMAX ) {
	  if ( ptr = qflist[blocks] ) {
	       qflist[blocks] = NEXT(ptr);

#ifdef QF_STAT
	       b_used += blocks;
	       b_free -= blocks;
	       n_allocs++;
#endif

#ifdef QF_CHECK
	       qfcheckreuse(ptr-1, blocks);
#endif

	       return((void *)(ptr) );
	  } else {	/* No free list for blocks */
	       if ( heapfree >= blocks + EXTRA_BLOCKS ) {
		    ptr = heap;
		    SIZE(ptr) = blocks;

#ifdef QF_CHECK
		    qfchecknew(ptr, blocks);
#endif

		    heap += blocks + EXTRA_BLOCKS;
		    heapfree -= blocks + EXTRA_BLOCKS;

#ifdef QF_STAT
		    b_used += blocks;
		    n_allocs++;
#endif

		    return( (void *)(ptr+1) );
	       } else { /* Heap is exhausted */
		    qf_free_heap();
		    if ( !(heap = (Header *)ALLOC((QFSIZE)sizeof(Header)*SYS_CHUNK))  ) {

#ifdef QF_CHECK
			 fprintf(stderr, "QUICKFIT: Out of memory  (%lu requested)\n",
				 (unsigned long)((sizeof(Header)*SYS_CHUNK)) );
#endif

			 return((void *)NULL);
		    }

#ifdef QF_STAT
		    h_allocated += (QFSIZE)(SYS_CHUNK);
#endif

		    heapfree = SYS_CHUNK;
		    return( qfalloc(size) );
	       }
	  }
     }

     /* blocks >= QFMAX */
     for ( mptr = &misc; *mptr && SIZE(*mptr-1) < blocks; *mptr = NEXT(*mptr) );
     if ( *mptr && SIZE(*mptr-1) == blocks ) {
	  ptr = *mptr;

#ifdef QF_CHECK
	  qfcheckreuse(ptr-1, blocks);
#endif

#ifdef QF_STAT
	  b_used += blocks;
	  b_free -= blocks;
	  n_allocs++;
	  n_miscs++;
#endif

	  *mptr = NEXT(*mptr);
	  return( (void *)(ptr) );
     }

     /* No spare misc list */
     if ( !(ptr = (Header *)ALLOC((QFSIZE)(sizeof(Header)*(blocks+EXTRA_BLOCKS)))) )
       return((void *)NULL);
     SIZE(ptr) = blocks;
#ifdef QF_STAT
     b_used += blocks;
     h_allocated += (QFSIZE)((blocks+EXTRA_BLOCKS));
     n_allocs++;
     n_miscs++;
#endif

#ifdef QF_CHECK
     qfchecknew(ptr, blocks);
#endif

     return( (void *)(ptr + 1) );
}

void qf_free_heap()
{
     register QFSIZE n_blocks = heapfree;
     register Header *ptr = (Header *)heap;

     heapfree = 0;
     if (heap == NULL) return;
     if ( n_blocks <= EXTRA_BLOCKS ) return;
     if ( n_blocks >= QFMAX  ) {
	  fprintf(stderr, "QUICKFIT: serious bug -- mismatch in heapsize\n");
	  return;
     }

     SIZE(ptr) = n_blocks - EXTRA_BLOCKS;
     NEXT(ptr+1) = qflist[n_blocks - EXTRA_BLOCKS];
     qflist[n_blocks-EXTRA_BLOCKS] = ptr+1;
     heap = NULL;

#ifdef QF_CHECK
     qfchecknew(ptr, SIZE(ptr));
#endif

#ifdef QF_STAT
     b_free += (QFSIZE)(n_blocks-EXTRA_BLOCKS);
#endif

     return;
}

void qffree(addr)
register void *addr;
{
     register Header *haddr = (Header *) addr;

     register Header *head = haddr -1;
     register QFSIZE size;

#ifdef QF_CHECK
     qfverify(head);
     CHECK(head) = NULL_CHECK;
#endif

     /* Check for qflist member */
     if ( (size = SIZE(head)) < QFMAX ) {
	  NEXT(haddr) = qflist[size];
	  qflist[size] = haddr;
     } else {
	  /* Add to  misc free list (maybe pass back to sys alloc?) */
	  register Header **mptr;

	  for ( mptr = &misc;  *mptr && SIZE(*mptr-1) < size;  mptr = &NEXT(*mptr) );
	  NEXT(haddr) = *mptr;
	  *mptr = haddr;
     }

#ifdef QF_STAT
     b_free += (QFSIZE)size;
     b_used -= (QFSIZE)size;
#endif

}

#ifdef QF_STAT
void qfstats()
{
     printf("QUICKFIT: statistics\n\n");
     printf("total heap allocated:\t%lu\n", (unsigned long)(h_allocated*sizeof(Header)));
     printf("total heap free:\t\t%lu\n", (unsigned long)(heapfree*sizeof(Header)));
     printf("total blocks used:\t\t%lu\n", (unsigned long)(b_used*sizeof(Header)));
     printf("total blocks free:\t%lu\n", (unsigned long)(b_free*sizeof(Header)));
     printf("total no. allocations:\t%lu\n", (unsigned long)n_allocs);
     printf("total no. misc allocs:\t%lu\n", (unsigned long)n_miscs);
     printf("--------------\nWasted = %lu bytes (%f%%)\n",
	    (unsigned long)((h_allocated-heapfree-b_free-b_used)*sizeof(Header)),
	    100.0*((float)(h_allocated-heapfree-b_free-b_used))/((float)h_allocated) );

}
#else
void qfstats()
{
     printf("QUICKFIT: statistics unavailable\n");
}
#endif

#ifdef QF_CHECK
QFSIZE qfchecksum(size)
register QFSIZE size;
{
     return((QFSIZE)((unsigned long)size + (unsigned long)1989)); /* Change this every year */
}

void qfverify(head)
register Header *head;
{
     if ( CHECK(head) != qfchecksum(SIZE(head)) ) {
	  fprintf(stderr, "QUICKFIT: bad checksum (?freeing non-existent block?)\n");
	  exit(1);
     }
     if ( MAGIC(head) != QF_MAGIC ) {
	  fprintf(stderr, "QUICKFIT: trashed block (size %lu)\n", (unsigned long)SIZE(head));
     }
}

void qfcheckreuse(head, blocks)
Header *head;
QFSIZE blocks;
{
     if ( MAGIC( head ) != QF_MAGIC )
       fprintf(stderr, "QUICKFIT: Re-allocating trashed block\n");
     if ( SIZE(head)  != blocks )
       fprintf(stderr, "QUICKFIT: Wrong size in free block (?QUICKFIT bug?)\n");
     CHECK(head) = qfchecksum(blocks);
}

void qfchecknew(head, blocks)
Header *head;
QFSIZE blocks;
{
     CHECK(head) = qfchecksum(blocks);
     MAGIC(head) = QF_MAGIC;
     *last_next_all = A_NEXT_ALL(head);
     last_next_all = &(NEXT_ALL(head));
}
#endif

