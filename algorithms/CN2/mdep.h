/*  File:     mdep.h
    Author:   Tim Niblett
    Purpose:  Machine dependencies for RealId
*/

       /* SccsId = "@(#)mdep.h 5.1 9/25/91 MLT" */

/* Dunno if these are necessary.  Best not to touch... */
#define SUN
#define SUN3
#ifdef SUN
#define TIMER
#endif

// SunOS directory-handling utils have changed between OS3 and OS4
// OS should be set to 3 or 4, as appropriate.

#define OS (4)

