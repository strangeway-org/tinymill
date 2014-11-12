/*
 * Expression.h
 * Definition of the structure used to build the syntax tree.
 */
#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

/**
 * @brief The operation type
 */
typedef enum tagEOperationType
{
    eVALUE,
    eMULTIPLY,
    ePLUS,
    ePARENTHESES
} EOperationType;

/**
 * @brief The expression structure
 */
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

/**
 * @brief It creates an identifier
 * @param value The number value
 * @return The expression or NULL in case of no memory
 */
SExpression *createNumber(int value, int from, int to);

/**
 * @brief It creates an operation
 * @param type The operation type
 * @param left The left operand
 * @param right The right operand
 * @return The expression or NULL in case of no memory
 */
SExpression *createOperation(EOperationType type, SExpression *left, SExpression *center, SExpression *right, int from, int to);

/**
 * @brief Deletes a expression
 * @param b The expression
 */
void deleteExpression(SExpression *b);

#endif // __EXPRESSION_H__
