/*  File:     ingest.y
    Author:   Robin Boswell
    Purpose:  Parsing examples
*/ 

%{
static char *SccsId = "@(#)ingest.y 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

/* Parsing routines for RealID */

#include "mdep.h"

#include <stdio.h>
#include <strings.h>


#define _MC68881_
#include <math.h>

#include "cn_externs.h"

/* Other C declarations for example reading */

void attr_error(), print_att_value(), dc_error(), uk_error();
int number_of_errors;
EList example_list;
EList *e_ptr;
EList *ex_ptr_array;

List attribute_list, new_list, tree_att_list;
List *attr_ptr;

binary_action default_binary_flag, current_binary_flag;

Attribute *IDclass, *current_attr;

int att_num, number_of_attributes, number_of_classes;
BOOL ukdc_flag;
long number_of_examples;
int errflag, ex_errflag;
char temp[BUFSIZ];

/* Other C declarations for tree reading */

int att_val, count_index;

%}

%union{
	int ival;
	float fval;
	char *sval;
}

%token <sval> STRING
%token <ival> INTEGER_TOKEN
%token <fval> FLOAT_TOKEN
%token BOTH_FILE_HEADER ATTRIBUTE_FILE_HEADER
%token EXAMPLE_FILE_HEADER TREE_FILE_HEADER RULE_FILE_HEADER
%token ORDERED_RULE_TOKEN UNORDERED_RULE_TOKEN
%token BEFORE_TOKEN ORDERING_TOKEN
%token IF_TOKEN THEN_TOKEN AND_TOKEN ELSE_TOKEN DEFAULT_TOKEN
%token BINARY_TOKEN MULTIPLE_TOKEN
%token DONT_CARE UNKNOWN
%token FLOAT_TYPE INTEGER_TYPE SEPARATOR COLON EOE_CHAR
%token LEQ GE LE EQUALS
%token NULL_DECISION CLASH_DECISION
%token OPEN_PARENTHESIS CLOSE_PARENTHESIS
%token OPEN_BRACKET CLOSE_BRACKET
%token OPEN_SQUARE CLOSE_SQUARE
%token W_TOKEN  
%type  <ival> att_vals examples
%type  <ival> att_declarations
%%

input:
        { ln = 1; }
        input_file;
     
input_file:
             both_file
          |  attribute_file
          |  example_file
          |  rule_file
          |  rubbish;

  /* --------------- GRAMMAR FOR ATTS AND EXAMPLES FILE --------------- */  

both_file:
            BOTH_FILE_HEADER
              {
                if (input_type == ATTRIBUTES_AND_EXAMPLES){
		     fprintf(stdout,
			     "Reading attributes and examples...\n");
		}
		else {
		     input_type_error(ATTRIBUTES_AND_EXAMPLES);
   		     YYERROR;
		}
	      }
            attributes_etc
            SEPARATOR
            all_examples
            SEPARATOR
              { fprintf(stdout, "%d examples!\n", (int) number_of_examples);
                fprintf(stdout,
			"Finished reading attribute and example file!\n"); };



attribute_file:
            ATTRIBUTE_FILE_HEADER
             {
                if (input_type == ATTRIBUTES){
		     fprintf(stdout,
			     "Reading attributes...\n");
		}
		else {
		     input_type_error(ATTRIBUTES);
   		     YYERROR;
		}
	      }
            attributes_etc
              { fprintf(stdout, "Finished reading attribute file!\n");
	      };

example_file:
            EXAMPLE_FILE_HEADER
             {
                 if (input_type == EXAMPLES){
		     fprintf(stdout,
			     "Reading examples...\n");
		}
		else {
		     input_type_error(EXAMPLES);
   		     YYERROR;
		}
	      }
            all_examples
              { fprintf(stdout, "%d examples!\n", (int) number_of_examples);
                fprintf(stdout, "Finished reading example file!\n"); };


attributes_etc:
          all_attributes
              {
#ifdef DEBUG_INPUT
                fprintf(stdout, "No order declarations.\n"); 
#endif
	      }
      |   all_attributes
              {
#ifdef DEBUG_INPUT
                fprintf(stdout, "Order declarations....\n"); 
#endif
	      }  
          ORDERING_TOKEN
          attribute_ordering;

