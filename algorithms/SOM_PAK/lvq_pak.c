/************************************************************************
 *                                                                      *
 *  Program packages 'lvq_pak' and 'som_pak' :                          *
 *                                                                      *
 *  lvq_pak.c                                                           *
 *   -very general routines needed in many places                       *
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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#ifndef NO_BACKGROUND_SNAP
#include <unistd.h>
#endif
#include <math.h>
#include <float.h>
#include <gsl/gsl_rng.h>
#include "lvq_pak.h"
#include "datafile.h"

/* find_winner_euc - finds the winning entry (1 nearest neighbour) in
   codebook using euclidean distance. Information about the winning
   entry is saved in the winner_info structure. Return 1 (the number
   of neighbours) when successful and 0 when winner could not be found
   (for example, all components of data vector have been masked off) */

int
find_winner_euc (struct entries *codes, struct data_entry *sample,
								 struct winner_info *win, int knn)
{
	struct data_entry *codetmp;
	int dim, i, masked;
	double diffsf, diff, difference;
	eptr p;

	dim = codes->dimension;
	win->index = -1;
	win->winner = NULL;
	win->diff = -1.0;

	/* Go through all code vectors */
	codetmp = rewind_entries (codes, &p);
	diffsf = DBL_MAX;

	while (codetmp != NULL) {
		difference = 0.0;
		masked = 0;

		/* Compute the distance between codebook and input entry */
		for (i = 0; i < dim; i++) {
			if ((sample->mask != NULL) && (sample->mask[i] != 0)) {
				masked++;
				continue;								/* ignore vector components that have 1 in mask */
			}
			diff = codetmp->points[i] - sample->points[i];
			difference += diff * diff;
			if (difference > diffsf)
				break;
		}

		if (masked == dim)
			return 0;									/* can't calculate winner, empty data vector */

		/* If distance is smaller than previous distances */
		if (difference < diffsf) {
			win->winner = codetmp;
			win->index = p.index;
			win->diff = difference;
			diffsf = difference;
		}

		codetmp = next_entry (&p);
	}

	if (win->index < 0)
		ifverbose (3)
			fprintf (stderr, "find_winner_euc: can't find winner\n");

	return 1;											/* number of neighbours */
}

int
find_winner_euc2 (struct entries *codes, struct data_entry *sample,
									struct winner_info *win, int knn)
{
	struct data_entry *codetmp;
	int dim, i;
	double diffsf, diff, difference, *s, *c;
	eptr p;

	if (sample->mask != NULL)
		return find_winner_euc (codes, sample, win, knn);

	dim = codes->dimension;
	win->index = -1;
	win->winner = NULL;
	win->diff = -1.0;

	/* Go through all code vectors */
	codetmp = rewind_entries (codes, &p);
	diffsf = DBL_MAX;

	while (codetmp != NULL) {
		difference = 0.0;

		/* Compute the distance between codebook and input entry */
		c = codetmp->points;
		s = sample->points;
		for (i = 0; i < dim; i++) {
			diff = *c++ - *s++;
			difference += diff * diff;
		}

		/* If distance is smaller than previous distances */
		if (difference < diffsf) {
			win->winner = codetmp;
			win->index = p.index;
			win->diff = difference;
			diffsf = difference;
		}

		codetmp = next_entry (&p);
	}

	if (win->index < 0)
		ifverbose (3)
			fprintf (stderr, "find_winner_euc: can't find winner\n");

	return 1;											/* number of neighbours */
}

/* find_winner_knn - finds the winning entrys (k nearest neighbours)
   in codebook using euclidean distance. Information about the winning
   entry is saved in the winner_info structures provided by the
   caller. Return k (the number of neighbours) when successful and 0
   when winner could not be found (for example, all components of data
   vector have been masked off) */

int
find_winner_knn (struct entries *codes, struct data_entry *sample,
								 struct winner_info *win, int knn)
{
	struct data_entry *codetmp;
	int dim, i, j, masked;
	double difference, diff;
	eptr p;

