/*  File:     cn_header.h
    Author:   Robin Boswell
    Purpose:  Structures and Types for CN2

    Change Log:

      3/20/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Syntax (minor): added semicolon to declaration of "distribution"
          member of Rule structure.
*/

       /* SccsId = "@(#)cn_header.h 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989" */

#include  "mlt_float.h"

#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* -------------------------------- */

/* Type definitions: These should be altered on a 
 * machine-by machine basis
 */
typedef short SHORT;
typedef unsigned short USHORT;
typedef long int INT;
typedef unsigned long int UINT;
typedef long int LONG;
typedef unsigned long int ULONG;
typedef float FLOAT;
typedef double DOUBLE;
typedef int BOOL;
typedef int BOOLEAN;
#ifdef MAC
typedef short AlignmentType;
#endif
#define LOG_MAX 128

/* -------------------------------- */

typedef	float		Ordered;
typedef	long int	Discrete;
typedef	long int	Id;  /* Identifier for examples */
typedef	struct {
     Ordered o;
     Discrete d;
} Value;


#define UK_STRING  "Unknown"
#define UK_INT     (-1)
#define DC_INT     (-2)
#define UK_FLOAT   (FLT_MAX)       /* Was (0xFFFFFFFF) */
#define DC_FLOAT   (- FLT_MAX)    /* Was (0xFFFFFFFE) */
typedef	char	Type;


#define ORDERED_TYPE	'o'
#define DISCRETE_TYPE	'd'
#define ATOM_TYPE	'a'
#define LIST_TYPE	'l'
#define ATTRIBUTE_TYPE	'A'  /* Maybe */
#define EXAMPLE_TYPE	'e'  /* Maybe */
#define SPLODGE_TYPE 	's'  /* Maybe */
#define INT_TYPE 	'i'  /* Maybe */


/* -------------------------------- */

typedef struct Atom
{
     Type  type;
     char *name;
     struct Atom *link;
     struct Atom *next_value;
} Atom;

/* -------------------------------- */
/*          LISTS                   */


/* Objects */

typedef struct {
     Type	otype;
     void *value;						
} Object;

/*  Structure */

typedef struct ListCell {
     Object *head;
     struct ListCell *tail;
} ListCell;

typedef ListCell *List;

/*  Access functions */

#define HEAD(list)	(list -> head)
#define TAIL(list)	(list -> tail)
#define HEADVAL(list)	(list -> head.value)
#define TYPE(obj)	(obj -> otype)


     
/* -------------------------------- */


/*    Attributes  */
    /* Interface */

#define N_VALUES(att)	((att) -> n_values)
#define A_VALUES(att)	((att) -> avalues)
#define PREREQUS(att)   ((att) -> prerequs)
#define ATT_NO(att)	((att) -> index)
#define ATT_TYPE(att)	((att) -> atype)
#define ATT_NTYPE(att)	((att) -> ntype)
#define BIN_ACT(att)    ((att) -> bin_action) 
#define D_DC(attval)    ((attval == DC_INT))
#define D_UNK(attval)   ((attval == UK_INT))

#define O_DC(attval)    ((attval < DC_FLOAT/10))
#define O_UNK(attval)   ((attval > UK_FLOAT/10 ))

typedef enum {
     TWOWAY = 0,
     MULTIPLE = 1,
     DEFAULT = 2
  } binary_action;

typedef enum {
     INTEGRAL = 0,
     REAL = 1
  } numeric_type;

/* Structure */

typedef struct Attribute {
     Atom	*aname;
     Type	atype;     
     numeric_type ntype;
     int	n_values;
     int	index;     
     int        *prerequs;
     List	avalues;
     binary_action bin_action;
} Attribute;

/* -------------------------------- */

/* Examples and example-lists */
   /*   Structure */

typedef struct {
     Type  etype;
     Id	   id;
     Value *values;
     void  *clientdata;
} Example;


struct EListElement {
     double weight;
     Value *values;
     struct EListElement *next;
};


typedef struct EListElement *EList;

     
/* Access */
#define E_VAL(att, ex)	((ex) -> values[ATT_NO(att)])
#define E_OVAL(att, ex)	((ex) -> values[ATT_NO(att)].o)
#define E_DVAL(att, ex)	((ex) -> values[ATT_NO(att)].d)
#define E_VALUES(ex)    ((ex) -> values)

#define E_DDVAL(attno, ex)	((ex) -> values[attno].d)
#define E_OOVAL(attno, ex)	((ex) -> values[attno].o)
#define E_NEXT(ex)              ((ex) -> next)
#define E_WEIGHT(ex)            ((ex) -> weight)
#define E_EMPTY(ex)             (!(ex))



/* Record of attribute uses */
typedef struct {
     int att_index;
     union {
	  List list;   /* List of values included in current branch */
	  Discrete d;  
     } uses;
} Splodge;



typedef enum {
     ATTRIBUTES_AND_EXAMPLES = 0,      
     ATTRIBUTES = 1,     
     EXAMPLES = 2,
     TREE = 3,
     RULES = 4,     
     ERROR = 5
  } InputType;


/* ------------------------------- */
/*       CN specific stuff         */



/* secundus is not currently used. */
typedef struct {
     FLOAT primus;
     FLOAT secundus;
} Rank;

/* In the program these structures are generally formed into arrays, and
   hold example-lists, divided into classes, together with counts of the
   number in each class (strictly, the total weight).
   Thus, in terms of the yyy example:
        Quotquae *foo;
	foo[0].quot = e.g. the number of mammals
	foo[0].quae is an example list full of mammals       */

