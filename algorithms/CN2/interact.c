/*  File:     interact.c
    Author:   Robin Boswell
    Purpose:  Interaction

    Change Log:

      3/20/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Added include of <unistd.h> for declaration of access() args
        (see get_permitted_file())
*/ 

static char *SccsId = "@(#)interact.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include <stdio.h>
#include "mdep.h"

#include "cn_externs.h"
#include <ctype.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>


FILE *get_permitted_file();
BOOL yes();
BOOL tty_ok;
char data_dir[BUFSIZ];
DataFlow data_flow;
InputType input_type;
float threshold;

interact()
{
     BOOL exit = FALSE;
     strcpy(data_dir, "");

     
     while (! exit){
	  fprintf(stdout, "CN> ");
	  fflush(stdout);
	  
	  switch (select_char("irstdcmxqehawl?\n")) {
	  case 'i':
	       fprintf(stdout, "Induce\n");
	       run_cn();
	       break;
	  case 'r':
	       fprintf(stdout, "Read\n");	       
	       i_read_file();
	       break;
	  case 'w':
	       fprintf(stdout, "Write\n");	       
	       i_write_file();
	       break;
	  case 'c':
	       fprintf(stdout, "CKRL\n");
	       ckrl_mode();
	       break;
	  case 's':
	       fprintf(stdout, "Star size\n");	       
	       change_starsize();
	       break;
	  case 'm':
	       fprintf(stdout, "Maximum class forcing\n");	       
	       change_maxclass();
	       break;	       
	  case 't':
	       fprintf(stdout, "Threshold\n");	       
	       change_threshold();
	       break;	       
	  case 'd':
	       fprintf(stdout, "Display\n");	       
	       change_tracing();
	       break;
	  case 'a':
	       fprintf(stdout, "Algorithm\n");	       
	       change_algorithm();
	       break;
	  case 'e':
	       fprintf(stdout, "Error estimate\n");	       
	       change_errest();
	       break;
	  case 'x':
	       fprintf(stdout, "Execute\n");	       
	       evaluate_rules();
	       break;
	  case 'l':
	       fprintf(stdout, "List\n");	       
	       list_rules();
	       break;
	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");	       	       
	       cn_help();
	       break;
	  case '\n':
	       fprintf(stdout, "\n");
	       break;
	  default:
	       fprintf(stdout, "Quit\n");	       
	       exit = TRUE;
	       break;	       
	  }
     }
     fprintf(stdout, "Have a nice day!\n");
     return(1);     
}
     

i_read_file()
{
     char filename[BUFSIZ];
     
     fprintf(stdout, "READ> Both, Atts, Examples or Rules? ");
     fflush(stdout);     
     switch (select_char("baer\n")) {	  
     case 'b':
	  fprintf(stdout, "Both\n");
	  input_type = ATTRIBUTES_AND_EXAMPLES;
	  free_list(attribute_list);
	  attribute_list = (List)0;
	  data_flow.status &= ~D_ATTRIBUTES;	  
	  really_free_elist(example_list);
	  example_list = (EList)0;
	  data_flow.status &= ~D_EXAMPLES;	       	  	  
	  break;
     case 'a':
	  fprintf(stdout, "Attributes\n");
	  input_type = ATTRIBUTES;
	  free_list(attribute_list);
	  attribute_list = (List)0;
	  data_flow.status &= ~D_ATTRIBUTES;	  	  
	  really_free_elist(example_list);
	  example_list = (EList)0;
	  data_flow.status &= ~D_EXAMPLES;	       	       	  
	  break;
     case 'e':
	  fprintf(stdout, "Examples\n");
	  if (! DATA_ATTRIBUTES){
	       fprintf(stdout, "You must load some attribute definitions ");
	       fprintf(stdout, "before you can read any examples.\n");
	       return(0);
	  }
	  else {
	       really_free_elist(example_list);
	       example_list = (EList)0;
	       data_flow.status &= ~D_EXAMPLES;	       	       	       
	       input_type = EXAMPLES;
	  }
	  break;
     case 'r':
	  fprintf(stdout, "Rules\n");
	  if (! DATA_ATTRIBUTES){
	       fprintf(stdout, "You must load some attribute definitions ");
	       fprintf(stdout, "before you can read any rules.\n");
	       return(0);
	  }
	  else
	    input_type = RULES;
	  break;
     case '\n':
	  fprintf(stdout, "\n   Returning to top level...\n");
	  return(0);
     }
     
     if (! (yyin = get_permitted_file(filename, "r"))){
	  fprintf(stdout, "Returning to top level...\n");  
	  return(0);
     }
     
     if (yyparse() != 0){
	  fprintf(stdout, "ERROR: Failed to parse file \"%s\".\n", filename);
	  fclose(yyin);	  
	  return(0);
     }
     else {
	  switch (input_type){
	  case ATTRIBUTES_AND_EXAMPLES:
	       data_flow.status |= D_BOTH;
	       strcpy(data_flow.example_file, global_readfile);
	       strcpy(data_flow.attribute_file, global_readfile);
#ifdef STATS	       
	       qfstats();
#endif	       
	       break;
	  case ATTRIBUTES:
               if (DATA_EXAMPLES)
		 fprintf(stdout, "Scrapping previously-loaded examples\n");
	       data_flow.status |= D_ATTRIBUTES;
	       data_flow.status &= ~D_EXAMPLES;
	       strcpy(data_flow.attribute_file, global_readfile);
	       strcpy(data_flow.example_file, "");
	       break;
	  case EXAMPLES:
	       data_flow.status |= D_EXAMPLES;
	       strcpy(data_flow.example_file, global_readfile);
	       break;
	  case RULES:
	       data_flow.status |= D_RULES;
	       break;
	  }
	  fclose(yyin);
	  return(1);
     }     
}

