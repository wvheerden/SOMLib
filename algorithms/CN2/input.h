/*  File:     input.h
    Author:   Robin Boswell
    Purpose:  Header file for input.y and input.l
*/ 

       /* SccsId = "@(#)input.h 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989" */

#include <stdio.h>

extern Attribute *IDclass;
extern List      attribute_list;
extern EList     example_list;
extern EList     *ex_ptr_array;
extern int       number_of_attributes, number_of_classes;
extern long      number_of_examples;
/* extern Tree      *yacked_tree; */ 
extern FILE      *yyin;
extern BOOL      ukdc_flag;
extern long      ln;
extern BOOL      errflag;




