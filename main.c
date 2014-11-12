/*
 * main.c file
 */

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

#include <stdio.h>

char test[] = " 4 + 2*10 + 3*( 5 + 1 )";

int yyparse(SExpression **expression, yyscan_t scanner);

SExpression *getAST(const char *expr) {
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
	// couldn't initialize
	return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&expression, scanner)) {
	// error parsing
	return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return expression;
}

int evaluate(SExpression *e) {
    char str[1024] = {0};
    int ret = 0;
    switch (e->type) {
	case eVALUE:
	    ret = e->value;
	    break;
	case eMULTIPLY:
	    ret = evaluate(e->left) * evaluate(e->right);
	    break;
	case ePLUS:
	    ret = evaluate(e->left) + evaluate(e->right);
	    break;
	case ePARENTHESES:
	    ret = evaluate(e->center);
	    break;
	default:
	    // shouldn't be here
	    return 0;
    }
    memcpy(str, test+e->from, e->to-e->from);
    printf("[%s] = %d\n", str, ret);
    return ret;
}

int main(void) {
    SExpression *e = NULL;
    int result = 0;

    e = getAST(test);

    result = evaluate(e);

    printf("Result of '%s' is %d\n", test, result);

    deleteExpression(e);

    return 0;
}