all_attributes:
           binary_flag
            {  errflag = FALSE;      
	       attribute_list = new_listelement();
	       attr_ptr = &attribute_list;
	       att_num = 0;}
           att_declarations
             { number_of_attributes = $3;  /* att_declarations */
#ifdef DEBUG_INPUT
	       fprintf(stdout, "I reckon there were %d attributes\n\n",
		                                      number_of_attributes);
#endif
	       FREE(*attr_ptr);
               (*attr_ptr) = (List)0;
   	       IDclass = (last(attribute_list)) -> head -> value;
	       if (ATT_TYPE(IDclass) == ORDERED_TYPE) 
		 num_class_error();
	       number_of_classes = N_VALUES(IDclass);
	       
	       if (errflag) {
		    fprintf(stdout, "Aborting parse.\n");
		    YYERROR;
	       }
	       else
		 setup_attribute_array();
	      };

/* No attributes */
all_attributes:
         {    fprintf(stdout, "ERROR: No attributes declarations\n");
	      fprintf(stdout, "Aborting parse.\n");
	      YYERROR;
	 };


binary_flag:
          OPEN_PARENTHESIS BINARY_TOKEN CLOSE_PARENTHESIS
                          {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "Default discrete split is binary\n");
#endif
		      default_binary_flag = TWOWAY; }
         | OPEN_PARENTHESIS MULTIPLE_TOKEN CLOSE_PARENTHESIS
                          {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "Default discrete split is multiple\n");
#endif
		      default_binary_flag = MULTIPLE; }
         |                {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "No default split declaration,\n");
	              fprintf(stdout, "so default will be multiple.\n");
#endif
	              default_binary_flag = MULTIPLE; };


all_examples:
             {  errflag = FALSE;
		ukdc_flag = FALSE;
	        example_list = new_elistelement();
	        e_ptr = &example_list;  }
           examples
             { (*e_ptr) = (EList)0;
	       number_of_examples = (long ) 1 + $2;    /* examples */
	       ex_ptr_array = (EList *) ALLOC((number_of_examples + 1)
					      * sizeof(EList));
               if (errflag) {
		    fprintf(stdout, "Aborting parse.\n");
		    YYERROR;
	       }
	      };

/* No examples */
all_examples:
         {    fprintf(stdout, "ERROR: No examples\n");
	      fprintf(stdout, "Aborting parse.\n");
	      YYERROR;
	 };


att_declarations:  /* Return the number of attributes */
           att_declarations
           att_declaration
		  {$$ = $1 + 1;}
         | att_declaration
                 { $$ = 1; };

