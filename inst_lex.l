%{
/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */
#include <stdio.h>
#include "inst_par.h"
%}

CHAR            [[:alnum:] ,'&./()-]
CHARNAME        [[:alnum:]_+-]
SPACE           [ \t]

%%

^"I"                          { return INST; }

^"S"                          { return SEM; }

^"P"                          { return PROL; }

"//".*                       { }

{CHARNAME}{CHARNAME}{CHARNAME}*      { yylval.string = strdup(yytext); return NAME; }

"\"\"\""[^ù]*"\"\"\""      { yylval.string = strndup(yytext+3, strlen(yytext)-6); return STRING; }

"\"".*"\""      { yylval.string = strndup(yytext+1, strlen(yytext)-2); return STRING; }

\n                         { return yytext[0]; }

{SPACE}+                   { }

%%
