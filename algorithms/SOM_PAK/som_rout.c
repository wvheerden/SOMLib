/************************************************************************
 *                                                                      *
 *  Program package 'som_pak':                                          *
 *                                                                      *
 *  som_rout.c                                                          *
 *  - routines needed in some programs in som_pak                       *
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
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "lvq_pak.h"
#include "som_rout.h"
#include "datafile.h"

const int DEBUG = 0;

int numErrors;

double *trainingErrors;
double *validationErrors;
//double *cumulWeightChanges;

/*---------------------------------------------------------------------*/

struct entries *
randinit_codes (struct entries *data, int topol, int neigh,
								int xdim, int ydim)
{
	long noc, i;
	int dim;
	struct entries *codes;
	struct data_entry *entr;
	struct data_entry *maval, *mival;
	eptr p;
	long *compcnt = NULL;

	noc = xdim * ydim;

	if ((codes = alloc_entries ()) == NULL) {
		fprintf (stderr, "randinit_codes: can't allocate memory for codes\n");
		return NULL;
	}

	dim = data->dimension;
	codes->dimension = dim;
	codes->flags.loadmode = LOADMODE_ALL;
	codes->xdim = xdim;
	codes->ydim = ydim;
	codes->topol = topol;
	codes->neigh = neigh;

	/* allocate codebook entries */
	if ((entr = alloc_entry (codes)) == NULL) {
		fprintf (stderr,
						 "randinit_codes: can't allocate memory for codebook vector\n");
		close_entries (codes);
		return NULL;
	}
	codes->entries = entr;

	for (i = 1; i < noc; i++) {
		entr->next = alloc_entry (codes);
		entr = entr->next;
		if (entr == NULL)
			break;
	}

	if (entr == NULL) {
		fprintf (stderr, "randinit_codes: can't allocate codebook\n");
		close_entries (codes);
		return NULL;
	}

	codes->num_entries = noc;

	/* Find the maxim and minim values of data */

	if ((compcnt = malloc (sizeof (long) * dim)) == NULL) {
		fprintf (stderr, "randinit_codes: can't allocate memory\n");
		close_entries (codes);
		return NULL;
	}

	for (i = 0; i < dim; i++)
		compcnt[i] = 0;

	maval = alloc_entry (data);
	mival = alloc_entry (data);
	if (!(maval && mival)) {
		close_entries (codes);
		codes = NULL;
		goto end;
	}

	for (i = 0; i < data->dimension; i++) {
		maval->points[i] = DBL_MIN;
		mival->points[i] = DBL_MAX;
	}

	if ((entr = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "randinit_codes: can't get data\n");
		close_entries (codes);
		codes = NULL;
		goto end;
	}

	while (entr != NULL) {
		for (i = 0; i < dim; i++)
			if (!((entr->mask != NULL) && (entr->mask[i] != 0))) {
				compcnt[i]++;
				if (maval->points[i] < entr->points[i])
					maval->points[i] = entr->points[i];
				if (mival->points[i] > entr->points[i])
					mival->points[i] = entr->points[i];
			}
		entr = next_entry (&p);
	}

	for (i = 0; i < dim; i++)
		if (compcnt[i] == 0)
			fprintf (stderr,
							 "randinit_codes: warning! component %d has no data, using 0.0\n",
							 (int) (i + 1));

	/* Randomize the vector values */

	entr = rewind_entries (codes, &p);
	while (entr != NULL) {
		for (i = 0; i < dim; i++) {
			if (compcnt[i] > 0) {
				entr->points[i] = mival->points[i] + (maval->points[i] - mival->points[i]) *
			(orand_dbl ());  // [0,1)  originally: //((double) orand() / 32768.0);
			} else {
				entr->points[i] = 0.0;
      }
		}
		clear_entry_labels (entr);
		entr = next_entry (&p);
	}

end:
	if (compcnt)
		free (compcnt);
	free_entry (mival);
	free_entry (maval);

	return (codes);
}


/*---------------------------------------------------------------------*/

void
normalize (double *v, int n)
{
	double sum = 0.0;
	int j;

	for (j = 0; j < n; j++)
		sum += v[j] * v[j];
	sum = sqrt (sum);
	for (j = 0; j < n; j++)
		v[j] /= sum;
}


double
dotprod (double *v, double *w, int n)
{
	double sum = 0.0;
	int j;

	for (j = 0; j < n; j++)
		sum += v[j] * w[j];
	return (sum);
}


int
gram_schmidt (double *v, int n, int e)
{
	int i, j, p, t;
	double sum, *w = (double *) malloc (n * e * sizeof (double));

	if (w == NULL)
		return 1;

	for (i = 0; i < e; i++) {
		for (t = 0; t < n; t++) {
			sum = v[i * n + t];
			for (j = 0; j < i; j++)
				for (p = 0; p < n; p++)
					sum -= w[j * n + t] * w[j * n + p] * v[i * n + p];
			w[i * n + t] = sum;
		}
		normalize (w + i * n, n);
	}
	memcpy (v, w, n * e * sizeof (double));
	free (w);
	return 0;
}

