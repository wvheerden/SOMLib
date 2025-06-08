/*  File:     main.c
    Author:   Robin Boswell
    Purpose:  Top level of CN
*/ 

static char *SccsId = "@(#)main.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"


main()
{
     set_signal_handling(); /* So that we reset the terminal if the user */
                            /* quits or stops in cbreak mode             */
     
     initialise_global_variables();
     print_greeting();
     interact();
}

List global_rule_list;
RuleParams global_rule_parameters;
char *global_readfile;
pqueue *HEAP_PTR;

run_cn()
{

#ifdef NODE_COUNT
     nodecounter = 0;
#endif     

     if (DATA_BOTH){
	  fprintf(stdout, "Running CN on current example set...\n");
	  HEAP_PTR = create_heap();
	  if (ORDERED)
	    global_rule_list = ordered_cn(example_list);
	  else
	    global_rule_list = unordered_cn(example_list);
	  set_rule_parameters();
	  print_rule_list(stdout, global_rule_list, HUMAN);
#ifdef STATS	  
	  qfstats();
#endif	  
	  data_flow.status |= D_RULES;
     }
     
     else {
	  if (! DATA_ATTRIBUTES)
	    fprintf(stdout, "Data not loaded\n");
	  else
	    fprintf(stdout, "No current examples\n");	    
     }

}

       
initialise_global_variables()
{
     threshold = DEFAULT_THRESHOLD;
     star_size = DEFAULT_STAR_SIZE;
     trace_flag = DEFAULT_TRACING;
     algorithm_flag = DEFAULT_ALGORITHM;
     max_class_flag = DEFAULT_MAX_CLASS;     
     errest_flag = DEFAULT_ERREST;     
     init_data_flow();
     init_rule_params();
     global_readfile = (char *) ALLOC(BUFSIZ * sizeof(char));
}
