/*  File:     trace.c
    Author:   Robin Boswell
    Purpose:  
*/ 

static char *SccsId = "@(#)trace.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include <ctype.h>    /* for isprint() */
#include <strings.h>
#include <string.h>
#include "mdep.h"
#include "cn_externs.h"

#define RH_COL_INDENT 4
#define MAX_TRACE_OPTS 20


char display[MAX_TRACE_OPTS][BUFSIZ];

unsigned short trace_flag;
unsigned short algorithm_flag;
unsigned short max_class_flag;
Ranking errest_flag;

void change_tracing()
{
     BOOL exit = FALSE;
     
     while (! exit){
	  fprintf(stdout, "SET TRACE FLAGS> ");
	  fflush(stdout);
	  switch (select_char("andpscbuk.h?eqr\n")) {
	  case 'a':
	       fprintf(stdout, "All\n");
	       fprintf(stdout, "  All tracing is now turned ON\n"); 
	       trace_flag |= T_ALL;
	       break;
	  case 'n':
	       fprintf(stdout, "None\n");
	       fprintf(stdout, "  All tracing is now turned OFF\n");   
	       trace_flag &= T_NONE;
	       break;
	  case 'd':
	       fprintf(stdout, "Default\n");
	       fprintf(stdout, "  Tracing is set to the default values\n");
	       trace_flag = DEFAULT_TRACING;
	       break;
	  case '.':
	       fprintf(stdout, ". printing ");
	       if (TRACE_DOTS) {
		    trace_flag &=  ~T_DOTS;
		    fprintf(stdout, "OFF\n   No longer printing dots\n");
	       }
	       else {
		    trace_flag |=  T_DOTS;
		    fprintf(stdout,
			    "ON\n   Will print lots of dots while inducing rules\n");
	       }
	       break;	       
	  case 'p':
	       fprintf(stdout, "Print\n");	       	       	       
	       display_tracing();
	       break;
	  case 's':
	       fprintf(stdout, "Star ");
	       if (TRACE_PRINT_STAR) {
		    trace_flag &=  ~T_PRINT_STAR;
		    fprintf(stdout, "OFF\n   No longer printing the star\n");
	       }
	       else {
		    trace_flag |=  T_PRINT_STAR;
		    fprintf(stdout,
			    "ON\n   Will print the star after each iteration\n");
	       }
	       break;	       
	  case 'c':
	       fprintf(stdout, "Current ");
	       if (TRACE_CURRENT_NODE) {
		    trace_flag &=  ~T_CURRENT_NODE;
		    fprintf(stdout,
			    "OFF\n   No longer printing the current_node\n");
	       }
	       else {
		    trace_flag |=  T_CURRENT_NODE;
		    fprintf(stdout,
			    "ON\n   Will print the node being specialised\n");
	       }	       
	       break;	       
	  case 'b':
	       fprintf(stdout, "Best ");
	       if (TRACE_BEST_UPDATE) {
		    trace_flag &=  ~T_BEST_UPDATE;
		    fprintf(stdout,
			    "OFF\n   No longer notifying updates of best node\n");
	       }
	       else {
		    trace_flag |=  T_BEST_UPDATE;
		    fprintf(stdout,
			    "ON\n   Will tell you whenever the best node is updated\n");
	       }	       
	       break;
	  case 'r':
	       fprintf(stdout, "Rule ");
	       if (TRACE_RULE) {
		    trace_flag &=  ~T_RULE;
		    fprintf(stdout,
			    "OFF\n   No longer displaying the best rule at each iteration\n");
	       }
	       else {
		    trace_flag |=  T_RULE;
		    fprintf(stdout,
			    "ON\n   Will display the best rule at each iteration\n");
	       }	       
	       break;	       
	  case 'u':
	       fprintf(stdout, "Useless ");
	       if (TRACE_USELESS) {
		    trace_flag &=  ~T_USELESS;
		    fprintf(stdout,
			    "OFF\n   No longer notifying rejection of useless nodes\n");
	       }
	       else {
		    trace_flag |=  T_USELESS;
		    fprintf(stdout,
			    "ON\n   Will display rejection of useless nodes\n");
	       }	       
	       break;	       
	  case 'k':
	       fprintf(stdout, "Class ");
	       if (TRACE_CLASS) {
		    trace_flag &=  ~T_CLASS;
		    fprintf(stdout,
			    "OFF\n   No longer notifying rejection of useless nodes\n");
	       }
	       else {
		    trace_flag |=  T_CLASS;
		    fprintf(stdout,
			    "ON\n   Will display rejection of useless nodes\n");
	       }	       
	       break;	       
	       
  	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");	       
	       help_tracing();
	       break;	       
	  default:
	       fprintf(stdout, "Returning to top level...\n");	       	       
	       exit = TRUE;
	       break;	       
	  }
     }
}