i_write_file()
{
     char filename[BUFSIZ];
     FILE *fp;
     if (DATA_RULES){
	  if (! (fp = get_permitted_file(filename, "w")))
	    return(0);
	  fprintf(stdout, "Writing current rules to %s\n", filename);
	  print_rule_file(fp, global_rule_list);
	  fclose(fp);
	  return(1);
     }
     else {
	  fprintf(stdout, "No rules to print.\n");
	  return(0);
     }
}




FILE *get_permitted_file(filename, perm)
char *filename, *perm;
{
     FILE *fp;
     char prompt[BUFSIZ];
     char prompt2[BUFSIZ];     

     if (strcmp(perm, "w") == 0)
       strcpy(prompt, "WRITE> ");
     else
       strcpy(prompt, "READ> ");
     strcpy(prompt2, prompt);
     strcat(prompt2, "Filename? ");
     
     while (TRUE){
          if (! get_filename(prompt2, data_dir, filename))
	    return((FILE *)0);
	  
	  if (strcmp(perm, "w") == 0){
	       if (access(filename, W_OK) == 0){
		    fprintf(stdout, "%sFile exists. Overwrite? ", prompt);
		    fflush(stdout);
		    if (yes()){
			 if (fp  =  fopen(filename, "w"))
			   return(fp);
			 else
			   perror(filename);
		    }
		    continue;
	       }
	  }

	  if (directory_p(filename)) {
	       fprintf(stdout, "%s: is a directory\n", filename);
	       return((FILE *)0);
	  }

	  
	  if (fp = fopen(filename, perm)){
	       assert_filename(filename);
	       return(fp);
	  }
	  
	  else {
	       perror(filename);
	       return((FILE *)0);
       }
     }
}	       

     
     
BOOL yes()
{
       switch(select_char("yn")){
       case 'y':
	    fprintf(stdout, "Yes\n");
	    return(1);
       case 'n':
	    fprintf(stdout, "No\n");
	    return(0);
       default:
	    return(0); /* To keep sabertool happy */
       }
}


init_data_flow()
{
     data_flow.example_file = (char *)ALLOC(BUFSIZ * sizeof(char));
     data_flow.attribute_file = (char *)ALLOC(BUFSIZ * sizeof(char));
     data_flow.status = (unsigned short) 0;
}

init_rule_params()
{
     global_rule_parameters.example_file =
       (char *)ALLOC(BUFSIZ * sizeof(char));
     global_rule_parameters.time_stamp =
       (char *)ALLOC(BUFSIZ * sizeof(char));
}

     
void cn_help()
{
     fprintf(stdout, "Options:\n");
     fprintf(stdout, "   r: Read in data\n");
     fprintf(stdout, "   i: Induce rules\n");
     fprintf(stdout, "   w: Write rules to file\n");
     fprintf(stdout, "   c: Generate CKRL\n");                    
     fprintf(stdout, "   l: List current rules\n");     
     fprintf(stdout, "   x: Execute rules - i.e test them on (new) data\n\n");
     fprintf(stdout, "      Changing parameters\n");     
     fprintf(stdout, "      -------------------\n");
     fprintf(stdout, "   a: Algorithm\n");
     fprintf(stdout, "   e: Error estimate\n");               
     fprintf(stdout, "   s: Star size\n");
     fprintf(stdout, "   m: Maximum class forcing\n");     
     fprintf(stdout, "   t: Significance threshold (chi-squared) for accepting rules\n");
     fprintf(stdout, "   d: Display (amount of tracing info)\n");
     fprintf(stdout, "      -------------------\n");               
     fprintf(stdout, "   q: Quit\n");
     fprintf(stdout, "   h (or ?):  This message\n");
}

     
list_rules()
{
     FILE *fp;
     
     if (DATA_RULES){
	  fp = pager_open();
	  print_rule_list(fp, global_rule_list, HUMAN);	  
	  pager_close(fp);
     }
     else 
       fprintf(stdout, "No rules to list!\n");
}

     
     
     
     
     
