/*
 * Expression.h
 * Definition of the structure used to build the syntax tree.
 */
#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

typedef enum tagEOperationType
{
    eVALUE,
    eMULTIPLY,
    ePLUS,
    ePARENTHESES
} EOperationType;

typedef struct tagSExpression
{
    EOperationType type;///< type of operation
    int from;
    int to;
    int value;///< valid only when type is eVALUE
    struct tagSExpression *left;
    struct tagSExpression *right;
    struct tagSExpression *center;
} SExpression;

SExpression *createNumber(int value, int from, int to);

SExpression *createOperation(EOperationType type, SExpression *left, SExpression *center, SExpression *right, int from, int to);

void deleteExpression(SExpression *b);

#endif // __EXPRESSION_H__