	if (knn == 1)									/* might be a little faster */
		return find_winner_euc (codes, sample, win, 1);

	dim = codes->dimension;

	for (i = 0; i < knn; i++) {
		win[i].index = -1;
		win[i].winner = NULL;
		win[i].diff = DBL_MAX;
	}
	/* Go through all code vectors */

	codetmp = rewind_entries (codes, &p);

	while (codetmp != NULL) {
		difference = 0.0;

		masked = 0;
		/* Compute the distance between codebook and input entry */
		for (i = 0; i < dim; i++) {
			/* pitaisiko ottaa huomioon myos codebookissa olevat?? */
			if ((sample->mask != NULL) && (sample->mask[i] != 0)) {
				masked++;
				continue;								/* ignore vector components that have 1 in mask */
			}
			diff = codetmp->points[i] - sample->points[i];
			difference += diff * diff;
			if (difference > win[knn - 1].diff)
				break;
		}

		if (masked == dim)
			return 0;

		/* If distance is smaller than previous distances */
		for (i = 0; (i < knn) && (difference > win[i].diff); i++);

		if (i < knn) {
			for (j = knn - 1; j > i; j--) {
				win[j].diff = win[j - 1].diff;
				win[j].index = win[j - 1].index;
				win[j].winner = win[j - 1].winner;
			}

			win[i].diff = difference;
			win[i].index = p.index;
			win[i].winner = codetmp;
		}

		codetmp = next_entry (&p);
	}

	if (win->index < 0)
		ifverbose (3)
			fprintf (stderr, "find_winner_knn: can't find winner\n");

	return knn;										/* number of neighbours */
}

int
find_winner_knn2 (struct entries *codes, struct data_entry *sample,
									struct winner_info *win, int knn)
{
	struct data_entry *codetmp;
	int dim, i, j;
	double difference, diff, *s, *c;
	eptr p;

	if (sample->mask != NULL)
		return find_winner_knn (codes, sample, win, knn);

	if (knn == 1)									/* might be a little faster */
		return find_winner_euc2 (codes, sample, win, 1);

	dim = codes->dimension;

	for (i = 0; i < knn; i++) {
		win[i].index = -1;
		win[i].winner = NULL;
		win[i].diff = DBL_MAX;
	}
	/* Go through all code vectors */

	codetmp = rewind_entries (codes, &p);

	while (codetmp != NULL) {
		difference = 0.0;

		/* Compute the distance between codebook and input entry */
		c = codetmp->points;
		s = sample->points;
		for (i = 0; i < dim; i++) {
			diff = *c++ - *s++;
			difference += diff * diff;
		}

		/* If distance is smaller than previous distances */
		for (i = 0; (i < knn) && (difference > win[i].diff); i++);

		if (i < knn) {
			for (j = knn - 1; j > i; j--) {
				win[j].diff = win[j - 1].diff;
				win[j].index = win[j - 1].index;
				win[j].winner = win[j - 1].winner;
			}

			win[i].diff = difference;
			win[i].index = p.index;
			win[i].winner = codetmp;
		}

		codetmp = next_entry (&p);
	}

	if (win->index < 0)
		ifverbose (3)
			fprintf (stderr, "find_winner_knn: can't find winner\n");

	return knn;										/* number of neighbours */
}

/* vector_dist_euc - compute distance between two vectors is euclidean
   metric. Returns < 0 if distance couldn't be calculated (all components
   were masked off */

double
vector_dist_euc (struct data_entry *v1, struct data_entry *v2, int dim)
{
	double diff, difference;
	int i, masked = 0;

	difference = 0.0;
	for (i = 0; i < dim; i++) {
		if (((v1->mask != NULL) && (v1->mask[i] != 0)) ||
				((v2->mask != NULL) && (v2->mask[i] != 0))) {
			masked++;
			/* ignore vector components that have 1 in mask */
		} else {
			diff = v1->points[i] - v2->points[i];
			difference += diff * diff;
		}
	}

	if (masked == dim)
		return -1;

	return sqrt (difference);
}