att_declaration:
           STRING  COLON binary_att_flag
                   { value_list = new_listelement();
		     value_ptr = &value_list; }
          att_vals EOE_CHAR
                { ((*attr_ptr) -> head) = new_object();
#ifdef DEBUG_INPUT
                   fprintf(stdout, "\nAttribute:%s\n", $1);
#endif
                  ((*attr_ptr) -> head -> value) =       /* att_vals */  
   		    new_attribute(intern($1), DISCRETE_TYPE, 0, $5, value_list, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    current_binary_flag;
		  
		  (*attr_ptr) -> tail = new_listelement();
                  attr_ptr = &((*attr_ptr) -> tail); 
		  att_num++;
#ifdef DEBUG_INPUT
                   fprintf(stdout, "\n");
#endif
    	        }
        | STRING COLON  float_type
               {  ((*attr_ptr) -> head) = new_object();

#ifdef DEBUG_INPUT
                   fprintf(stdout, "\nAttribute:%s FLOAT\n", $1);
#endif		  
                  ((*attr_ptr) -> head -> value) =
		     new_attribute(intern($1), ORDERED_TYPE, REAL, 2, (List)NULL, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;  
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    MULTIPLE;
		  (*attr_ptr) -> tail = new_listelement();		  
                   attr_ptr = &((*attr_ptr) -> tail);
		   att_num++; }		  
        | STRING COLON  integer_type
   	       {  ((*attr_ptr) -> head) = new_object();
                  ((*attr_ptr) -> head -> value) =
  		     new_attribute(intern($1), ORDERED_TYPE, INTEGRAL, 2, (List)NULL, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    MULTIPLE;		  
		  (*attr_ptr) -> tail = new_listelement();		  
                   attr_ptr = &((*attr_ptr) -> tail);
		   att_num++; };
		 

binary_att_flag:
          OPEN_PARENTHESIS BINARY_TOKEN CLOSE_PARENTHESIS
             {
#ifdef DEBUG_INPUT
	          fprintf(stdout, "Binary split coming up...\n");
#endif
		  current_binary_flag = TWOWAY; }
       |  OPEN_PARENTHESIS MULTIPLE_TOKEN CLOSE_PARENTHESIS
             {
#ifdef DEBUG_INPUT
	          fprintf(stdout, "Multiple split coming up...\n");
#endif
		  current_binary_flag = MULTIPLE; }
       |  empty
             { current_binary_flag = default_binary_flag; };  

empty:
  ;                  

integer_type:
          OPEN_PARENTHESIS INTEGER_TYPE CLOSE_PARENTHESIS;

float_type:
          OPEN_PARENTHESIS FLOAT_TYPE   CLOSE_PARENTHESIS;
   
/* Returns the number of values */
att_vals:
            STRING
              {  add_att_val($1);
                 $$ = 1;
              }
          | att_vals STRING
              {  add_att_val($2);
                 $$ = $1 + 1;
              };

examples:
             example  {$$ = 0;} /* This gives the right answer! */
           | examples example {$$ = $1 + 1;};   


example:
		{ att_num = 0;
		  attr_ptr = &attribute_list;
	          current_attr = (Attribute *) (*attr_ptr) -> head -> value;
		  ex_errflag = FALSE; }
           example_values example_terminator
                { if (! (att_num == (number_of_attributes-1)))
		    attr_num_error(ln, att_num, number_of_attributes);
		  (*e_ptr)->next = new_elistelement();
	          e_ptr = &((*e_ptr) -> next);
#ifdef DEBUG_INPUT
		  fprintf(stdout, "\n");
#endif
	        };
		  

example_terminator:
           EOE_CHAR
               {(*e_ptr)->weight = 1.0;};
example_terminator:
           W_TOKEN INTEGER_TOKEN
           EOE_CHAR
               {(*e_ptr)->weight = (float) $2;}
       |   W_TOKEN FLOAT_TOKEN
           EOE_CHAR
               {(*e_ptr)->weight = $2;};
     

example_values:
                example_value
             |
 	        example_values
			{
			  if (att_num++ > (number_of_attributes - 2))
			    ex_errflag = TRUE;			     
			  if (! ex_errflag) {
			       attr_ptr = &((*attr_ptr) -> tail);
			       current_attr = (Attribute *)
				   (*attr_ptr) -> head -> value;
		          }
		     }
	       example_value;
			  


example_value:
           STRING  {if (! ex_errflag) {
		if (((current_attr ->atype) == DISCRETE_TYPE)
		     && value_id(intern($1), att_num,
				  (&(*e_ptr) -> values[att_num].d))){
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "%d:", att_num);
		     fprintf(stdout, "%s ", $1);
#endif
		    }
		      else
			attr_error(ln, att_num,$1);
 		    }
	           }
         | FLOAT_TOKEN   {if (! ex_errflag) {
	               if ((current_attr -> atype) == ORDERED_TYPE)
			 (*e_ptr) -> values[att_num].o = $1;
		       else {
			    sprintf(temp, "%f", $1);
			    attr_error(ln, att_num, temp);
		       }
		    }
                   }		   
         | INTEGER_TOKEN {if (! ex_errflag) {
	               if ((current_attr->atype) == ORDERED_TYPE){
#ifdef DEBUG_INPUT		     
			 fprintf(stdout, "%d:", att_num);
		         fprintf(stdout, "%d ", $1);
#endif			 
			 (*e_ptr) -> values[att_num].o = (float) $1;
		       }
		       else {
			    sprintf(temp, "%d", $1);		      
			    attr_error(ln, att_num, temp);
		       }
		    }
	           }
         | DONT_CARE {if (! ex_errflag) {
	               ukdc_flag = TRUE;
	               if (att_num == (number_of_attributes-1)) 
			      dc_error(ln);		       
	               switch (current_attr -> atype){
		       case ORDERED_TYPE:
			    (*e_ptr) -> values[att_num].o = DC_FLOAT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "DONT_CARE ");
#endif			    			    
			    break;
		       case DISCRETE_TYPE:
			    (*e_ptr) -> values[att_num].d = DC_INT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "DONT_CARE ");
#endif			    
			    break;
		       }
		    }
		 }
	 | UNKNOWN {if (! ex_errflag) {
	               if (att_num == (number_of_attributes-1)) 
			    uk_error(ln);	      
	               ukdc_flag = TRUE;	      
	               switch (current_attr -> atype){
		       case ORDERED_TYPE:
			    (*e_ptr) -> values[att_num].o = UK_FLOAT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "UNKNOWN ");
#endif			    			    
			    break;
		       case DISCRETE_TYPE:
			    (*e_ptr) -> values[att_num].d = UK_INT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "UNKNOWN ");
#endif			    			    
			    break;
		       }
		    }
	       };

  /* -------------------- ATTRIBUTE ORDERING -------------------- */    

