%{
/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1
#include "gen_plugin.hpp"
%}

%union
{
  char* string;
}

%token <string> NAME
%token <string> STRING

%token INST
%token SEM
%token PROL
%token EXTRA


%%
input:      /* empty */ {  }
|  pattern input        {  }
;
pattern:
INST NAME NAME NAME NAME                        { /* printf("0 - %s\n", $2); */ add_inst0($2, $3, $4, $5); }
|  INST NAME NAME NAME NAME NAME                { /* printf("1 - %s\n", $2); */ add_inst1($2, $3, $4, $5, $6); }
|  INST NAME NAME NAME NAME NAME NAME           { /* printf("2 - %s\n", $2); */ add_inst2($2, $3, $4, $5, $6, $7); }
|  INST NAME NAME NAME NAME NAME NAME NAME      { /* printf("3 - %s\n", $2); */ add_inst3($2, $3, $4, $5, $6, $7, $8); }
|  INST NAME NAME NAME NAME NAME NAME NAME NAME { /* printf("4 - %s\n", $2); */ add_inst4($2, $3, $4, $5, $6, $7, $8, $9); }
|  SEM  NAME STRING { add_sem($2, $3); }
|  PROL STRING { add_prol($2); }
|  EXTRA STRING { add_extra($2); }
| '\n'
;
%%

int
yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
  return(0);
}

int
yywrap(void)
{
  return(-1);
}