/*
//  Returns [][first principal eigenvector][second principal eigenvector]

struct data_entry *
find_eigenvectors (struct entries *data)
{
	int n = data->dimension;
	double *r = (double *) malloc (n * n * sizeof (double));
	double *m = (double *) malloc (n * sizeof (double));       // holds means for each component over entire data set
	double *u = (double *) malloc (2 * n * sizeof (double));
	double *v = (double *) malloc (2 * n * sizeof (double));
	double mu[2];
	struct data_entry *ptr, *tmp;
	double sum;
	long i, j;
	long *k2, k;
	eptr p;
	char *mask;

	if (r == NULL || m == NULL || u == NULL || v == NULL)
		goto everror;

	for (i = 0; i < n * n; i++)
		r[i] = 0.0;
	for (i = 0; i < n; i++)
		m[i] = 0.0;

	k2 = malloc (n * sizeof (long));
	if (k2 == NULL)
		goto everror;
	memset (k2, 0, n * sizeof (long));

	if ((ptr = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "find_eigenvectors: can't get data\n");
		goto everror;
	}

	//  compute mean component values over all records in the data set

	for (k = 0; ptr != NULL; k++, ptr = next_entry (&p)) {
		mask = ptr->mask;
		for (i = 0; i < n; i++)
			if ((!mask) || (mask && (mask[i] == 0))) {
				m[i] += ptr->points[i];	// masked components have the value 0 so they don't affect the sum
				k2[i]++;
			}
	}

	if (k < 3)
		goto everror;

	for (i = 0; i < n; i++)
		m[i] /= k2[i];

	free (k2);
	k2 = NULL;

	if ((ptr = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "find_eigenvectors: can't get data\n");
		goto everror;
	}

	for (; ptr != NULL; ptr = next_entry (&p)) {
		mask = ptr->mask;
		for (i = 0; i < n; i++) {
			// the components that are masked off are ignored
			if (mask && (mask[i] != 0))
				continue;
			for (j = i; j < n; j++)
				if (mask && (mask[j] != 0))
					continue;
				else
					r[i * n + j] += (ptr->points[i] - m[i]) * (ptr->points[j] - m[j]);
		}
	}

	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			r[j * n + i] = r[i * n + j] /= k;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < n; j++) {
      u[i * n + j] =
        orand()/16384.0-1.0;
    }
		normalize (u + i * n, n);
		mu[i] = 1.0;
	}

	for (k = 0; k < 10; k++) {
		for (i = 0; i < 2; i++)
			for (j = 0; j < n; j++)
				v[i * n + j] =
					mu[i] * dotprod (r + j * n, u + i * n, n) + u[i * n + j];

		gram_schmidt (v, n, 2);

		sum = 0.0;
		for (i = 0; i < 2; i++) {
			for (j = 0; j < n; j++)
				sum += fabs (v[i * n + j] / dotprod (r + j * n, v + i * n, n));

			mu[i] = sum / n;
		}

		memcpy (u, v, 2 * n * sizeof (double));
	}

	if (mu[0] == 0.0 || mu[1] == 0.0)
		goto everror;

	//  add the mean over all records in the data set to ptr[0]

	ptr = tmp = alloc_entry (data);
	memcpy (tmp->points, m, n * sizeof (double));

	//  build first two principal eigenvectors, and add them to ptr[1] and ptr[2]

	for (i = 0; i < 2; i++) {
		tmp->next = alloc_entry (data);
		tmp = tmp->next;
		if (tmp == NULL) {
			fprintf (stderr, "find_eigenvectors: can't allocate vector\n");
			goto everror;
		}
		memcpy (tmp->points, u + n * i, n * sizeof (double));
		for (j = 0; j < n; j++)
			tmp->points[j] /= sqrt (mu[i]);
	}
	tmp->next = NULL;

	ofree (v);
	ofree (u);
	ofree (m);
	ofree (r);
	return (ptr);

everror:
	if (v != NULL)
		ofree (v);
	if (u != NULL)
		ofree (u);
	if (m != NULL)
		ofree (m);
	if (r != NULL)
		ofree (r);
	return (NULL);

}
*/