attribute_ordering:
     { initialise_order_array(); }
  att_orders
     { transform_order_array(); };

att_orders:
     att_orders  
     att_order
   | att_order;

att_order:
     STRING BEFORE_TOKEN STRING EOE_CHAR
        {
#ifdef DEBUG_INPUT
	     fprintf(stdout, "%s before %s\n", $1, $3);
#endif	     
	     insert_order_array($1,$3);
	};

		    
  /* -------------------- GRAMMAR FOR RULE FILE -------------------- */    

rule_file:
        RULE_FILE_HEADER
              {
                if (input_type == RULES){
		     fprintf(stdout,
			     "Reading rules...\n");
		}
		else {
		     input_type_error(RULES);
   		     YYERROR;
		}
	      }
        root
              { fprintf(stdout, "Finished reading rules!\n"); };


root:
      SEPARATOR
   { init_rule_reader(); }
      rule_parameters
      SEPARATOR
      rule_type_declaration
      all_rules;

rule_type_declaration:
      ORDERED_RULE_TOKEN
  	       { algorithm_flag |= A_ORDERED;
#ifdef DEBUG_INPUT		     
		 fprintf(stdout, "Rules will be Ordered\n");
#endif
	    };

rule_type_declaration:
      UNORDERED_RULE_TOKEN
  	       { algorithm_flag &= ~A_ORDERED;
#ifdef DEBUG_INPUT		     
		 fprintf(stdout, "Rules will be Un-Ordered\n");
#endif
	    };


all_rules:
      rule_list
      default_rule
  |   empty_rule_list
      default_rule;

rule_list:
       rule
    |  rule_list rule;

empty_rule_list:
  ;

rule:
            { add_rule(); }
       IF_TOKEN
            {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "If ");
#endif
	    }
       premise
       THEN_TOKEN
            {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "Then ");
#endif
	    }
       conclusion
       rule_separator;

rule_separator:
     ELSE_TOKEN
  |  {  };



default_rule:
            {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "Default Rule:\n");
#endif
	    }
     OPEN_PARENTHESIS DEFAULT_TOKEN CLOSE_PARENTHESIS
            { add_rule(); }
     conclusion;




premise:
     condition
   | premise AND_TOKEN condition;
  
condition:
    att_string EQUALS STRING
          {
		if (((current_attr ->atype) == DISCRETE_TYPE)
		     && value_id(intern($3), att_num, &att_val)){
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "= %s\n ", $3);
#endif
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
		
		     (current_rule -> selector)[att_num].discriminant->attval =
                      att_val;
		     (current_rule -> selector)[att_num].setp =
		       TOTAL_INSTANTIATION;
		}
		      else
			attr_error(ln, att_num,$3);
          };


condition:
  att_string LE FLOAT_TOKEN
                 {
                     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));

		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = UPPER_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->upper = $3;
		     (current_rule -> selector)[att_num].setp = INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "< %.2f\n ", $3);
#endif
                 };
  
condition:
    att_string GE FLOAT_TOKEN
                  {
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
		      
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = LOWER_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->lower = $3;
		     (current_rule -> selector)[att_num].setp = INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "> %.2f\n ", $3);
#endif
                 };
  
  
condition:
   FLOAT_TOKEN LE att_string LE FLOAT_TOKEN
                   {
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
			
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = DOUBLE_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->upper = $5;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->lower = $1;		     
		     (current_rule -> selector)[att_num].setp =
		       TOTAL_INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "between %.2f and %.2f\n", $1, $5);
#endif
                 };

  
  
att_string:
   STRING
        {  if (current_attr = string_to_attribute($1)){
	     att_num = ATT_NO(current_attr);
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s ", $1);
#endif	     
        }
     else
       YYERROR;
       };

conclusion:
  STRING EQUALS STRING
        {
	     errflag |= ! value_id(string_to_atom($3),
				   ATT_NO(IDclass),
				   &(current_rule->class));
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s = %s\n ", $1, $3);
#endif	     	     
	};

conclusion:
  STRING EQUALS STRING
        {
	     errflag |= ! value_id(string_to_atom($3),
				   ATT_NO(IDclass),
				   &(current_rule->class));
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s = %s\n ", $1, $3);
#endif
	     current_rule->distribution = (double *) ALLOC(number_of_classes *
					  sizeof(double));
        }
         count_array;

count_array:
  OPEN_SQUARE {
#ifdef DEBUG_INPUT
                fprintf(stdout, "Found a count_array!\n");
		fflush(stdout);		
#endif       
                count_index = 0;
	      }
  count_numbers CLOSE_SQUARE;