double
vector_dist_euc2 (struct data_entry *v1, struct data_entry *v2, int dim)
{
	double diff, difference, *x1, *x2;
	int i;

	if ((v1->mask != NULL) || (v2->mask != NULL))
		return vector_dist_euc (v1, v2, dim);

	difference = 0.0;
	for (x1 = v1->points, x2 = v2->points, i = 0; i < dim; i++) {
		diff = *x1++ - *x2++;
		difference += diff * diff;
	}

	return sqrt (difference);
}


/* adapt_vector - move a codebook vector towards another vector */

void
adapt_vector (struct data_entry *codetmp, struct data_entry *sample,
							int dim, double alpha)
{
	int i;

  currentVectorWeightChange = 0.0;

	for (i = 0; i < dim; i++) {
		if ((sample->mask != NULL) && (sample->mask[i] != 0)) {
			continue;									/* ignore vector components that have 1 in mask */
		} else {
      currentVectorWeightChange += pow(alpha * (sample->points[i] - codetmp->points[i]), 2.0);
			codetmp->points[i] += alpha * (sample->points[i] - codetmp->points[i]);
    }
  }
}

void
adapt_vector2 (struct data_entry *codetmp, struct data_entry *sample,
							 int dim, double alpha)
{
	int i;
	double *c, *s;

	if (sample->mask != NULL)
		adapt_vector (codetmp, sample, dim, alpha);

	c = codetmp->points;
	s = sample->points;
	for (i = 0; i < dim; i++, c++)
		*c += alpha * (*s++ - *c);
}

/*******************************************************************
 * Routines for general usage                                      *
 *******************************************************************/

/* package errors */

int lvq_errno;

void
errormsg (char *msg)
{
	fprintf (stderr, "%s\n", msg);
}

/* My own free routine */
void
ofree (void *data)
{
	if (data != NULL)
		free (data);
}

/* oalloc - my malloc allocation routine with some error checking. Not
   used much any more as it exits if an error occurs. */

void *
oalloc (unsigned int len)
{
	void *tmp;

	if ((tmp = malloc (len)) == NULL) {
		fprintf (stderr, "Can't allocate memory");
		exit (-1);
	}

	return (tmp);
}

/* orealloc - my realloc allocation routine with some error
   checking. Not used much any more as it exits if an error occurs. */

void *
orealloc (void *po, unsigned int len)
{
	void *tmp;

	if ((tmp = realloc (po, len)) == NULL) {
		fprintf (stderr, "Can't reallocate memory");
		exit (-1);
	}

	return (tmp);
}


/* Print dots indicating that a job is in progress */
void
mprint (long rlen)
{
#ifndef time_t
#define time_t long
#endif
	static time_t startt, prevt;
	time_t currt;
	static long totlen = 0;
	long t1, t2;
	int i;

	currt = time (NULL);

	if (!totlen) {
		totlen = rlen;
		startt = currt;
		fprintf (stderr, "               ");
		for (i = 0; i < 10; i++)
			fprintf (stderr, "------");
	}

	if (currt != prevt || !rlen) {
		t1 = currt - startt;
		if (rlen != totlen)
			t2 = (currt - startt) * (double) totlen / (totlen - rlen);
		else
			t2 = 0;
		if (t2 > 9999) {
			t1 /= 60;
			t2 /= 60;
			i = 0;
		} else
			i = 1;
		fprintf (stderr, "\r%4u/%4u %4s ", (int) t1, (int) t2,
						 i ? "sec." : "min.");
		if (totlen) {
			i = (int) (60 * (double) (totlen - rlen) / totlen);
			while (i--)
				fprintf (stderr, ".");
		}
		fflush (stderr);
		prevt = currt;
	}
	if (!rlen)
		totlen = 0;
}