display_tracing()
{

     BOOL don = FALSE, doff = FALSE;
     int s = BUFSIZ / 2;
     int i_on = 0, i_off = 0;
     int i2_on = 0, i2_off = 0;
     register int i, j;

     for (i=0; i < MAX_TRACE_OPTS; ++i){
	  for (j=0; j < BUFSIZ; ++j)
	    display[i][j] = (char)0;
     }
     
     if (TRACE_PRINT_STAR)
       strcpy(display[i_on++], "PRINT_STAR is ON.");
     else {
	  strcpy(display[i_off++]+s, "PRINT_STAR is OFF.");
     }
     
     if (TRACE_BEST_UPDATE)
       strcpy(display[i_on++], "BEST_UPDATE is ON.");
     else {
	  strcpy(display[i_off++]+s, "BEST_UPDATE is OFF.");
     }
     
     if (TRACE_CURRENT_NODE)
       strcpy(display[i_on++], "CURRENT_NODE is ON.");
     else {
	  strcpy(display[i_off++]+s, "CURRENT_NODE is OFF.");
     }
     
     if (TRACE_RULE)
       strcpy(display[i_on++], "RULE is ON.");
     else {
	  strcpy(display[i_off++]+s, "RULE is OFF.");
     }
     
     if (TRACE_USELESS)
       strcpy(display[i_on++], "USELESS is ON.");
     else {
	  strcpy(display[i_off++]+s, "USELESS is OFF.");
     }
     
     if (TRACE_CLASS)
       strcpy(display[i_on++], "CLASS is ON.");
     else {
	  strcpy(display[i_off++]+s, "CLASS is OFF.");
     }

     if (TRACE_DOTS)
       strcpy(display[i_on++], "DOTS is ON.");
     else {
	  strcpy(display[i_off++]+s, "DOTS is OFF.");
     }

     strcpy(display[i_on++], "");
     strcpy(display[i_off++]+s, "");     

     i2_on = i2_off = 0;
     while (! (don && doff)){  
	  fprintf(stdout, "   %-25s", display[i2_on]);
	  fprintf(stdout, "%-30s\n", display[i2_off]+s);
	  if (i2_on < i_on)
	    ++i2_on;
	  else
	    don = TRUE;
	  if (i2_off < i_off)
	    ++i2_off;
	  else
	    doff = TRUE;
     }
     
     
}


help_tracing()
{
     fprintf(stdout, "   a: All tracing on\n");
     fprintf(stdout, "   n: No tracing\n");
     fprintf(stdout, "   d: Default tracing\n");          
     fprintf(stdout, "   p: Print the current status of tracing\n\n");
     fprintf(stdout, "      The following are all toggles:\n");
     fprintf(stdout, "      -----------------------------\n");
     fprintf(stdout, "   .: DOTS - print dots while inducing\n");
     fprintf(stdout, "   r: RULE - print each rule as it is chosen\n");     
     fprintf(stdout, "   s: STAR - display the star after each iteration\n");
     fprintf(stdout, "   k: KLASS (Unordered mode) - display current class\n");
     fprintf(stdout, "   c: CURRENT - say which node is being specialised\n");
     fprintf(stdout, "   b: BEST - display updates to the best node\n");
     fprintf(stdout, "   u: USELESS - say which nodes are being rejected\n\n");
}

     
     

void change_threshold()
{

     char buffer[BUFSIZ];
     float tmp;
     int c;
     int i=0;
     
     fprintf(stdout, "Current threshold is %.2f\n", threshold);
     fprintf(stdout, "New threshold: ");
     fflush(stdout);
     while ((c = getchar()) != '\n'  && i < (BUFSIZ-1)){
	  if (isprint(c))
	    buffer[i++] = (char) c;
     }

     if (i == 0) {
	  fprintf(stdout, "(No change)\n");       
	  return;
     }

     buffer[i] = (char)0;

     if (ishelp(buffer[0])){
	  help_threshold();
	  change_threshold();
	  return;
     }
     
     if (sscanf(buffer, "%f", &tmp) == 1 && tmp >= 0) {
	  fprintf(stdout, "OK!\n");       
	  threshold = tmp;
     }
     else
       fprintf(stdout, "Invalid input - cutoff threshold.\n");
     
}     


