/*  File:     qlalloc.h
    Author:   Tim Niblett
    Purpose:  Unknown (or possibly, don't care)
    */ 

/* SccsId = "@(#)qlalloc.h 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989"; */

#define	QLTYPE			long int     /* either short,long or double */

#define	QLALIGN			sizeof(QLTYPE)
#define	QLLARGEST		((QLTYPE)(~((QLTYPE)1 << ((QLALIGN << 3) - 1))))

#define	qlsize(p)		(((struct ql_header *)(p))[-1].bytes)
#define qlalloc(bytes)		_qlalloc((QLTYPE)(bytes))
#define qlsetsize(p,bytes)	_qlsetsize(p,(QLTYPE)(bytes))
#define qlzero(p)		setmem(p,(unsigned)qlsize(p),'\0')

#define QLNEW(type,count)	((type *)qlalloc((count) * sizeof(type)))
#define QLNEWSTR(ptr,str)	(ptr) = (char *)qlalloc(strlen(str) + 1); strcpy(ptr,str)

struct ql_header {
     QLTYPE	bytes;
};

extern void *_qlalloc();
extern int  _qlsetsize();
extern void qlfree();
extern void *qlcopy();
extern void qlinit();

 