count_numbers:
             count_number
           | count_numbers count_number;


count_number:
             INTEGER_TOKEN
             { current_rule->distribution[count_index++] = (double) $1;
#ifdef DEBUG_INPUT
                fprintf(stdout, "INTEGER ");
                fprintf(stdout, "Index %d, Count %f\n",
			count_index-1,
			current_rule->distribution[count_index-1]);
		fflush(stdout);	       
#endif
             };


count_number:
             FLOAT_TOKEN
             { current_rule->distribution[count_index++] = (double) $1;
#ifdef DEBUG_INPUT
                fprintf(stdout, "FLOAT %.2f  ", $1);	       
                fprintf(stdout, "Index %d, Count %f\n",
			count_index-1,
			current_rule->distribution[count_index-1]);
		fflush(stdout);	       
#endif
	     };  

  /* --------------------- RULE PARAMETERS --------------------- */

rule_parameters:
     rule_parameters
     rule_parameter
  |  rule_parameter;


rule_parameter:
     STRING
     COLON
     time_stamp;

rule_parameter:
     STRING
     COLON
     STRING
     { rule_par_sread($1, $3);};
rule_parameter:
     STRING
     COLON
     FLOAT_TOKEN
     { rule_par_fread($1, $3);};
rule_parameter:
     STRING
     COLON
     INTEGER_TOKEN
     { rule_par_nread($1, $3);};

time_stamp:
     OPEN_SQUARE
     weekday
     month
     day
     time
     year
     CLOSE_SQUARE;

weekday: STRING;
month:   STRING;
day:     INTEGER_TOKEN;
time:    INTEGER_TOKEN COLON INTEGER_TOKEN COLON INTEGER_TOKEN;
year:    INTEGER_TOKEN;


  /* ------------------------ RUBBISH ------------------------ */

rubbish: { input_type_error(ERROR);
	   YYERROR;};


%%

#include "lex.yy.c"
yywrap()
{
     return(1);
}


void attr_error(ln, att_num, entry)
long ln;
int att_num;
char *entry;
{    errflag = TRUE;
     fprintf(stdout, "ERROR: Inappropriate value for attribute ");
     fprintf(stdout, "%d\n", att_num);
     fprintf(stdout, " ->  %s\n", entry);          
     fprintf(stdout, "Line number: %ld\n", ln);
}

void dc_error(ln)
long ln;
{    errflag = TRUE;
     fprintf(stdout, "\nERROR: \"Don't Care\" is not a  permitted ");
     fprintf(stdout, "class value!\n");
     fprintf(stdout, "Line number: %ld\n", ln);
}

void uk_error(ln)
long ln;
{    errflag = TRUE;
     fprintf(stdout, "\nERROR: \"Unknown\" is not a permitted ");
     fprintf(stdout, "class value!\n");
     fprintf(stdout, "Line number: %ld\n", ln);
}


     
attr_num_error(ln, att_num, number_of_attributes)
long ln;
int att_num, number_of_attributes;
{
     errflag = TRUE;
     fprintf(stdout, "ERROR: Wrong number of attributes\n");
     fprintf(stdout, "Line number: %ld\n", ln);
     fprintf(stdout, "\tAttributes expected (including class): %d\n", number_of_attributes);
     fprintf(stdout, "\tAttributes found:                      %d\n", att_num+1);
}

     




/* Make into a #define
void print_att_value(stream, attno, value)
FILE *stream;
Attval value;
SHORT attno;
{
	switch (attribute[attno]->type)
	{
	case name:
		if (value.ivalue == UK_INT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%s ", id_value(value.ivalue, attno)->name);
		break;
	case ivalue:
		if (value.ivalue == UK_INT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%d ", value.ivalue);
		break;
	case fvalue:
		if (value.fvalue == UK_FLOAT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%5.1f ", value.fvalue);
		break;
	}
}
                                                                    */
input_type_error(type_found)
InputType type_found;
{
     fprintf(stdout,  "ERROR: wrong type of file\n");
     fprintf(stdout, "   Type expected: ");
     print_input_type(stdout, input_type);
     fprintf(stdout, "   Type found: ");
     print_input_type(stdout, type_found);
}


 
num_class_error()
{
     fprintf(stdout,
	     "ERROR: CN2 doesn't handle numeric classes.\n");
     fprintf(stdout,
	     "You must either discretise the class attribute, \n");
     fprintf(stdout,
	     "or use NewId instead.\n\n");
     errflag = TRUE;
}


