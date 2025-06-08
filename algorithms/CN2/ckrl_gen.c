/*  File:     ckrl_gen.c
    Author:   Robin Boswell
    Purpose:  Generate ckrl
*/ 

static char *SccsId = "@(#)ckrl_gen.c 5.3 9/27/91 MLT"; 

#include <string.h>
#include <stdio.h>
#include "mdep.h"
#include "cn_externs.h"
#include "reserved.h"

BOOL printing_rules;

int ckrl_mode()
{
     BOOL exit = FALSE;
     
     while (! exit){
	  fprintf(stdout, "GENERATE CKRL> ");
	  fflush(stdout);
	  switch (select_char("at?qrh\n")) {
	  case 'a':
	       fprintf(stdout, "Attributes and Examples\n");
	       printing_rules = FALSE;
	       ckrl_ae();
	       break;
	  case 'r':
	       fprintf(stdout, "Rules\n");
	       printing_rules = TRUE;	       
	       ckrl_rules();
	       break;
  	  case 'h':
	  case '?':
	       fprintf(stdout, "Help\n");	       
	       help_ckrl();
	       break;	       
	  default:
	       fprintf(stdout, "Returning to top level...\n");	       	       
	       exit = TRUE;
	       break;	       
	  }
     }
}


help_ckrl()
{
     fprintf(stdout, "  CKRL GENERATION MODE\n\n");
     fprintf(stdout, "      a: Attributes and Examples\n");
     fprintf(stdout, "      r: Rules\n");
     fprintf(stdout, "      h: This help message\n");
     fprintf(stdout, "<RET>/r: Return to top level\n\n");
     fprintf(stdout, "  Note: It doesn't make sense to print examples and attributes separately\n");
     fprintf(stdout, "  in CKRL. \n");
}


ckrl_rules()
{
     char filename[BUFSIZ];
     FILE *fp;

     if (D_RULES & data_flow.status){
	  if (! (fp = get_permitted_file(filename, "w")))
	    return(0);

	  fprintf(stdout, "Writing rules in CKRL to %s...\n", filename);

	  ckrl_rules2(fp);
	  
	  fclose(fp);
	  fprintf(stdout, "Done..\n");
	  return(1);
     }
     else
       fprintf(stderr, "No rules to convert!\n");
     return(0);
}


ckrl_rules2(fp)
FILE *fp;
{
     
     ckrl_rules_header(fp); 
     ckrl_header(fp);	  
     ckrl_attributes(fp);
     ckrl_attributes_end(fp);
     print_ckrl_nominal(fp, "deftarget %s;\n\n", IDclass->aname->name);	  
     ckrl_print_rules(fp, global_rule_list);
     ckrl_rules_footer(fp);  
}




ckrl_ae()
{
     char filename[BUFSIZ];
     FILE *fp;
     
     if (DATA_BOTH){
	  if (! (fp = get_permitted_file(filename, "w")))
	    return(0);

	  fprintf(stdout, "Writing attributes and examples in CKRL to %s...\n", filename);
	  ckrl_ae2(fp);
	  fclose(fp);
	  fprintf(stdout, "Done..\n");
	  return(1);
     }
     else {
	  if (! DATA_ATTRIBUTES)
	    fprintf(stderr, "No data!\n");
	  else
	    fprintf(stderr, "No current examples\n");
	  return(0);
     }
}



ckrl_ae2(fp)
FILE *fp;
{
     ckrl_header(fp);
     ckrl_attributes(fp);
     ckrl_examples(fp);
     ckrl_footer(fp);
}


ckrl_header(fp)
FILE *fp;
{
     char buffer[BUFSIZ];
     root_name(data_flow.example_file, buffer);
     fprintf(fp, "ckrl begin\n\n");
     fprintf(fp, "defclass %s\n", buffer);
}

ckrl_attributes(fp)
FILE *fp;
{
     int i;
     Attribute *attribute;
     
     for (i = 0; i < number_of_attributes; ++i){
	  switch(ATT_TYPE(attribute = nth_attribute(i))){
	  case DISCRETE_TYPE:
	       ckrl_disc_att(fp, attribute);
	       break;
	  case ORDERED_TYPE:
	       ckrl_ord_att(fp, attribute);	       
	       break;       
	  }
     }
}

ckrl_disc_att(fp, attribute)
FILE *fp;
Attribute *attribute;
{
     print_ckrl_nominal(fp,
	 "   property (%s (range (nominal (", attribute->aname->name);
     {
	  int i;
	  for (i = 0; i < N_VALUES(attribute); ++i){
	       print_ckrl_nominal(fp, "%s", val_string(A_VALUES(attribute), i));
	       if (i < N_VALUES(attribute) - 1)
		 fprintf(fp, ", ");
	  }
     }
     fprintf(fp, "))))\n");
}