// **************************************
// Added for Su approach
// **************************************
/*
void swap(double *a, int i, int j) {
    double tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int Random(int i, int j) {
    return i + rand() % (j-i+1);
}

void quicksort(double *a, int left, int right) {
    int last = left, i;

    if (left >= right) return;

    swap(a,left,Random(left,right));
    for (i = left + 1; i <= right; i++)
        if (a[i] < a[left])
            swap(a,++last,i);
    swap(a,left,last);
    quicksort(a,left,last-1);
    quicksort(a,last+1,right);
}
*/
void
printDataSet(double ***dataSet, int numberOfDataSetRecords, int dataSetDimension)
{
  int i;
  int j;

  for (i = 0; i < numberOfDataSetRecords; i++) {
    for (j = 0; j < dataSetDimension; j++) {
      if (dataSet[i][j] == NULL) {
        printf("x ");
      } else {
        printf("%f ", dataSet[i][j][0]);
      }
      fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
  }
}

double
euclideanDistance(double *a, double *b, char *aMask, char *bMask, int dim)
{
  double sum = 0.0;
  int i;

  for (i = 0; i < dim; i++)
  {
    if (((aMask == NULL) || (aMask[i] == 0)) && ((bMask == NULL) || (bMask[i] == 0))) {
      sum += pow(a[i] - b[i], 2.0);
    }
  }

  return sqrt(sum);
}

// **************************************
// Modified lininit to follow Su approach
// **************************************

struct entries *
lininit_codes (struct entries *data, int topol, int neigh, int xdim, int ydim)
{
  long i = 0;
  long j = 0;
  long k = 0;
  int recordCounter = 0;
	eptr p;
  double **dataSet;
/*
double *ageValues;
int numAges;
int ageOffset;
int numBins;
*/
  char **dataRecordMasks;
  double ***SOMGrid;
  int dataSetDimension = data->dimension;
  long int numberOfDataSetRecords = 0;
  int numberOfCodebookVectors = xdim * ydim;
  double distance;
  double maxDistance = 0;
  struct data_entry *dataRecords;
  int boundingEntryIndex1 = 0;
  int boundingEntryIndex2 = 0;
  int boundingEntryIndex3 = 0;
  int boundingEntryIndex4 = 0;
  FILE *trackingFile;

  int returnValue = 0;

  // codebook vector that is returned
  struct entries *codebookVectors;

  // allocate memory for codebook vectors
  if ((codebookVectors = alloc_entries ()) == NULL) {
	  fprintf (stderr, "lininit_codes: Can't allocate memory for codes\n");
		return NULL;
	}

  // set parameters of codebook vectors
  codebookVectors->dimension = data->dimension;
  codebookVectors->flags.loadmode = LOADMODE_ALL;
	codebookVectors->xdim = xdim;
	codebookVectors->ydim = ydim;
	codebookVectors->topol = topol;
	codebookVectors->neigh = neigh;
	codebookVectors->num_entries = numberOfCodebookVectors;

	// allocate memory for initial data record associated with the codebook vectors
	if ((dataRecords = alloc_entry(codebookVectors)) == NULL) {
		fprintf (stderr, "lininit_codes: can't allocate memory for codebook vector\n");
		close_entries (codebookVectors);
		return NULL;
	}
	codebookVectors->entries = dataRecords;

  // allocate memory for the rest of the data records
	for (i = 1; i < numberOfCodebookVectors; i++) {
		dataRecords->next = alloc_entry (codebookVectors);
		dataRecords = dataRecords->next;
		if (dataRecords == NULL) {
		  fprintf (stderr, "randinit_codes: can't allocate codebook\n");
		  close_entries (codebookVectors);
		  return NULL;
    }
	}

  // reset data records
	if ((dataRecords = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "lininit_codes: can't get data\n");
		close_entries (codebookVectors);
		codebookVectors = NULL;
	}

  // read data records and data record masks out into a simpler structure
  while (dataRecords != NULL) {
    numberOfDataSetRecords++;
    dataRecords = next_entry(&p);
  }

  if (DEBUG == 1) {
    printf("%ld data set records read\n", numberOfDataSetRecords);
    printf("%d fields per record\n\n", dataSetDimension);
    fflush(stdout);
  }

  dataSet = (double **) malloc(numberOfDataSetRecords * sizeof(double *));
  for (i = 0; i < numberOfDataSetRecords; i++) {
    dataSet[i] = (double *) malloc(dataSetDimension * sizeof(double));
  }

  dataRecordMasks = (char **) malloc(numberOfDataSetRecords * sizeof(char *));
  for (i = 0; i < numberOfDataSetRecords; i++) {
    dataRecordMasks[i] = (char *) malloc(dataSetDimension * sizeof(char));
  }

  if ((dataRecords = rewind_entries(data, &p)) == NULL) {
		fprintf (stderr, "randinit_codes: can't get data\n");
		close_entries (codebookVectors);
		codebookVectors = NULL;
  }

/*
ageValues = (double *) malloc(numberOfDataSetRecords * sizeof(double));
ageOffset = 231;
numAges = 0;
*/
  for (i = 0; dataRecords != NULL; dataRecords = next_entry(&p), i++) {
    memcpy(dataSet[i], dataRecords->points, (dataSetDimension * sizeof(double)));
/*
if ((dataRecords->mask != NULL) && (dataRecords->mask[ageOffset] != 1)) {
  ageValues[numAges] = dataRecords->points[ageOffset];
  numAges++;
}
*/
    if (dataRecords->mask != NULL) {
      memcpy(dataRecordMasks[i], dataRecords->mask, (dataSetDimension * sizeof(char)));
    } else {
      dataRecordMasks[i] = NULL;
    }
  }

  // allocate memory for SOM grid
  if (DEBUG == 0) {
    SOMGrid = (double ***) malloc(xdim * sizeof(double **));
    for (i = 0; i < xdim; i++) {
      SOMGrid[i] = (double **) malloc(ydim * sizeof(double *));
      for (j = 0; j < ydim; j++) {
        SOMGrid[i][j] = (double *) malloc(dataSetDimension * sizeof(double));
      }
    }
  }

  i = 0;

  trackingFile = fopen("tracking1.txt", "r");
  if (trackingFile != NULL) {
    returnValue = fscanf(trackingFile, "%li %i %i %lf", &i, &boundingEntryIndex1, &boundingEntryIndex2, &maxDistance);
    fclose(trackingFile);
  }

  // find furthest separated two vectors (initialise  1 = upper right, 2 = lower left)
  for (; i < (numberOfDataSetRecords - 1); i++) {
      if (DEBUG == 1) {
        trackingFile = fopen("tracking1.txt", "w");
        fprintf(trackingFile, "%li %i %i %f", i, boundingEntryIndex1, boundingEntryIndex2, maxDistance);
        fclose(trackingFile);
      }
    for (j = (i + 1); j < numberOfDataSetRecords; j++) {
      distance = euclideanDistance(dataSet[i], dataSet[j], dataRecordMasks[i], dataRecordMasks[j], dataSetDimension);

      if (distance > maxDistance) {
        boundingEntryIndex1 = i;
        boundingEntryIndex2 = j;
        maxDistance = distance;
      }
    }
  }

  if (DEBUG == 1) {
    printf("Upper right: [");
    for (i = 0; i < dataSetDimension; i++) {
      if ((dataRecordMasks[boundingEntryIndex1] != NULL) && (dataRecordMasks[boundingEntryIndex1][i] == 1)) {
        printf("x ");
      } else {
        printf("%f ", dataSet[boundingEntryIndex1][i]);
      }
    }
    printf("]\n");
    fflush(stdout);

    printf("Lower left: [");
    for (i = 0; i < dataSetDimension; i++) {
      if ((dataRecordMasks[boundingEntryIndex2] != NULL) && (dataRecordMasks[boundingEntryIndex2][i] == 1)) {
        printf("x ");
      } else {
        printf("%f ", dataSet[boundingEntryIndex2][i]);
      }
    }
    printf("]\n");
    fflush(stdout);
  }

  // find third furthest separated vector (initialise upper left codebook)
  maxDistance = 0;
  i = 0;

  trackingFile = fopen("tracking2.txt", "r");
  if (trackingFile != NULL) {
    returnValue = fscanf(trackingFile, "%li %i %i %i %lf", &i, &boundingEntryIndex1, &boundingEntryIndex2, &boundingEntryIndex3, &maxDistance);
    fclose(trackingFile);
  }

  if (DEBUG == 1) {
    trackingFile = fopen("tracking2.txt", "w");
  }

  for (; i < numberOfDataSetRecords; i++) {
    if (DEBUG == 1) {
      trackingFile = fopen("tracking2.txt", "w");
      fprintf(trackingFile, "%li %i %i %i %f", i, boundingEntryIndex1, boundingEntryIndex2, boundingEntryIndex3, maxDistance);
      fclose(trackingFile);
    }
    if ((i != boundingEntryIndex1) && (i != boundingEntryIndex2)) {
      distance = euclideanDistance(dataSet[i], dataSet[boundingEntryIndex1], dataRecordMasks[i], dataRecordMasks[boundingEntryIndex1], dataSetDimension) + euclideanDistance(dataSet[i], dataSet[boundingEntryIndex2], dataRecordMasks[i], dataRecordMasks[boundingEntryIndex2], dataSetDimension);
      if (distance > maxDistance) {
        boundingEntryIndex3 = i;
        maxDistance = distance;
      }
    }
  }

  if (DEBUG == 1) {
    printf("Upper left: [");
    for (i = 0; i < dataSetDimension; i++) {
      if ((dataRecordMasks[boundingEntryIndex3] != NULL) && (dataRecordMasks[boundingEntryIndex3][i] == 1)) {
        printf("x ");
      } else {
        printf("%f ", dataSet[boundingEntryIndex3][i]);
      }
    }
    printf("]\n");
    fflush(stdout);
  }

  // find fourth furthest separated vector (initialise lower right)
  maxDistance = 0;
  i = 0;

  trackingFile = fopen("tracking3.txt", "r");
  if (trackingFile != NULL) {
    returnValue = fscanf(trackingFile, "%li %i %i %i %i %lf", &i, &boundingEntryIndex1, &boundingEntryIndex2, &boundingEntryIndex3, &boundingEntryIndex4, &maxDistance);
    fclose(trackingFile);
  }

  if (DEBUG == 1) {
    trackingFile = fopen("tracking3.txt", "w");
  }

  for (; i < numberOfDataSetRecords; i++) {
    if (DEBUG == 1) {
      trackingFile = fopen("tracking3.txt", "w");
      fprintf(trackingFile, "%li %i %i %i %i %f", i, boundingEntryIndex1, boundingEntryIndex2, boundingEntryIndex3, boundingEntryIndex4, maxDistance);
      fclose(trackingFile);
    }
    if ((i != boundingEntryIndex1) && (i != boundingEntryIndex2) && (i != boundingEntryIndex3)) {
      distance = euclideanDistance(dataSet[i], dataSet[boundingEntryIndex1], dataRecordMasks[i], dataRecordMasks[boundingEntryIndex1], dataSetDimension) + euclideanDistance(dataSet[i], dataSet[boundingEntryIndex2], dataRecordMasks[i], dataRecordMasks[boundingEntryIndex2], dataSetDimension) + euclideanDistance(dataSet[i], dataSet[boundingEntryIndex3], dataRecordMasks[i], dataRecordMasks[boundingEntryIndex3], dataSetDimension);
      if (distance > maxDistance) {
        boundingEntryIndex4 = i;
        maxDistance = distance;
      }
    }
  }

  if (DEBUG == 1) {
    printf("Lower right: [");
    for (i = 0; i < dataSetDimension; i++) {
      if ((dataRecordMasks[boundingEntryIndex4] != NULL) && (dataRecordMasks[boundingEntryIndex4][i] == 1)) {
        printf("x ");
      } else {
        printf("%f ", dataSet[boundingEntryIndex4][i]);
      }
    }
    printf("]\n");
    fflush(stdout);
  }

  if (DEBUG == 0) {

    memcpy(SOMGrid[xdim - 1][0], dataSet[boundingEntryIndex1], dataSetDimension * sizeof(double));
    memcpy(SOMGrid[0][ydim - 1], dataSet[boundingEntryIndex2], dataSetDimension * sizeof(double));
    memcpy(SOMGrid[0][0], dataSet[boundingEntryIndex3], dataSetDimension * sizeof(double));
    memcpy(SOMGrid[xdim - 1][ydim - 1], dataSet[boundingEntryIndex4], dataSetDimension * sizeof(double));

    // initialise upper and lower row of SOM grid
    for (i = 1; i < (xdim - 1); i++) {
      for (j = 0; j < dataSetDimension; j++) {
        SOMGrid[i][0][j] = (((SOMGrid[xdim - 1][0][j] - SOMGrid[0][0][j]) / (xdim - 1)) * i) + (SOMGrid[0][0][j]);
        SOMGrid[i][ydim - 1][j] = (((SOMGrid[xdim - 1][ydim - 1][j] - SOMGrid[0][ydim - 1][j]) / (xdim - 1)) * i) + (SOMGrid[0][ydim - 1][j]);
      }
    }

    // initialise left and right columns of SOM grid
    for (i = 1; i < (ydim - 1); i++) {
      for (j = 0; j < dataSetDimension; j++) {
        SOMGrid[0][i][j] = (((SOMGrid[0][ydim - 1][j] - SOMGrid[0][0][j]) / (ydim - 1)) * i) + (SOMGrid[0][0][j]);
        SOMGrid[xdim - 1][i][j] = (((SOMGrid[xdim - 1][ydim - 1][j] - SOMGrid[xdim - 1][0][j]) / (ydim - 1)) * i) + (SOMGrid[xdim - 1][0][j]);
      }
    }

    // initialise inner codebook vectors of SOM grid
    for (i = 1; i < (ydim - 1); i++) {
      for (j = 1; j < (xdim - 1); j++) {
        for (k = 0; k < dataSetDimension; k++) {
          SOMGrid[j][i][k] = (((SOMGrid[xdim - 1][i][k] - SOMGrid[0][i][k]) / (xdim - 1)) * j) + (SOMGrid[0][i][k]);
        }
      }
    }

    // set dataRecords to output to codebookVectors
    dataRecords = rewind_entries(codebookVectors, &p);

    // output SOMGrid to data file
    for (i = 0; i < ydim; i++) {
      for (j = 0; j < xdim; j++) {
        for (k = 0; k < dataSetDimension; k++) {
          dataRecords->points[k] = SOMGrid[j][i][k];
        }
        dataRecords = dataRecords->next;
      }
    }

    for (i = 0; i < numberOfDataSetRecords; i++) {
      free(dataSet[i]);
    }
    free(dataSet);

    for (i = 0; i < xdim; i++) {
      for (j = 0; j < ydim; j++) {
        free(SOMGrid[i][j]);
      }
      free(SOMGrid[i]);
    }
    free(SOMGrid);

  }

  return codebookVectors;

}

// old lininit code which appears to fail

/*
struct entries *
lininit_codes (struct entries *data, int topol, int neigh, int xdim, int ydim)
{
	long i, number_of_codes, index;
	int dim;
	double xf, yf;
	struct data_entry *mean, *eigen1, *eigen2, *entr;
	struct entries *codes;
	eptr p;

	number_of_codes = xdim * ydim;

	if ((codes = alloc_entries ()) == NULL) {
		fprintf (stderr, "Can't allocate memory for codes\n");
		return NULL;
	}

	dim = data->dimension;
	codes->dimension = dim;
	codes->flags.loadmode = LOADMODE_ALL;
	codes->xdim = xdim;
	codes->ydim = ydim;
	codes->topol = topol;
	codes->neigh = neigh;
	codes->num_entries = number_of_codes;

	// mean[0] = mean over all data patterns in the data set
	// mean[1] = first principal eigenvector
	// mean[2] = second principal eigenvector

	mean = find_eigenvectors (data);
	if (mean == NULL) {
		fprintf (stderr, "lininit_codes: Can't find eigenvectors\n");
		close_entries (codes);
		return NULL;
	}
	eigen1 = mean->next;
	eigen2 = eigen1->next;

	// allocate codebook entries
	if ((entr = alloc_entry (codes)) == NULL) {
		fprintf (stderr,
						 "lininit_codes: can't allocate memory for codebook vector\n");
		close_entries (codes);
		return NULL;
	}
	codes->entries = entr;

	for (i = 1; i < number_of_codes; i++) {
		entr->next = alloc_entry (codes);
		entr = entr->next;
		if (entr == NULL)
			break;
	}

	if (entr == NULL) {
		fprintf (stderr, "lininit_codes: can't allocate codebook\n");
		free_entrys (mean);
		close_entries (codes);
		return NULL;
	}

	// Initialize the units
	entr = rewind_entries (codes, &p);
	index = 0;
	while (entr != NULL) {
		xf = 4.0 * (double) (index % xdim) / (xdim - 1.0) - 2.0;
		yf = 4.0 * (double) (index / xdim) / (ydim - 1.0) - 2.0;

		for (i = 0; i < dim; i++) {
			entr->points[i] = mean->points[i]
				+ xf * eigen1->points[i] + yf * eigen2->points[i];
		}
		clear_entry_labels (entr);

		entr = next_entry (&p);
		index++;
	}

	free_entrys (mean);

	return (codes);
}*/


/*---------------------------------------------------------------------*/

double
hexa_dist (int bx, int by, int tx, int ty)
{
	double ret, diff;

	diff = bx - tx;

	if (((by - ty) % 2) != 0) {
		if ((by % 2) == 0) {
			diff -= 0.5;
		} else {
			diff += 0.5;
		}
	}

	ret = diff * diff;
	diff = by - ty;
	ret += 0.75 * diff * diff;
	ret = (double) sqrt ((double) ret);

	return (ret);
}

double
rect_dist (int bx, int by, int tx, int ty)
{
	double ret, diff;

	diff = bx - tx;
	ret = diff * diff;
	diff = by - ty;
	ret += diff * diff;
	ret = (double) sqrt ((double) ret);

	return (ret);
}

/* Adaptation function for bubble-neighborhood */

void
bubble_adapt (struct teach_params *teach, struct data_entry *sample,
							int bx, int by, double radius, double alpha)
{
	long index;
	int tx, ty, xdim;
	struct entries *codes = teach->codes;
	MAPDIST_FUNCTION *dist = teach->mapdist;
	struct data_entry *codetmp;
	VECTOR_ADAPT *adapt = teach->vector_adapt;
	eptr p;

	xdim = codes->xdim;

	ifverbose (10) fprintf (stderr, "Best match in %d, %d\n", bx, by);

	codetmp = rewind_entries (codes, &p);
	index = 0;

	while (codetmp != NULL) {
		tx = index % xdim;
		ty = index / xdim;

		if (dist (bx, by, tx, ty) <= radius) {
			ifverbose (11) fprintf (stderr, "Adapt unit %d, %d\n", tx, ty);

			adapt (codetmp, sample, codes->dimension, alpha);

		}
		codetmp = next_entry (&p);
		index++;
	}
}


/* Adaptation function for gaussian neighbourhood */

void
gaussian_adapt (struct teach_params *teach, struct data_entry *sample,
								int bx, int by, double radius, double alpha)
{
	long index;
	int tx, ty, xdim;
	double dd;
	double alp;
	struct entries *codes = teach->codes;
	MAPDIST_FUNCTION *dist = teach->mapdist;
	VECTOR_ADAPT *adapt = teach->vector_adapt;
	struct data_entry *codetmp;
	eptr p;

	xdim = codes->xdim;

	ifverbose (10) fprintf (stderr, "Best match in %d, %d\n", bx, by);

	codetmp = rewind_entries (codes, &p);
	index = 0;

//  currentCumulativeWeightChange = 0.0;

	while (codetmp != NULL) {
		tx = index % xdim;
		ty = index / xdim;

		ifverbose (11) fprintf (stderr, "Adapt unit %d, %d\n", tx, ty);
		dd = dist (bx, by, tx, ty);

    // calculate (gaussian kernel) neighbourhood function
		alp = alpha * (double) exp ((double) (-dd * dd / (2.0 * radius * radius)));

		adapt (codetmp, sample, codes->dimension, alp);
//    currentCumulativeWeightChange += currentVectorWeightChange;

		codetmp = next_entry (&p);
		index++;
	}

//  currentCumulativeWeightChange /= (index * codes->dimension);
}

void
initErrorMeasures()
{
  numErrors = 100;
  trainingErrors = (double *) malloc(numErrors * sizeof(double));
  validationErrors = (double *) malloc(numErrors * sizeof(double));
//  cumulWeightChanges = (double *) malloc(numErrors * sizeof(double));

  // required for timeline graph output
	//printf("iteration\ttrainingError\tvalidationError\n");
}

int
checkStoppingConditions(struct teach_params *teach, int qmode, long *iteration)
{
  // general
  int precision = DBL_DIG;
  int i;

  // error levels
  double *newTrainingErrors;
  double *newValidationErrors;
//  double *newCumulWeightChanges;

  // error moving averages
  const int WINDOW_SIZE = 30;
  double trainingErrorMovingAverage = 0.0;
//  double validationErrorMovingAverage = 0.0;
//  double cumulWeightChangeMovingAverage = 0.0;

  // standard deviation
  double trainingMovingStandardDeviation = DBL_MAX;
//  double validationMovingStandardDeviation = DBL_MAX;
//  double cumulWeightChangeStandardDeviation = DBL_MAX;

  // grow error structures if necessary
  if (*iteration == numErrors) {
    newTrainingErrors = (double *) malloc((numErrors + 100) * sizeof(double));
    newValidationErrors = (double *) malloc((numErrors + 100) * sizeof(double));
//    newCumulWeightChanges = (double *) malloc((numErrors + 100) * sizeof(double));
    for (i = 0; i < numErrors; i++) {
      newTrainingErrors[i] = trainingErrors[i];
      newValidationErrors[i] = validationErrors[i];
//      newCumulWeightChanges[i] = cumulWeightChanges[i];
    }
    numErrors += 100;
    free(trainingErrors);
    free(validationErrors);
//    free(cumulWeightChanges);
    trainingErrors = newTrainingErrors;
    validationErrors = newValidationErrors;
//    cumulWeightChanges = newCumulWeightChanges;
  }

  // update error arrays (this is average quantisation error)
  if (qmode > 0) {
    trainingErrors[*iteration] = find_training_qerror2(teach) / (double) teach->data_training_error->num_entries;
    validationErrors[*iteration] = find_validation_qerror2(teach) / (double) teach->data_validation_error->num_entries;
  } else {
    trainingErrors[*iteration] = find_training_qerror(teach) / (double) teach->data_training_error->num_entries;
    validationErrors[*iteration] = find_validation_qerror(teach) / (double) teach->data_validation_error->num_entries;
  }

  // update cumulative weight change array
//  cumulWeightChanges[*iteration] = currentCumulativeWeightChange;

  if (*iteration >= WINDOW_SIZE - 1) {
    // calculate moving averages
    for (i = *iteration; i > *iteration - WINDOW_SIZE; i--) {
      trainingErrorMovingAverage += trainingErrors[i];
//      validationErrorMovingAverage += validationErrors[i];
//      cumulWeightChangeMovingAverage += cumulWeightChanges[i];
    }
    trainingErrorMovingAverage /= WINDOW_SIZE;
//    validationErrorMovingAverage /= WINDOW_SIZE;
//    cumulWeightChangeMovingAverage /= WINDOW_SIZE;

    // calculate windowed standard deviations
    trainingMovingStandardDeviation = 0.0;
//    validationMovingStandardDeviation = 0.0;
//    cumulWeightChangeStandardDeviation = 0.0;
    for (i = *iteration; i > *iteration - WINDOW_SIZE; i--) {
      trainingMovingStandardDeviation += pow((trainingErrors[i] - trainingErrorMovingAverage), 2.0);
//      validationMovingStandardDeviation += pow((validationErrors[i] - validationErrorMovingAverage), 2.0);
//      cumulWeightChangeStandardDeviation += pow((cumulWeightChanges[i] - cumulWeightChangeMovingAverage), 2.0);
    }
    trainingMovingStandardDeviation /= (WINDOW_SIZE - 1);
    trainingMovingStandardDeviation = sqrt(trainingMovingStandardDeviation);
//    validationMovingStandardDeviation /= (WINDOW_SIZE - 1);
//    validationMovingStandardDeviation = sqrt(validationMovingStandardDeviation);
//    cumulWeightChangeStandardDeviation /= (WINDOW_SIZE - 1);
//    cumulWeightChangeStandardDeviation = sqrt(cumulWeightChangeStandardDeviation);
  }

/*
if (*iteration >= WINDOW_SIZE) {
//  printf("%d\t%.*f\t%.*f\t%.*f\t%.*f\n", *iteration, DBL_DIG, cumulWeightChanges[*iteration], DBL_DIG, cumulWeightChangeMovingAverage, DBL_DIG, cumulWeightChangeStandardDeviation);
  printf("%d\t%.*f\t%.*f\t%.*f\t%.*f\n", *iteration, DBL_DIG, trainingErrors[*iteration], DBL_DIG, trainingErrorMovingAverage, DBL_DIG, trainingMovingStandardDeviation, DBL_DIG, validationErrors[*iteration]);
  fflush(stdout);
} else {
//  printf("%d\t%.*f\t\t\n", *iteration, DBL_DIG, cumulWeightChanges[*iteration]);
  printf("%d\t%.*f\t.\t.\t%.*f\n", *iteration, DBL_DIG, trainingErrors[*iteration], DBL_DIG, validationErrors[*iteration]);
  fflush(stdout);
}
*/

  // required for timeline graph output
	//printf("%d\t%.*f\t%.*f\n", *iteration, precision, trainingErrors[*iteration], precision, validationErrors[*iteration], precision);

	if ((trainingMovingStandardDeviation < 0.0001) || (*iteration >= 100000)) {
		fprintf(stderr, "\nFinal iteration: %ld\nFinal training error: %.*f\nFinal validation error: %.*f\n\n", *iteration, precision, trainingErrors[*iteration], precision, validationErrors[*iteration]);
		return TRUE;
	} else {
		(*iteration)++;
		return FALSE;
	}

}

/* som_training - train a SOM. Radius of the neighborhood decreases
   linearly from the initial value to one and the learning parameter
   decreases linearly from its initial value to zero. */

struct entries *som_training (struct teach_params *teach)
{

	NEIGH_ADAPT *adapt;
	WINNER_FUNCTION *find_winner = teach->winner;
	//ALPHA_FUNC *get_alpha = teach->alpha_func;    removed due to adaptive stopping conditions
	int dim;
	int bxind, byind;
	double weight;
	double trad, talp;
	struct data_entry *sample;
	struct entries *data_training = teach->data_training;
	struct entries *data_training_error = teach->data_training_error;
	struct entries *data_validation_error = teach->data_validation_error;
	struct entries *codes = teach->codes;
	long le = 0;
	int qmode = teach->qmode;
	double alpha = teach->alpha;
	double radius = teach->radius;
	struct snapshot_info *snap = teach->snapshot;
	struct winner_info win_info;
	eptr pt;
	int done = FALSE;

/*
int i;
*/

	if (set_som_params (teach)) {
		fprintf (stderr, "som_training: can't set SOM parameters\n");
		return NULL;
	}

	adapt = teach->neigh_adapt;

	if ((sample = rewind_entries (data_training, &pt)) == NULL) {
		fprintf (stderr, "som_training: can't get training data\n");
		return NULL;
	}

	dim = codes->dimension;
	if (data_training->dimension != dim) {
		fprintf (stderr, "code dimension (%d) != data dimension (%d)\n",
						 dim, data_training->dimension);
		return NULL;
	}

	time (&teach->start_time);

  initErrorMeasures();

  do {
		/* if we are at the end of data file, go back to the start */
		if (sample == NULL) {
			sample = rewind_entries (data_training, &pt);

			if (sample == NULL) {
				fprintf (stderr,
								 "som_training: couldn't rewind data (%ld iterations done)\n",
								 le);
				return NULL;
			}
		}

		weight = sample->weight;

		/* Radius decreases linearly to one */

		//trad = 1.0 + (radius - 1.0) * (double) (length - le) / (double) length;
    trad = radius * exp(-le / teach->radiusDecay);
    if (trad < 1.0)
      trad = 1.0;
    talp = alpha * exp(-le / teach->alphaDecay);

		//talp = get_alpha (le, alpha);   removed due to adaptive stopping conditions

		/* If the sample is weighted, we
		   modify the training rate so that we achieve the same effect as
		   repeating the sample 'weight' times */
		if ((weight > 0.0) && (use_weights (-1))) {
			talp = 1.0 - (double) pow ((double) (1.0 - talp), (double) weight);
		}

		/* Find the best match */
		/* If fixed point and is allowed then use that value */
		if ((sample->fixed != NULL) && (use_fixed (-1))) {
			/* Get the values from fixed-structure */
			bxind = sample->fixed->xfix;
			byind = sample->fixed->yfix;
		} else {

			if (find_winner (codes, sample, &win_info, 1) == 0) {
				ifverbose (3)
					fprintf (stderr, "ignoring empty sample %ld\n", le);
				goto skip_teach;				/* ignore empty samples */
			}
			bxind = win_info.index % codes->xdim;
			byind = win_info.index / codes->xdim;
		}

/*
printf("Adapting using sample: ");
for (i = 0; i < data_training->dimension; i++) {
  printf("%f ", sample->points[i]);
}
printf("\n");
*/

		/* Adapt the units */
		adapt (teach, sample, bxind, byind, trad, talp);

	skip_teach:
		/* save snapshot when needed */
		if ((snap) && ((le % snap->interval) == 0) && (le > 0)) {
			ifverbose (2)
				fprintf (stderr, "Saving snapshot, %ld iterations\n", le);
			if (save_snapshot (teach, le)) {
				fprintf (stderr, "snapshot failed, continuing teaching\n");
			}
		}

		//ifverbose (1) mprint ((long) (length - le));
    //printf(".");

    done = checkStoppingConditions(teach, qmode, &le);
    sample = next_entry (&pt);
	} while (!done);

	time (&teach->end_time);
  //printf("Convergence after: %d epochs", le);

	//ifverbose (1) {
		//mprint ((long) 0);
		//fprintf (stderr, "\n");
	//}
	return (codes);
}


/*---------------------------------------------------------------------*/

/* find_qerror - calculate quantization error. */

double
find_training_qerror (struct teach_params *teach)
{
	double qerror;
	struct entries *data;
	struct entries *codes = teach->codes;
	WINNER_FUNCTION *find_winner = teach->winner;
	struct data_entry *dtmp;
	struct winner_info win_info;
	eptr p;
	int length_known;

  // choose training set
  data = teach->data_training_error;

	if (set_som_params (teach)) {
		fprintf (stderr, "find_qerror: can't set SOM parameters\n");
		return -1;
	}

	// Scan all data entries

	qerror = 0.0;
	if ((dtmp = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "find_qerror: can't get data\n");
		return -1.0;
	}

  // calculate quantisation error over entire set of data entries
	for (; dtmp != NULL; dtmp = next_entry (&p)) {
    // ignore empty vectors
		if (find_winner (codes, dtmp, &win_info, 1) == 0) {
			continue;
    }
    // add euclidean distance (sqrt(difference)) to quantisation error
		qerror += sqrt ((double) win_info.diff);
	}

	return (qerror);
}

double
find_validation_qerror (struct teach_params *teach)
{
	double qerror;
	struct entries *data;
	struct entries *codes = teach->codes;
	WINNER_FUNCTION *find_winner = teach->winner;
	struct data_entry *dtmp;
	struct winner_info win_info;
	eptr p;
	int length_known;

  // choose validation set
  data = teach->data_validation_error;

	if (set_som_params (teach)) {
		fprintf (stderr, "find_qerror: can't set SOM parameters\n");
		return -1;
	}

	// Scan all data entries

	qerror = 0.0;
	if ((dtmp = rewind_entries (data, &p)) == NULL) {
		fprintf (stderr, "find_qerror: can't get data\n");
		return -1.0;
	}

  // calculate quantisation error over entire set of data entries
	for (; dtmp != NULL; dtmp = next_entry (&p)) {
    // ignore empty vectors
		if (find_winner (codes, dtmp, &win_info, 1) == 0) {
			continue;
    }
    // add euclidean distance (sqrt(difference)) to quantisation error
		qerror += sqrt ((double) win_info.diff);
	}

	return (qerror);
}

double
bubble_qerror (struct teach_params *teach, struct data_entry *sample,
							 int bx, int by, double radius)
{
	long index;
	int tx, ty, xdim;
	struct entries *codes = teach->codes;
	MAPDIST_FUNCTION *mdist = teach->mapdist;
	DIST_FUNCTION *distance = teach->dist;
	struct data_entry *codetmp;
	eptr p;
	double d, qerror;

	xdim = codes->xdim;

	ifverbose (10) fprintf (stderr, "Best match in %d, %d\n", bx, by);

	codetmp = rewind_entries (codes, &p);
	index = 0;
	qerror = 0;

	while (codetmp != NULL) {
		tx = index % xdim;
		ty = index / xdim;

		if (mdist (bx, by, tx, ty) <= radius) {
			ifverbose (11) fprintf (stderr, "Adapt unit %d, %d\n", tx, ty);

			d = distance (codetmp, sample, codes->dimension);
			/* assume that alpha = 1.0 */
			qerror += d * d;

		}
		codetmp = next_entry (&p);
		index++;
	}
	return (qerror);
}


double
gaussian_qerror (struct teach_params *teach, struct data_entry *sample,
								 int bx, int by, double radius)
{
	long index;
	int tx, ty, xdim;
	double dd;
	double alp;
	struct entries *codes = teach->codes;
	MAPDIST_FUNCTION *mdist = teach->mapdist;
	DIST_FUNCTION *distance = teach->dist;
	struct data_entry *codetmp;
	eptr p;
	double d, qerror;

	xdim = codes->xdim;

	ifverbose (10) fprintf (stderr, "Best match in %d, %d\n", bx, by);

	codetmp = rewind_entries (codes, &p);
	index = 0;
	qerror = 0.0;

	while (codetmp != NULL) {
		tx = index % xdim;
		ty = index / xdim;

		ifverbose (11) fprintf (stderr, "Adapt unit %d, %d\n", tx, ty);
		dd = mdist (bx, by, tx, ty);

		alp = exp ((double) (-dd * dd / (2.0 * radius * radius)));

		d = distance (codetmp, sample, codes->dimension);

		qerror += alp * d * d;

		codetmp = next_entry (&p);
		index++;
	}

	return (qerror);
}

/* find_qerror2 - calculate quantization error in a different way. */

double
find_training_qerror2 (struct teach_params *teach)
{
	double qerror;
	struct entries *data;
	struct entries *codes = teach->codes;
	WINNER_FUNCTION *find_winner = teach->winner;
	NEIGH_QERROR *calc_qerror;
	struct data_entry *dtmp;
	struct winner_info win_info;
	int bxind, byind, length_known;
	double radius = teach->radius;
	eptr p;

  // choose training set
  data = teach->data_training_error;

	if (set_som_params (teach)) {
		fprintf (stderr, "find_qerror2: can't set SOM parameters\n");
		return -1;
	}

	/* select neighborhood */
	if (teach->codes->neigh == NEIGH_GAUSSIAN) {
		ifverbose (3) fprintf (stderr, "qmode 1, gaussian neighbourhood\n");
		calc_qerror = gaussian_qerror;
	} else {
		ifverbose (3) fprintf (stderr, "qmode 1, bubble neighbourhood\n");
		calc_qerror = bubble_qerror;
	}

	/* Scan all data entries */

	qerror = 0.0;

	dtmp = rewind_entries (data, &p);

	for (; dtmp != NULL; dtmp = next_entry (&p)) {
		if (find_winner (codes, dtmp, &win_info, 1) == 0)
			continue;									/* ignore empty vectors */

		bxind = win_info.index % codes->xdim;
		byind = win_info.index / codes->xdim;

		qerror += calc_qerror (teach, dtmp, bxind, byind, radius);
	}

	return (qerror);
}

double
find_validation_qerror2 (struct teach_params *teach)
{
	double qerror;
	struct entries *data;
	struct entries *codes = teach->codes;
	WINNER_FUNCTION *find_winner = teach->winner;
	NEIGH_QERROR *calc_qerror;
	struct data_entry *dtmp;
	struct winner_info win_info;
	int bxind, byind, length_known;
	double radius = teach->radius;
	eptr p;

  // choose validation set
  data = teach->data_validation_error;

	if (set_som_params (teach)) {
		fprintf (stderr, "find_qerror2: can't set SOM parameters\n");
		return -1;
	}

	/* select neighborhood */
	if (teach->codes->neigh == NEIGH_GAUSSIAN) {
		ifverbose (3) fprintf (stderr, "qmode 1, gaussian neighbourhood\n");
		calc_qerror = gaussian_qerror;
	} else {
		ifverbose (3) fprintf (stderr, "qmode 1, bubble neighbourhood\n");
		calc_qerror = bubble_qerror;
	}

	/* Scan all data entries */

	qerror = 0.0;

	dtmp = rewind_entries (data, &p);

	for (; dtmp != NULL; dtmp = next_entry (&p)) {
		if (find_winner (codes, dtmp, &win_info, 1) == 0)
			continue;									/* ignore empty vectors */

		bxind = win_info.index % codes->xdim;
		byind = win_info.index / codes->xdim;

		qerror += calc_qerror (teach, dtmp, bxind, byind, radius);
	}

	return (qerror);
}

MAPDIST_FUNCTION *
get_mapdistf (int topol)
{
	MAPDIST_FUNCTION *dist;

	switch (topol) {
	case TOPOL_RECT:
		dist = rect_dist;
		break;
	case TOPOL_HEXA:
		dist = hexa_dist;
		break;
	case TOPOL_LVQ:
	default:
		dist = NULL;
		break;
	}
	return dist;
}

NEIGH_ADAPT *
get_nadaptf (int neigh)
{
	NEIGH_ADAPT *nadapt;

	switch (neigh) {
	case NEIGH_GAUSSIAN:
		nadapt = gaussian_adapt;
		break;
	case NEIGH_BUBBLE:
		nadapt = bubble_adapt;
		break;
	default:
		nadapt = NULL;
		break;
	}

	return nadapt;
}

/* set_som_params - set functions needed by the SOM algorithm in the
   teach_params structure */

int
set_som_params (struct teach_params *params)
{
	if (!params->mapdist)
		if ((params->mapdist = get_mapdistf (params->topol)) == NULL)
			return 1;

	if (!params->neigh_adapt)
		if ((params->neigh_adapt = get_nadaptf (params->neigh)) == NULL)
			return 1;

	return 0;
}