typedef struct {
     double quot;
     EList quae;
} Quotquae;

#define LOWER_BOUND 01
#define UPPER_BOUND 02
#define DOUBLE_BOUND 03
#define LOWER_BOUND_SET_P(i) ((i) & LOWER_BOUND)
#define UPPER_BOUND_SET_P(i) ((i) & UPPER_BOUND)
#define BOTH_BOUNDS_SET_P(i) ((i) & DOUBLE_BOUND)

/* Bounds indicate the instantiation of numeric attributes in selectors */
typedef struct {
     unsigned short instantiation;
     FLOAT lower;
     FLOAT upper;
} Bounds;

/* Discriminant indicates the instantiation of an attribute - for a
   discrete att, we just set attval, for a numeric att, we use the Bounds
   structure.        */
typedef union {
     int attval;
     Bounds *bounds;
} Discriminant;

#define INSTANTIATION   01
#define TOTAL_INSTANTIATION     03
#define INSTANTIATED(i) ((i) & INSTANTIATION)
#define TOTALLY_INSTANTIATED(i)   ((i) == TOTAL_INSTANTIATION)

/* setp indicates the degree of instantiation of the attribute;
   if it is totally instantiated, then don't bother to try to specialise
   it further (and if it isn't instantiated at all, then take the
   appropriate action when pretty-printing the selector).    */
   
typedef struct {
     unsigned short setp;
     Discriminant *discriminant;
} Selector;

typedef struct {
     Selector *selector;
     int      class;
     double   *distribution;
} Rule;


typedef struct {
     Rank *rank;
     Quotquae *quotquae;
     Selector *selector;
} Node;


typedef Node **Star;

typedef struct {
     float attval;
     int class;
     double weight;
} Epitome;

typedef struct {
     float bound;
     double score;
} SOA_pair;
     


/* ------------------------------- */
/*     Memory allocation macros    */


#include "qlalloc.h"
/*
#define ALLOC(p) qfalloc((unsigned)p)
#define FREE(p)  qffree(p)                   
                                         */

#define ALLOC(p) malloc((unsigned)p)
#define FREE(p)  free(p)              

/*
#define ALLOC(p) raballoc((unsigned)p)
#define FREE(p)  free(p)                 */

/* DataFlow is used to keep track of what we have loaded and where
   it came from (currently the file-name strings aren't used, but
   they probably should be sooner or later).                    */

typedef struct {
     char *example_file;
     char *attribute_file;
     unsigned short status;
} DataFlow;


typedef enum {
     LAPLACIAN = 0,
     NAIVE = 1,
     ENTROPY = 2,
     ENTROPY2 = 3
  } Ranking;

#define ENTROPIC(x) ((x) == ENTROPY || (x) == ENTROPY2)

typedef struct {
     char *example_file;
     char *time_stamp;
     unsigned short algorithm;
     Ranking errest;     
     float threshold;
     int star_size;
} RuleParams;

#define D_ATTRIBUTES  (01)
#define D_EXAMPLES    (02)
#define D_BOTH        (03)
#define D_RULES       (010)

#define DATA_BOTH       ((D_BOTH & data_flow.status) == D_BOTH)
#define DATA_EXAMPLES   (D_EXAMPLES & data_flow.status)
#define DATA_ATTRIBUTES (D_ATTRIBUTES & data_flow.status)
#define DATA_RULES       (D_RULES & data_flow.status)


/* Heaps */

typedef struct
{
     Node **item;
     int last;
} pqueue;


/* Flags for controlling tracing info etc.  */
#define T_NONE           (00)
#define T_PRINT_STAR     (01)
#define T_BEST_UPDATE    (02)
#define T_CURRENT_NODE   (04)
#define T_RULE          (010)
#define T_USELESS       (020)
#define T_CLASS         (040)
#define T_DOTS         (0100)
#define T_ALL          (0177)

#define TRACE_PRINT_STAR   (trace_flag & T_PRINT_STAR)
#define TRACE_BEST_UPDATE  (trace_flag & T_BEST_UPDATE)
#define TRACE_CURRENT_NODE (trace_flag & T_CURRENT_NODE)
#define TRACE_RULE     (trace_flag & T_RULE)
#define TRACE_USELESS  (trace_flag & T_USELESS)
#define TRACE_CLASS    (trace_flag & T_CLASS)
#define TRACE_DOTS     (trace_flag & T_DOTS)


#define A_ORDERED    (01)
#define A_UNORDERED  (0)
#define ORDERED      (algorithm_flag & A_ORDERED)


#define DEFAULT_STAR_SIZE (5)
#define DEFAULT_THRESHOLD (0.0)
#define DEFAULT_TRACING    ( T_RULE | T_CLASS | T_DOTS)
#define DEFAULT_ALGORITHM   A_UNORDERED
#define DEFAULT_MAX_CLASS  (0)
#define DEFAULT_ERREST      LAPLACIAN

#define USELESS             (0)
#define WORSE_THAN_DEFAULT  (1)
#define BETTER_THAN_DEFAULT (2)

#define COMMENT_CHAR        (35) /* # */


#define HUMAN (0)
#define MACHINE (1)

/* Used in execute.c and cn.c */
#define NO_COVERING       (0)
#define PARTIAL_COVERING  (1)
#define TOTAL_COVERING    (2)
#define UNKNOWN_COVERING  (3)


#define nth_attribute(i) (attribute_array[i])

typedef enum {
     CKRL = 0,
     CN2  = 1
  } Language;

