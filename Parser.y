%{
 
/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */
 
#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"
 
int yyerror(YYLTYPE *l, SExpression **expression, yyscan_t scanner, const char *msg) {
    // Add error handling routine as needed
}
 
%}
%locations

%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 
}
 
%output  "Parser.c"
%defines "Parser.h"
 
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }
 
%union {
    int value;
    SExpression *expression;
}
 
%left '+' TOKEN_PLUS
%left '*' TOKEN_MULTIPLY
 
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_PLUS
%token TOKEN_MULTIPLY
%token <value> TOKEN_NUMBER
 
%type <expression> expr
 
%%
 
input
    : expr { *expression = $1; }
    ;
 
expr
    : expr[L] TOKEN_PLUS expr[R]        { $$ = createOperation( ePLUS,        $L, 0,  $R, @1.first_column, @3.last_column ); }
    | expr[L] TOKEN_MULTIPLY expr[R]    { $$ = createOperation( eMULTIPLY,    $L, 0,  $R, @1.first_column, @3.last_column ); }
    | TOKEN_LPAREN expr[C] TOKEN_RPAREN { $$ = createOperation( ePARENTHESES, 0,  $C, 0,  @1.first_column, @3.last_column ); }
    | TOKEN_NUMBER                      { $$ = createNumber($1, @1.first_column, @1.last_column); }
    ;
 
%%