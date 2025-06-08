/*  File:     test.c
    Author:   Robin Boswell
    Purpose:  Testing
*/ 

static char *SccsId = "@(#)test.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"

test()
{
     input_type = ATTRIBUTES_AND_EXAMPLES;

     
     if (! (yyin = fopen("/users/robin/mltools/NewId/Data/foo", "r"))) {
	  perror("test");
	  exit(1);
     }
	 
	  
     if (yyparse() != 0){
	  fprintf(stdout, "ERROR: Failed to parse foo\n");
	  fclose(yyin);
	  return(0);
     }
     else {
	  data_flow.status |= D_BOTH;
	  fclose(yyin);
     }
     threshold = DEFAULT_THRESHOLD;
     star_size = DEFAULT_STAR_SIZE;
     trace_flag = DEFAULT_TRACING;
     algorithm_flag = 0;
     
     run_cn();
     return(0);
     
}

     
