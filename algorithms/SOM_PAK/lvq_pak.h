/************************************************************************
 *                                                                      *
 *  Program packages 'lvq_pak' and 'som_pak' :                          *
 *                                                                      *
 *  lvq_pak.h                                                           *
 *  -definitions needed in programs                                     *
 *                                                                      *
 *  Version 3.2                                                         *
 *  Date: 21 Aug 1995                                                   *
 *                                                                      *
 *  NOTE: This program package is copyrighted in the sense that it      *
 *  may be used for scientific purposes. The package as a whole, or     *
 *  parts thereof, cannot be included or used in any commercial         *
 *  application without written permission granted by its producents.   *
 *  No programs contained in this package may be copied for commercial  *
 *  distribution.                                                       *
 *                                                                      *
 *  All comments  concerning this program package may be sent to the    *
 *  e-mail address 'lvq@cochlea.hut.fi'.                                *
 *                                                                      *
 ************************************************************************/
#ifndef LVQ_PAK_H
#define LVQ_PAK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "config.h"
#ifndef NO_BACKGROUND_SNAP
#include <sys/wait.h>
#include <sys/types.h>
#endif /* NO_BACKGROUND_SNAP */

/* parameters */
#define ALWAYS 1								/* required */
#define OPTION 0								/* optional */
#define OPTION2 2								/* optional, doesn't require an argument */

#define IN_DATA_FILE            "-din"
#define IN_VALIDATION_FILE      "-vin"          // added
#define OUT_DATA_FILE           "-dout"
#define IN_CODE_FILE            "-cin"
#define OUT_CODE_FILE           "-cout"
#define NUMBER_OF_CODES         "-noc"
#define RUNNING_LENGTH          "-rlen"
#define TRAINING_ALPHA          "-lrate"        // changed
#define ALPHA_DECAY             "-lratedecay"   // added
#define TRAINING_EPSILON        "-epsilon"
#define TRAINING_RADIUS         "-radius"
#define TRAINING_RADIUS_DECAY   "-radiusdecay"  // added
#define QUANTISATION_ERROR_TYPE "-qetype"       // added
#define WINDOW_WIDTH            "-win"
#define KNN_NEIGHBORS           "-knn"
#define LABEL                   "-label"
#define OUT_CLASSIFICATION_FILE "-cfout"
#define VERBOSE                 "-v"
#define RANDOM                  "-rand"
#define SILENT                  "-silent"
#define XDIM                    "-xdim"
#define YDIM                    "-ydim"
#define TOPOLOGY                "-topol"
#define NEIGHBORHOOD            "-neigh"
#define PLANE                   "-plane"
#define FIXPOINTS      	        "-fixed"
#define WEIGHTS                 "-weights"

enum boolean {FALSE, TRUE};

double currentVectorWeightChange;

struct fixpoint
{
	short xfix;
	short yfix;
};

/* every entry (either input data or code vector) is stored
   in linked lists consisting of following objects */
/* also used to store principal eigenvectors (in fact, seems to be used as a general vector structure) */

struct data_entry
{
	double *points;
	/* index to label data base */
	union
	{
		int *label_array;
		int label;
	}
	lab;
	short num_labs;
	short weight;
	/* pointer to next entry in list */
	struct data_entry *next;
	char *mask;										/* if mask is present, ignore vector components marked
																   with nonzero */
	struct fixpoint *fixed;
};

struct entries
{
	short dimension;							/* dimension of the entry */
	short topol;									/* topology type */
	short neigh;									/* neighbourhood */
	short xdim, ydim;							/* dimensions of the map */
	struct data_entry *current;		/* current entry */
	struct data_entry *entries;		/* pointer to entries */
	long num_loaded;							/* number of lines loaded in entries list */
	long num_entries;							/* number of entries in the data set if known */
	struct
	{
		unsigned int loadmode:1;		/* read whole file into memory or read entries
																   from file when needed */
		unsigned int totlen_known:1;	/* true when total length of file is
																	   known */
		unsigned int random_order:1;	/* use data vectors in random order.
																	   only available in LOADMODE_ALL */
		unsigned int skip_empty:1;	/* Ignore vectors that have all components
																   masked off (default) */
		unsigned int labels_needed:1;	/* Set if labels are required */
	}
	flags;
	int lap;											/* how many times have all samples been used */
	struct file_info *fi;					/* file info for file if needed */
	long buffer;									/* how many lines to read from file at one time */
	void *userdata;
};

#define labels_needed(codes) ((codes)->flags.labels_needed = 1)

/* structure used to get information about the winning entries. Also
   with k-nns */

struct winner_info
{
	long index;
	struct data_entry *winner;
	double diff;
};

/* adaptation function type */

struct teach_params;

/* function type for adapting a neighboruhood */
typedef void NEIGH_ADAPT (struct teach_params *teach,
													struct data_entry *sample,
													int bx, int by, double radius, double alpha);

/* function type for adapting a vector. */
typedef void VECTOR_ADAPT (struct data_entry *c, struct data_entry *s,
													 int d, double a);

/* function to return the distance between two units on the 2D map */
typedef double MAPDIST_FUNCTION (int bx, int by, int tx, int ty);

/* general distance between two vectors */
typedef double DIST_FUNCTION (struct data_entry *v1, struct data_entry *v2,
														 int dim);

typedef int WINNER_FUNCTION (struct entries *codes, struct data_entry *sample,
														 struct winner_info *w, int knn);