void change_starsize()
{
     char buffer[BUFSIZ];
     int tmp;
     int c;
     int i=0;
     BOOL errflag = FALSE;
     
     fprintf(stdout, "Current star size is %d\n", star_size);
     fprintf(stdout, "New star size: ");
     fflush(stdout);
     while ((c = getchar()) != '\n'  && i < (BUFSIZ-1)){
	  if (c == '.')
	    errflag = TRUE;
	  if (isprint(c))
	    buffer[i++] = (char) c;
     }
     
     if (i == 0) {
	  fprintf(stdout, "(No change)\n");       
	  return;
     }
     
     buffer[i] = (char)0;

     if (ishelp(buffer[0])){
	  help_starsize();
	  change_starsize();
	  return;
     }
     
     if ((! errflag) && sscanf(buffer, "%d", &tmp) == 1) {
	  if (tmp < 0) {
	       fprintf(stdout,
		       "You feel a wrenching sensation as the Universe turns\n");
	       fprintf(stdout,
		       "inside out around you... \n");
	       fprintf(stdout,
		       "When you wake up, everything seems back-to-front, but\n");
	       fprintf(stdout,
		       "the star size is still %d\n", star_size);
	       
	  }
	  else if (tmp == 0) {
	       fprintf(stdout, "Very restful, but not much use.\n");
	       fprintf(stdout, "Star size unchanged.\n");
	  }
	  else if (tmp > 200) {
	       fprintf(stdout, "The engines wi'nae take it, Capt'n.\n");
	       fprintf(stdout, "Star size unchanged.\n");
	  }
	  else {
	       fprintf(stdout, "OK!\n");       	    
	       star_size = tmp;
	  }
     }
     else
       fprintf(stdout, "Invalid input - star size unchanged.\n");
}     


void change_algorithm()
{
     BOOL exit = FALSE;
     
     if (ORDERED)
       fprintf(stdout, "Algorithm is currently set to ORDERED\n");
     else
       fprintf(stdout, "Algorithm is currently set to UN_ORDERED\n"); 

     while (! exit){
	  fprintf(stdout, "ALGORITHM> ");
	  fflush(stdout);
	  switch (select_char("oueqh?\n")) {
	  case 'o':
	       fprintf(stdout, "Ordered\n");
	       fprintf(stdout, "  CN will produce an ordered rule set\n");
	       algorithm_flag |= A_ORDERED;
	       exit = TRUE;
	       break;
	  case 'u':
	       fprintf(stdout, "Unordered\n");
	       fprintf(stdout,
		       "  CN will produce an unordered rule set\n");
	       algorithm_flag &= ~A_ORDERED;
	       if (ENTROPIC(errest_flag)) {
		    errest_flag = LAPLACIAN;
		    fprintf(stdout,
		       "*NOTE*  Error estimate is now set to \"LAPLACIAN\".\n");
	       }
	       exit = TRUE;	       
	       break;
  	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");	       
	       help_algorithm();
	       break;	       
	  default:
	       fprintf(stdout, "Returning to top level...\n");	       	       
	       exit = TRUE;
	       break;	       
	  }
     }
}


void change_maxclass()
{
     BOOL exit = FALSE;
     
     if (max_class_flag)
       fprintf(stdout, "Maximum class prediction is currently SET\n");
     else
       fprintf(stdout, "Maximum class prediction is currently UNSET\n");

     while (! exit){
	  fprintf(stdout, "MAX_CLASS> ");
	  fflush(stdout);
	  switch (select_char("suh?\n")) {
	  case 's':
	       fprintf(stdout, "Set\n");
	       fprintf(stdout, "  Max class prediction is now SET\n");
	       max_class_flag = TRUE;
	       exit = TRUE;
	       break;
	  case 'u':
	       fprintf(stdout, "Unset\n");
	       fprintf(stdout, "  Max class prediction is now UNSET\n");
	       max_class_flag = FALSE;
	       exit = TRUE;	       
	       break;
  	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");	       
	       help_maxclass();
	       break;	       
	  default:
	       fprintf(stdout, "Returning to top level...\n");	       	       
	       exit = TRUE;
	       break;	       
	  }
     }
}



     
help_maxclass()
{
     fprintf(stdout,
     "Setting \"maximum class prediction\" causes CN2 to reject any rules\n");
     fprintf(stdout,
     "for which the maximum count does not correspond to the class predicted\n");
     fprintf(stdout,
     "(So it only affects ordered rule-sets)\n\n");
     fprintf(stdout,
     "Options are:\n");
     fprintf(stdout, "   s: Set\n");
     fprintf(stdout, "   u: Unset\n");
     fprintf(stdout, "   h: Help\n");
     fprintf(stdout, "   e/q/<ret>: Return to top level\n");
}



     
help_algorithm()
{
     fprintf(stdout, "   o: Ordered\n");
     fprintf(stdout, "   u: Un-ordered\n");
     fprintf(stdout, "   h: Help\n");
     fprintf(stdout, "   e/q/<ret>: Return to top level\n");
}