//unsigned long int _seed = 0;
gsl_rng *generator = NULL;
#ifndef RND_MAX
#define RND_MAX 32767L
#endif

// modified in favour of GSL random number generation

void
osrand (unsigned long seed)
{
//_seed = seed;
  generator = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng_set (generator, seed);
}

void
freerand()
{
  if (generator != NULL) {
    gsl_rng_free (generator);
  }
}

// modified in favour of GSL random number generation
// returns value in range [0, range)
long
orand (unsigned long int range)
{
  return gsl_rng_uniform_int (generator, range) ;
	//return ((int) ((_seed = (_seed * 23) % 100000001) % RND_MAX));
}

double
orand_dbl ()
{
  return (double) gsl_rng_uniform (generator);
}

/* init_random - initialize own random number generator with seed.
   If seed is 0, uses current time as seed. */

void
init_random (long seed)
{
	if (!seed) {
		osrand (time (NULL));
	} else {
		osrand (seed);
  }
}

int verbose_level = 1;

int
verbose (int level)
{
	if (level >= 0) {
		verbose_level = level;
	}

	return (verbose_level);
}

int
silent (int level)
{
	static int silent_level = 0;

	if (level >= 0) {
		silent_level = level;
	}

	return (silent_level);
}

int
use_fixed (int level)
{
	static int fixed_level = 0;

	if (level >= 0) {
		fixed_level = level;
	}

	return (fixed_level);
}

int
use_weights (int level)
{
	static int weights_level = 0;

	if (level >= 0) {
		weights_level = level;
	}

	return (weights_level);
}

/* ostrdup - return a pointer to a duplicate of string str. If no memory
   for new string cannot be allocated, return NULL. */

char *
ostrdup (char *str)
{
	char *tmp;
	int len;

	/* allocate mem for duplicate */
	len = strlen (str);
	if (len < 0)
		return NULL;
	tmp = malloc (sizeof (char) * (len + 1));
	if (tmp == NULL) {
		fprintf (stderr, "ostrdup: Can't allocate mem.\n");
		perror ("ostrdup");
		return NULL;
	}

	/* copy string */
	strcpy (tmp, str);

	return (tmp);
}

/*******************************************************************
 * Routines to get the parameter values                            *
 *******************************************************************/

static int no_parameters = -1;

int
parameters_left (void)
{
	return (no_parameters);
}

long
oatoi (char *str, long def)
{
	if (str == (char *) NULL)
		return (def);
	else
		return (atol (str));
}

double
oatof (char *str, double def)
{
	if (str == (char *) NULL)
		return (def);
	else
		return ((double) atof (str));
}

char *
extract_parameter (int argc, char **argv, char *param, int when)
{
	int i = 0;

	if (no_parameters == -1)
		no_parameters = argc - 1;

	while ((i < argc) && (strcmp (param, argv[i]))) {
		i++;
	}

	if ((i <= argc - 1) && (when == OPTION2)) {
		no_parameters -= 1;
		return "";
	}

	if (i < argc - 1) {
		no_parameters -= 2;
		return (argv[i + 1]);
	} else {
		if (when == ALWAYS) {
			fprintf (stderr, "Can't find asked option %s\n", param);
			exit (-1);
		}
	}

	return ((char *) NULL);
}


/* global_options - handle some options that are common to all
   programs. Also read some environment variables. */

int
global_options (int argc, char **argv)
{
	char *s;

	/* set program name */
	setprogname (argv[0]);

#ifndef NO_PIPED_COMMANDS
	/* command for compressing */

	s = getenv ("LVQSOM_COMPRESS_COMMAND");
	if (s)
		compress_command = s;

	s = extract_parameter (argc, argv, "-compress_cmd", OPTION);
	if (s)
		compress_command = s;

	/* command for uncompressing */
	s = getenv ("LVQSOM_UNCOMPRESS_COMMAND");
	if (s)
		uncompress_command = s;

	s = extract_parameter (argc, argv, "-uncompress_cmd", OPTION);
	if (s)
		uncompress_command = s;
#endif /* NO_PIPED_COMMANDS */

	/* string that identifies a vector component to be ignored in files */
	s = getenv ("LVQSOM_MASK_STR");
	if (s)
		masked_string = s;

	s = extract_parameter (argc, argv, "-mask_str", OPTION);
	if (s)
		masked_string = s;

	if (extract_parameter (argc, argv, "-version", OPTION2))
		fprintf (stderr, "Version: %s\n", get_version ());

	verbose (oatoi (extract_parameter (argc, argv, VERBOSE, OPTION), 1));

	return 0;
}

