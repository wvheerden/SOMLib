/*  File:     reserved.h
    Author:   Robin Boswell
    Purpose:  CKRL keywords
*/ 

       /* SccsId = "@(#)reserved.h 5.2 9/25/91 MLT" */



/* Old version
char *reserved[]={
   "and", "deftarget", "or", 
   "begin", "descriptor", "ordered", 
   "boolean", "disjoint", "property", 
   "cardinal", "disjunct", "prototype", 
   "charac", "else", "range", 
   "ckrl", "end", "real", 
   "class", "eq", "relation", 
   "classref", "except", "relationref", 
   "concept", "false", "rule", 
   "default", "function", "ruleref", 
   "defblock", "ge", "self", 
   "defclass", "globalexcept", "single", 
   "defconcept", "gt", "sortref", 
   "defdisjointsets", "if", "string", 
   "deffacts", "instance", "subclass", 
   "deffunction", "integer", "subtype", 
   "definstance", "interval", "superclass", 
   "defmodifier", "le", "supervalue", 
   "defproperty", "lt", "then", 
   "defrelation", "modifier", "true", 
   "defrule", "nominal", "value", 
   "defsort", "nonordered", "when", 
   "not",
    0
 };     */
   
char *reserved[]={
   "and", "deftarget", "of",
   "begin", "descriptor", "or",
   "boolean", "disjoint", "ordered",
   "cardinal", "disjunct", "property",
   "charac", "else", "prototype",
   "ckrl", "end", "range",
   "class", "eq", "real",
   "classref", "except", "relation",
   "concept", "false", "relationref",
   "conceptref", "function", "rule",
   "default", "ge", "ruleref",
   "defblock", "globalexcept", "self",
   "defclass", "gt", "single",
   "defconcept", "if", "sortref",
   "defdisjointsets", "instance", "string",
   "deffacts", "integer", "subclass",
   "deffunction", "interval", "subtype",
   "definstance", "le", "superclass",
   "defmodifier", "lt", "supervalue",
   "defproperty", "modifier", "then",
   "defrelation", "ne", "true",
   "defrule", "nominal", "value",
   "defsort", "nonordered", "when",
   "not", 
   "NOTEQUAL", "NOSENSE", "DONTKNOW", "DONTCARE",
   0
};


