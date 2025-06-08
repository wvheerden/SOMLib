 
%{  
 /*  static char *SccsId = "@(#)ingest.l 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";  */
   char *stralloc();
   long ln;
%}

%%

^%.*$    { ; }            /* Ignore comment lines (but count line number) */
[ \t]    { ; }            /* Ignore white-space                           */
"\n"     { ln++; }

"FLOAT"                           {return(FLOAT_TYPE);}
"INT"                             {return(INTEGER_TYPE);}
"NULL"                            {return(NULL_DECISION);}
"CLASH"                           {return(CLASH_DECISION);}
"BINARY"                          {return(BINARY_TOKEN);}
"MULTIPLE"                        {return(MULTIPLE_TOKEN);}
"BEFORE"                          {return(BEFORE_TOKEN);}
"ORDERING"                          {return(ORDERING_TOKEN);}
"**ATTRIBUTE AND EXAMPLE FILE**"  {return(BOTH_FILE_HEADER);}
"**ATTRIBUTE FILE**"              {return(ATTRIBUTE_FILE_HEADER);}
"**EXAMPLE FILE**"                {return(EXAMPLE_FILE_HEADER);}
"**TREE FILE**"                   {return(TREE_FILE_HEADER);}
"**RULE FILE**"                   {return(RULE_FILE_HEADER);}
"*ORDERED-RULE-LIST*"             {return(ORDERED_RULE_TOKEN);}
"*UNORDERED-RULE-LIST*"           {return(UNORDERED_RULE_TOKEN);}
"AND"                             {return(AND_TOKEN);}
"DEFAULT"                         {return(DEFAULT_TOKEN);}
"ELSE"                            {return(ELSE_TOKEN);}
"THEN"                            {return(THEN_TOKEN);}
"IF"                              {return(IF_TOKEN);}
"<="                              {return(LEQ);}
">"                               {return(GE);}
"<"                               {return(LE);}
"?"                               {return(UNKNOWN);}
"*"                               {return(DONT_CARE);}
";"                               {return(EOE_CHAR);}
":"                               {return(COLON);}
^@                                {return(SEPARATOR);}
"="                               {return(EQUALS);}
"w"                               {return(W_TOKEN);}

"{"                               {return(OPEN_BRACKET);}
"}"                               {return(CLOSE_BRACKET);}
"("                               {return(OPEN_PARENTHESIS);}
")"                               {return(CLOSE_PARENTHESIS);}
"["                               {return(OPEN_SQUARE);}
"]"                               {return(CLOSE_SQUARE);}


[-+]?[0-9]*"."[0-9]+(E[+-]?[0-9]+)?           {
    sscanf(yytext, "%f", &(yylval.fval)); return(FLOAT_TOKEN);}
[-+]*[0-9]+                                   {
    sscanf(yytext, "%d", &(yylval.ival)); return(INTEGER_TOKEN);}

\"[^"\n]*\"                       {   /* A quoted string */
    yylval.sval = stralloc(yytext);               
    return(STRING);                               
    }

[a-zA-Z_]+[-.+a-zA-Z_0-9]*                     {  /* Strings now include */
    yylval.sval = stralloc(yytext);               /* "-" anywhere except */
    return(STRING);                               /* the first char      */
    }


%%

char *
stralloc(str)
char *str;
{
        char *s = (char *)malloc(strlen(str)+1);
        strcpy(s,str);
        return(s);
}

yyerror(str)
char *str;
{
        fprintf(stderr,"**** %s **** near line %ld.\n",str,ln);
}