/* save_snapshot - save a snapshot of the codebook */

int
save_snapshot (struct teach_params *teach, long iter)
{
	struct entries *codes = teach->codes;
	struct snapshot_info *shot = teach->snapshot;
	struct data_entry *entry;
	eptr p;
	char filename[1024];					/* hope this is enough */
	struct file_info *fi = NULL;
	int retcode = 0;
	int bg = shot->flags & SNAPFLAG_BACKGROUND;
	int ko = shot->flags & SNAPFLAG_KEEPOPEN;

	shot->counter++;
	if (ko)
		if ((fi = shot->fi) == NULL) {
			if ((shot->fi = open_file (shot->filename, "w")) == NULL)
				return 1;

			fi = shot->fi;
		} else
			fi = shot->fi;

#ifndef NO_BACKGROUND_SNAP
	if (bg) {
		if (shot->pid > 0) {
			int statptr;
			if (!(shot->flags & SNAPFLAG_NOWAIT)) {
				/* fprintf(stderr, "Snap: waiting for pid %d\n", (int)shot->pid); */
				/* wait for previous child before forking a new one */
				waitpid (shot->pid, &statptr, 0);
				shot->pid = -1;
			}
		}

		if ((shot->pid = fork ()) < 0) {
			perror ("save_snapshot(background):");
			return 1;
		}
		if (shot->pid == 0) {
			/* fprintf(stderr, "saving snapshot\n"); */
		} else {
			/* fprintf(stderr, "forked pid %d\n", (int)shot->pid); */
			return 0;
		}
	}
#endif /* NO_BACKGROUND_SNAP */

	if (fi == NULL) {
		/* make filename */
		sprintf (filename, shot->filename, iter);
		if ((fi = open_file (filename, "w")) == NULL)
			return 1;
	}

	if (ko)
		fprintf (fi2fp (fi), "#start %d\n", shot->counter);

	if (write_header (fi, codes)) {
		fprintf (stderr, "save_snapshot: Error writing headers\n");
		close_file (shot->fi);
		shot->fi = NULL;
		return 1;
	}

	/* open file for writing */

	ifverbose (3)
		fprintf (stderr, "saving snapshot: file '%s', type '%s'\n", filename,
						 get_str_by_id (snapshot_list, shot->type));

	fprintf (fi2fp (fi), "#SNAPSHOT FILE\n#iterations: %ld/%ld\n",
					 iter, teach->length);

	for (entry = rewind_entries (codes, &p); entry != NULL;
			 entry = next_entry (&p)) {
		if (write_entry (fi, codes, entry)) {
			fprintf (stderr, "save_entries: Error writing entry, aborting\n");
			retcode = 1;
			break;
		}
	}

	if (ko) {
		fprintf (fi2fp (fi), "#end\n");
		fflush (fi2fp (fi));
	} else
		close_file (fi);

#ifndef NO_BACKGROUND_SNAP
	if (bg)
		exit (retcode);
	else
#endif
		return (retcode);
}

/* get_snapshot - allocate and initialize snapshot info */

