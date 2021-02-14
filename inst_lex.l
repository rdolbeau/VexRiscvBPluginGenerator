%{
/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */
#include <stdio.h>
#include <stdlib.h>
#include "inst_par.h"
%}

CHAR            [[:alnum:] ,'&./()-]
FCHARNAME       [[:alpha:]]
CHARNAME        [[:alnum:]_+-]
SPACE           [ \t]

%%

^"I"                             { return INST; }

^"S"                             { return SEM; }

^"T"                             { return MEMSEM; }

^"P"                             { return PROL; }

^"E"                             { return EXTRA; }

"//".*                           { }

{FCHARNAME}{CHARNAME}{CHARNAME}* { yylval.string = strdup(yytext); return NAME; }

{CHARNAME}{32}                   { yylval.string = strdup(yytext); return NAME; }


"\"\"\""[^ù]*"\"\"\""            { yylval.string = strndup(yytext+3, strlen(yytext)-6); return STRING; }

"'''"[^ù]*"'''"                  { yylval.string = strndup(yytext+3, strlen(yytext)-6); return STRING; }

"\"".*"\""                       { yylval.string = strndup(yytext+1, strlen(yytext)-2); return STRING; }

[0-9][0-9]*                      { yylval.num = atoi(yytext); return NUM; }

\n                               { return yytext[0]; }

{SPACE}+                         { }

%%