void change_errest()
{
     BOOL exit = FALSE;

     switch(errest_flag) {
     case LAPLACIAN:
	  fprintf(stdout, "Error estimate is currently set to LAPLACIAN\n");
	  break;
     case NAIVE:
	  fprintf(stdout, "Error estimate is currently set to NAIVE\n");
	  break;
     case ENTROPY:
	  fprintf(stdout, "Error estimate is currently set to ENTROPY\n");
	  break;
     case ENTROPY2:
	  fprintf(stdout,
		  "Error estimate is currently set to MODIFIED ENTROPY\n");
	  break;	  
     }
     

     while (! exit){
	  fprintf(stdout, "ERROR_ESTIMATE> ");
	  fflush(stdout);
	  switch (select_char("lneimqh?\n")) {
	  case 'l':
	       fprintf(stdout, "Laplacian\n");
	       errest_flag = LAPLACIAN;
	       exit = TRUE;
	       break;
	  case 'n':
	       fprintf(stdout, "Naive\n");
	       errest_flag = NAIVE;
	       exit = TRUE;	       
	       break;
	  case 'i':
	       fprintf(stdout, "Information (entropy)\n");
	       if (! ORDERED) {
		    algorithm_flag |= A_ORDERED;
		    fprintf(stdout,
			    "*NOTE*  Algorithm now set to \"ordered\".\n");
	       }
	       errest_flag = ENTROPY;
	       exit = TRUE;
	       break;
	  case 'm':
	       fprintf(stdout, "Modified entropy\n");
	       if (! ORDERED) {
		    algorithm_flag |= A_ORDERED;
		    fprintf(stdout,
			    "*NOTE*  Algorithm now set to \"ordered\".\n");
	       }
	       errest_flag = ENTROPY2;
	       exit = TRUE;
	       break;	       
  	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");
	       help_errest();
	       break;	       
	  default:
	       fprintf(stdout, "Returning to top level...\n"); 
	       exit = TRUE;
	       break;	       
	  }
     }
}

     
help_errest()
{
     fprintf(stdout, "   l: Laplacian\n");
     fprintf(stdout, "   n: Naive\n");
     fprintf(stdout, "   i: Information (Entropy)\n");
     fprintf(stdout, "   m: Modified entropy\n");          
     fprintf(stdout, "   h: Help\n");
     fprintf(stdout, "   e/q/<ret>: Return to top level\n");
}

help_threshold()
{
     fprintf(stdout,
	     "   The chi-squared significance threshold is a statistical criterion \n");
     fprintf(stdout,
	     "   for acceptability of a rule.\n");
     fprintf(stdout,
	     "   (The higher the value, the fewer rules will be produced).\n");
     fprintf(stdout,
	     "   Its value must be a real number >= 0 \n");
}

help_starsize()
{
     fprintf(stdout, "   The star size is the width of CN2's beam search.\n");
     fprintf(stdout, "   Its value must be a positive integer >= 1\n");
}


set_rule_parameters()
{
     strcpy(global_rule_parameters.example_file,
	    data_flow.example_file);
     clockin(global_rule_parameters.time_stamp);
     global_rule_parameters.algorithm = algorithm_flag;
     global_rule_parameters.errest = errest_flag;     
     global_rule_parameters.threshold = threshold;
     global_rule_parameters.star_size = star_size;          
}


BOOL ishelp(c)
char c;
{
     if (c == '?' || c == 'h' || c == 'H')
       return(TRUE);
     else
       return(FALSE);       
}