ckrl_ord_att(fp, attribute)
FILE *fp;
Attribute *attribute;
{
     
     print_ckrl_nominal(fp,
	 "   property (%s (range ", attribute->aname->name);
     switch (ATT_NTYPE(attribute)){
     case INTEGRAL:
	  fprintf(fp, "(integer ");
	  break;
     case REAL:
	  fprintf(fp, "(real ");	  
	  break;
     }
                           /* Used to declare range as (*:*), but now
				 omit it altogether */
     fprintf(fp, ")))\n");     
}


ckrl_attributes_end(fp)
FILE *fp;
{
     if (printing_rules)
       ckrl_pseudo_attribute(fp);
     fprintf(fp, ";\n\n");
}

ckrl_pseudo_attribute(fp)
FILE *fp;
{
     fprintf(fp, "   property (covered_by_rule (range (boolean)))");
}


ckrl_examples(fp)
FILE *fp;
{
     EList examples = example_list;
     Value *values;
     Attribute *attribute;
     int e_number, knownp;
     char buffer[BUFSIZ];
     char buffer2[BUFSIZ];     
     

     fprintf(fp, "   instance (\n");
     for (e_number = 1; examples;  examples = E_NEXT(examples), ++e_number){
	  int i;
	  values = examples->values;
	  
	  fprintf(fp, "     e%d (", e_number);
	  
	  for (i = 0; i < number_of_attributes; ++i){
	       attribute = nth_attribute(i);
	       sprint_ckrl_nominal(buffer, "%s ", attribute->aname->name);
	       ckrl_att_val(buffer2, attribute, i, values);
         /* Used not to print unknowns - now do */
	       fprintf(fp, "%s%s", buffer, buffer2);		    
		 
	       if (i == number_of_attributes - 1) {
		      if (e_number == number_of_examples)
			fprintf(fp, ")\n");
		      else
			fprintf(fp, "),\n");		      
		 }
	       else 
		 fprintf(fp, ", ");
	  }
     }
     fprintf(fp, "   );\n\n");
}


int ckrl_att_val(buffer, attribute, att_no, values)
char *buffer;
Attribute *attribute;
int att_no;
Value *values;
{
     Type type = ATT_TYPE(attribute);
     Value value;
     int success = TRUE;

     switch(type) {
     case DISCRETE_TYPE:
	  value.d = values[att_no].d;
	  if (D_DC(value.d))
            sprintf(buffer, "DONTCARE");
          else if (D_UNK(value.d)){
	       sprintf(buffer, "DONTKNOW");	    
	       success = FALSE;
	  }
	  
          else
            sprint_ckrl_nominal(buffer, "%s", att_val_string(att_no, value.d));
          break;
     case ORDERED_TYPE:
	  value.o = values[att_no].o;
          if (O_DC(value.o))
            sprintf(buffer, "DONTCARE");
          else if (O_UNK(value.o)) {
	       sprintf(buffer, "DONTKNOW");	    	    
	       success = FALSE;
	  }
          else  
            switch (ATT_NTYPE(attribute)){
            case INTEGRAL:
                 sprintf(buffer, "%d", (int) value.o);              
                 break;
            case REAL:
                 sprintf(buffer, "%.2f", value.o);
                 break;
            }
	  break;
     }
     return(success);
}



ckrl_footer(fp)
FILE *fp;
{
     print_ckrl_nominal(fp, "deftarget %s;\n\n", IDclass->aname->name);
     fprintf(fp, "ckrl end\n");
}

root_name(in, out)
char *in, *out;
{
     char c;
     while ((c = *in++) && (c != '.') && (c != ':'))
       *out++ = c;
     *out = (char)0;
}


/* Print string, with appropriate modification and warning if it's
   a reserved word */
sprint_ckrl_nominal(buffer, control, string)
char *buffer;
char *control, *string;
{
     char **ptr = reserved;
     int match = FALSE;
     char tmp[BUFSIZ];

     if (string[0] == '"'){     /* Check if quoted */
	  int l = strlen(string);
	  strcpy(tmp, string);
	  tmp[0] = tmp[l-1] = 'S';
	  sprintf(buffer, control, tmp);     	  
     }
     else {
	  while (*ptr) {          /* Check if reserved */
	       if (strcmp(*ptr++, string) == 0){
		    match = TRUE;
		    break;
	       }
	  }
	  if (match){
	       strcpy(tmp, string);
	       strcat(tmp, "D");
	       sprintf(buffer, control, tmp);	  
	  }
	  else
	    sprintf(buffer, control, string);
     }
}



print_ckrl_nominal(fp, control, string)
FILE *fp;
char *control, *string;
{
     char buffer[BUFSIZ];
     sprint_ckrl_nominal(buffer, control, string);
     fprintf(fp, "%s", buffer);
}