struct snapshot_info *
get_snapshot (char *filename, long interval, int type)
{
	struct snapshot_info *shot;
	int len = 0;
	shot = malloc (sizeof (struct snapshot_info));
	if (shot == NULL) {
		fprintf (stderr, "get_snapshot: Can't allocate structure\n");
		perror ("get_snapshot");
		return NULL;
	}

	shot->flags = 0;
	shot->fi = NULL;
#ifndef NO_BACKGROUND_SNAP
	shot->pid = -1;
#endif
	shot->counter = 0;
	shot->data = NULL;

	/* allocate room for string */
	shot->filename = NULL;
	if (filename) {
		len = strlen (filename);
		if ((shot->filename = malloc (len + 1)) == NULL) {
			fprintf (stderr, "get_snapshot: Can't allocate mem for string\n");
			perror ("get_snapshot");
			free (shot);
			return NULL;
		} else
			strcpy (shot->filename, filename);
	}

	if (len > 0)
		if (shot->filename[len - 1] == '&') {
			shot->filename[len - 1] = '\0';
			shot->flags |= SNAPFLAG_BACKGROUND;
		}
	shot->interval = interval;
	shot->type = type;
	switch (type) {
	case SNAPSHOT_KEEPOPEN:
		shot->flags |= SNAPFLAG_KEEPOPEN;
		shot->flags &= (~SNAPFLAG_NOWAIT);
		break;
#ifndef NO_BACKGROUND_SNAP
	case SNAPSHOT_ASYNC:
		shot->flags |= SNAPFLAG_BACKGROUND;
		break;
	case SNAPSHOT_ASYNC_NOWAIT:
		shot->flags |= SNAPFLAG_BACKGROUND | SNAPFLAG_NOWAIT;
		break;
#endif
	default:
		break;
	}

	ifverbose (2)
		fprintf (stderr, "snapshot: filename: '%s', interval: %ld, type: %s\n",
						 shot->filename, shot->interval, get_str_by_id (snapshot_list,
																														type));

	return shot;
}

/* free_snapshot - deallocate snapshot info */

void
free_snapshot (struct snapshot_info *shot)
{
	if (shot) {
		if (shot->filename)
			free (shot->filename);
		if (shot->fi)
			close_file (shot->fi);
#ifndef NO_BACKGROUND_SNAP
		if ((shot->pid > 0) && (!(shot->flags & SNAPFLAG_NOWAIT))) {
			int statptr;
			waitpid (shot->pid, &statptr, 0);
			shot->pid = -1;
		}
#endif /* NO_BACKGROUND_SNAP */
		free (shot);
	}
}

/* get_type_by_id - search typelist for id */

struct typelist *
get_type_by_id (struct typelist *types, int id)
{
	for (; types->str; types++)
		if (types->id == id)
			break;

	return types;
}

/* get_type_by_str - search typelist for string */

struct typelist *
get_type_by_str (struct typelist *types, char *str)
{
	for (; types->str; types++)
		if (str)										/* NULL str gets the last item */
			if (strcasecmp (types->str, str) == 0)
				break;

	return types;
}

/* -------  different alpha functions -------------- */

/* alpha functions */

/*    removed due to adaptive stopping condition
struct typelist alpha_list[] = {
	{ALPHA_LINEAR, "linear", linear_alpha},
	{ALPHA_INVERSE_T, "inverse_t", inverse_t_alpha},
	{ALPHA_UNKNOWN, NULL, NULL}
};
*/

/* linearly decreasing alpha to 0 */

/*    removed due to adaptive stopping condition
double
linear_alpha (long iter, long length, double alpha)
{
	return (alpha * (double) (length - iter) / (double) length);
}
*/

/*
#ifndef INV_ALPHA_CONSTANT
#define INV_ALPHA_CONSTANT 100.0
#endif

double inv_alpha_constant = INV_ALPHA_CONSTANT;

//

double
inverse_t_alpha (long iter, long length, double alpha)
{
	double c;

	c = length / inv_alpha_constant;

	return (alpha * c / (c + iter));
}

*/

/* print_lines */

int
print_lines (FILE * fp, char **lines)
{
	char *line;
	while ((line = *lines++))
		fputs (line, fp);

	return 0;
}
