%{
 
/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "Expression.h"
#include "Parser.h"

#include <stdio.h>

int colnum = 0;
#define YY_USER_ACTION {yylloc->first_line = yylineno; \
        yylloc->first_column = colnum;                 \
        colnum=colnum+yyleng;                         \
        yylloc->last_column=colnum;                    \
        yylloc->last_line = yylineno;}

%}
%option yylineno
%option bison-locations
%option warn nodefault
 
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

KEYWORD     "int"
IDENTIFIER  [a-zA-Z][a-zA-Z0-9]*
LPAREN      "("
RPAREN      ")"
PLUS        "+"
MULTIPLY    "*"
 
NUMBER      [0-9]+
WS          [ \r\n\t]*
 
%%
 
{WS}            { /* Skip blanks. */ }
{NUMBER}        { sscanf(yytext, "%d", &yylval->value); return TOKEN_NUMBER; }
 
{MULTIPLY}      { return TOKEN_MULTIPLY; }
{PLUS}          { return TOKEN_PLUS; }
{LPAREN}        { return TOKEN_LPAREN; }
{RPAREN}        { return TOKEN_RPAREN; }
.               {  }
 
%%
 
//int yyerror(const char *msg) {
//    fprintf(stderr,"Error:%s\n",msg); return 0;
//}