/*  File:     mlt_float.h
    Author:   Robin Boswell
    Purpose:  Subset of <float.h>, which we ain't got.
              Further items to be added as required.
	      Maybe replace with the real thing someday.

    Change Log:

      2/16/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Added conditional to pick up <float.h> if available.
        Added log2 macro.
*/ 

       /* SccsId = "@(#)mlt_float.h 5.1 9/25/91 MLT" */


#ifdef _HAVE_FLOAT_H
#include <float.h>
#else
#define FLT_MAX  (1E+37)
#endif

#ifndef _HAVE_LOG2
#define log2(num) (log(num) * M_LOG2E)
#endif