//typedef double ALPHA_FUNC (long iter, double alpha);  removed due to adaptive stopping condition

struct snapshot_info
{
	long interval;								/* save codebook every 'interval' iterations */
	char *filename;								/* filename of snapshot file */
	int type;											/* type of action */
	int flags;
	struct file_info *fi;
#ifndef NO_BACKGROUND_SNAP
	pid_t pid;
#endif
	int counter;
	void *data;
};


/* Snapshot types. Not actually used right now because first two are
   determined from the filename and the last one is not yet
   implemented */

#define SNAPSHOT_SAVEFILE 1			/* Save codebook in file */
#define SNAPSHOT_EXEC_CMD 2			/* Pipe codebook file to a command. Filename
																   is the command line to execute. */
#ifndef NO_BACKGROUND_SNAP
#define SNAPSHOT_ASYNC 3				/* same as above but fork a new process
																   before saving */
#endif
#define SNAPSHOT_KEEPOPEN 4			/* save all snapshots consecutively in one file */
#define SNAPSHOT_ASYNC_NOWAIT 5	/* when starting a new backround snap don't
																   wait for the previous one to complete */

#define SNAPFLAG_KEEPOPEN 1

#ifndef NO_BACKGROUND_SNAP
#define SNAPFLAG_BACKGROUND 2		/* save file on background */
#define SNAPFLAG_NOWAIT 4				/* do not wait for previous save to complete */
#endif

struct teach_params
{
	short topol;
	short neigh;
	//short alpha_type;         removed due to adaptive stopping condition
	MAPDIST_FUNCTION *mapdist;		/* calculates distance between two units */
	DIST_FUNCTION *dist;					/* calculates distance between two vectors */
	NEIGH_ADAPT *neigh_adapt;			/* adapts weights */
	VECTOR_ADAPT *vector_adapt;		/* adapt one vector */
	WINNER_FUNCTION *winner;			/* function to find winner */
	//ALPHA_FUNC *alpha_func;   removed due to adaptive stopping condition
	double radius;									/* initial radius (for SOM) */
  double radiusDecay;          // added
  int qmode;                  // added
	double alpha;									/* initial alpha value */
  double alphaDecay;           // added
	long length;									/* length of training */
	int knn;											/* nearest neighbours */
	struct entries *codes;
	struct entries *data_training;
  struct entries *data_training_error;
  struct entries *data_validation_error;
	struct snapshot_info *snapshot;
	time_t start_time, end_time;
};

#define LOADMODE_ALL    0
#define LOADMODE_BUFFER 1

/* topology types */
#define TOPOL_UNKNOWN 0
#define TOPOL_DATA    1
#define TOPOL_LVQ     2
#define TOPOL_HEXA    3
#define TOPOL_RECT    4

/* neighborhood types */
#define NEIGH_UNKNOWN  0
#define NEIGH_BUBBLE   1
#define NEIGH_GAUSSIAN 2

/* alpha function types */
#define ALPHA_UNKNOWN 0
//#define ALPHA_LINEAR 1    removed due to adaptive stopping condition
//#define ALPHA_INVERSE_T 2

struct typelist
{
	int id;												/* numeric id */
	char *str;
	void *data;										/* data pointer */
};

extern struct typelist alpha_list[];

struct entry_ptr
{
	struct data_entry *current;
	struct entries *parent;
	long index;
};

typedef struct entry_ptr eptr;
extern int lvq_errno;

/* labels */
#include "labels.h"

WINNER_FUNCTION find_winner_euc, find_winner_knn;
DIST_FUNCTION vector_dist_euc;
VECTOR_ADAPT adapt_vector;

/* useful general routines */
void errormsg (char *msg);
void debugmsg (char *msg);
void *oalloc (unsigned int len);
void *orealloc (void *po, unsigned int len);
void ofree (void *ptr);
struct fixpoint *get_fixed (char *str);

void mprint (long rlen);
int verbose (int level);
int silent (int level);
extern int verbose_level;
#define ifverbose(lvl) if (verbose_level >= lvl)

void osrand (unsigned long seed);
void freerand();
long orand (unsigned long int range);
double orand_dbl ();
void init_random (long i);

char *ostrdup (char *str);

long oatoi (char *str, long def);
double oatof (char *str, double def);
char *extract_parameter (int argc, char **argv, char *param, int when);
int parameters_left (void);
int global_options (int argc, char **argv);


/* Saving snapshots */
int save_snapshot (struct teach_params *teach, long iter);
struct snapshot_info *get_snapshot (char *filename, long interval, int type);
void free_snapshot (struct snapshot_info *shot);


/* typelist searches */
struct typelist *get_type_by_id (struct typelist *types, int id);
struct typelist *get_type_by_str (struct typelist *types, char *str);

#define get_str_by_id(l,i) (get_type_by_id((l),(i))->str)
#define get_id_by_str(l,s) (get_type_by_str((l),(s))->id)
#define get_data_by_id(l,i) (get_type_by_id((l),(i))->data)
#define get_data_by_str(l,s) (get_type_by_str((l),(s))->data)

/* alpha functions */
//ALPHA_FUNC linear_alpha, inverse_t_alpha;   removed due to adaptive stopping condition

int print_lines (FILE * fp, char **);
#define printhelp() print_lines(stdout,usage)

char *get_version (void);
#endif /* LVQ_PAK_H */
