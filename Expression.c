/*
 * Expression.c
 * Implementation of functions used to build the syntax tree.
 */

#include "Expression.h"

#include <stdlib.h>

/**
 * @brief Allocates space for expression
 * @return The expression or NULL if not enough memory
 */
static SExpression *allocateExpression()
{
    SExpression *b = (SExpression *)malloc(sizeof(SExpression));

    if (b == NULL)
        return NULL;

    b->type = eVALUE;
    b->value = 0;

    b->left = NULL;
    b->right = NULL;

    return b;
}

SExpression *createNumber(int value, int from, int to)
{
    SExpression *b = allocateExpression();

    if (b == NULL)
        return NULL;

    b->type = eVALUE;
    b->value = value;
    b->from = from;
    b->to = to;

    return b;
}

SExpression *createOperation(EOperationType type, SExpression *left, SExpression *center, SExpression *right, int from, int to)
{
    SExpression *b = allocateExpression();

    if (b == NULL)
        return NULL;

    b->type = type;
    b->center = center;
    b->left = left;
    b->right = right;
    b->from = from;
    b->to = to;

    return b;
}

void deleteExpression(SExpression *b)
{
    if (b == NULL)
        return;

    deleteExpression(b->left);
    deleteExpression(b->right);

    free(b);
}
