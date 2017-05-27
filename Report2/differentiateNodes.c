#include <stdio.h>
#include <stdbool.h>
#include "createNode.h"
#include "calculateNodes.h"

/*
 * To simplify tree structure, summerize all value.
 *
 * hasValue   && hasXenos   -> TwoArgumentFunction -> recursive call in both nodes
 *                             OneArgumentFunction : one argument which has both value and x???
 *
 * hasValue   && !hasXenos  -> return newNode has calculeted value
 * !hasValue  && hasXenos   -> return itself
 * (!hasValue && !hasXenos) -> Error: it is not supposed to exist
 */
/*
 * simplify functions
 * (MAKE SURE to call summerizeValue(Node *) first)
 *
 * Plus[A, 0]  -> A
 * Times[A, 0] -> 0
 *
 * Divide[0, A] -> 0
 *
 * Subtract[A, 0] -> A
 * Subtract[0, A] -> Times[-1, A]
 * Power[A, 0] -> A
 * Power[0, A] -> 0
 *
 * Times[A, 1] -> A
 * Times[1, A] -> A
 * Divide[A, 1] -> A
 * Power[A, 1] -> A
 *
 * (If called summerizeValue(Node *), functions below are unnecessary to worry about)
 * Sin[num]: fmod(num, M_PI) == 0 -> 0
 * Cos[num]: fmod(num, M_PI) == M_PI / 2 -> 1
 *           fmod(num, M_PI) == -M_PI / 2 -> -1
 * Exp[num]: num == 0 -> 1
 * Log[num]: num == 1 -> 0
 */

static Node *summerizeValueSub(Node *node)
{
    if (node->hasValue && node->hasXenos) {
        if (node->type == TwoArgumentFunction) {
            node->lNode = summerizeValueSub(node->lNode);
            node->rNode = summerizeValueSub(node->rNode);
            node->hasValue = node->lNode->hasValue || node->rNode->hasValue;
            node->hasXenos = node->lNode->hasXenos || node->rNode->hasXenos;
            /* These renewals may change hasXenos and hasValue flags */

            if (node->lNode->type == Value) {
                double value = getDoubleValue(node->lNode->str);
                if(isNearlyZero(value)) {
                    /*
                     * the type of lNode is Value and the value is nearly zero,
                     * which means TwoArgumentFunction[0, A].
                     */
                    Node *newNode;
                    switch(getTwoArgumentsFunctionType(node->str)) {
                        case Plus:
                        /* Plus[0, A] -> A */
                            newNode = duplicateNode(node->rNode);
                            free(node->str);
                            free(node);
                            return newNode;
                        case Times:
                        /* Times[0, A] -> 0 */
                            mallocForNodeSafely(&(newNode), 1, __LINE__);
                            newNode = createValueTypeNode(0.);
                            freeAllNodes(node);
                            return newNode;
                        case Subtract:
                        /* Subtract[0, A] -> Times[-1, A] */
                            newNode = createTwoArgumentsFunctionNode(Times, true, true, createValueTypeNode(-1.), node->rNode);

                            free(node->str);
                            free(node);

                            return newNode;
                        case Divide:
                        /* Divide[0, A] -> 0 */
                            newNode = createValueTypeNode(0.);

                            freeAllNodes(node);

                            return newNode;
                        case Power:
                        /* Power[0, A] -> 0 */
                            newNode = createValueTypeNode(0.);

                            freeAllNodes(node);

                            return newNode;
                        default:
                            fprintf(stderr, "Something wrong is happening(line:%d)\n", __LINE__);
                            exit(1);
                    }
                } else if (isNearlyZero(value - 1)){
                    /*
                     * (Times[A, 1] -> A)
                     * Times[1, A] -> A
                     * (Divide[A, 1] -> A)
                     * (Power[A, 1] -> A)
                     */
                    Node *newNode;
                    if (getTwoArgumentsFunctionType(node->str) == Times) {
                        newNode = duplicateNode(node->rNode);
                        free(node->str);
                        free(node);
                        return newNode;
                    } else {
                        return node;
                    }
                }
            }
            if (node->rNode->type == Value) {
                double value = getDoubleValue(node->rNode->str);
                if(isNearlyZero(value)) {
                    /*
                     * the type of rNode is Value and the value is nearly zero,
                     * which means TwoArgumentFunction[A, 0].
                     * the difference from above appears at Subtract, Divide, Power.
                     */
                    Node *newNode;
                    switch(getTwoArgumentsFunctionType(node->str)) {
                        case Plus:
                        /* Plus[A, 0] -> A */
                            newNode = duplicateNode(node->lNode);
                            free(node->str);
                            free(node);
                            return newNode;
                        case Times:
                        /* Times[A, 0] -> 0 */
                            mallocForNodeSafely(&(newNode), 1, __LINE__);
                            newNode = createValueTypeNode(0.);
                            freeAllNodes(node);
                            return newNode;
                        case Subtract:
                            /* Subtract[A, 0] -> A */
                            newNode = duplicateNode(node->lNode);
                            free(node->str);
                            free(node);
                            return newNode;
                        case Divide:
                            /* Divide[A, 0] (0 is technically the value which is nearly 0) */
                            fprintf(stderr, "WARNING: You may about to divide by 0\n(line:%d)", __LINE__);
                            return node;
                        case Power:
                            /* Power[A, 0] -> 1 */
                            newNode = createValueTypeNode(1.);

                            freeAllNodes(node);

                            return newNode;
                        default:
                            fprintf(stderr, "Something wrong is happening(line:%d)\n", __LINE__);
                            exit(1);
                    }
                } else if (isNearlyZero(value - 1)){
                    /*
                     * Times[A, 1] -> A
                     * (Times[1, A] -> A)
                     * Divide[A, 1] -> A
                     * Power[A, 1] -> A
                     */
                    Node *newNode;
                    twoArgumentsFunctionType tAFType = getTwoArgumentsFunctionType(node->str);
                    if (tAFType == Times ||
                        tAFType == Divide ||
                        tAFType == Power) {
                        newNode = duplicateNode(node->lNode);
                        free(node->str);
                        free(node);
                        return newNode;
                    } else {
                        return node;
                    }
                } else {
                    /* just return itself */
                    return node;
                }
            }
            /* When TwoArgumentFunction has no nearly zero value, just return itself */
            return node;
        } else if (node->type == OneArgumentFunction) {
            node->lNode = summerizeValueSub(node->lNode);
            node->hasValue = node->lNode->hasValue;
            node->hasXenos = node->lNode->hasXenos;
            if (node->hasValue && !node->hasXenos) {
                Node *newNode;
                double value = calculateNodes(node);
                newNode = createValueTypeNode(value);
                return newNode;
            } else {
                return node;
            }
        } else {
            /* just return itself */
            return node;
        }
    } else if (node->hasValue && !node->hasXenos) {
        if (node->type == OneArgumentFunction || node->type == TwoArgumentFunction) {
            Node *newNode;
            double value = calculateNodes(node); /*
                                                  * node has only value, so calculateNodes(Node *) does not 
                                                  * cause error.
                                                  */
            newNode = createValueTypeNode(value);

            freeAllNodes(node);
            return newNode;
        } else {
            /* just return itself */
            return node;
        }
    } else if (!node->hasValue && node->hasXenos) {
        /* just return itself */
        return node;
    } else {
        /* Node has neither Value nor Xenos does not exist */
        fprintf(stderr, "ERROR: There is a Node whose flags are not configured.(line:%d)\n", __LINE__);
        exit(1);
    }
}

Node *summerizeValue(Node *node)
{
    Node *newNode;
    newNode = summerizeValueSub(node);
    return newNode;
}

/*
 * Node *differentiateFormulaWithXSub(Node *)
 * (WARNING: Make sure to call summerizeValue(Node *) beforehand and afterward
 *           Plus make sure to call configureNodeFlag(Node *) afterward)
 * This function recursively differentiate formula.
 *
 *
 * Plus[A, B]     -> Plus[A', B']
 * Times[A, B]    -> Plus[Times[A', B], Times[A, B']]
 * Subtract[A, B] -> Subtract[A', B']
 * Divide[A, B]   -> Divide[Subtract[Times[A', B], Times[A, B']], Power[B, 2]]
 * Power[A, B]    -> Times[Plus[Times[B', Log[A]], Times[Divide[B, A], A']], Power[A, B]]
 *
 * Plus[A, k]     -> A'
 * Time[A, k]     -> Times[A', k]
 * Subtract[A, k] -> A'
 *
 * Divide[A, k]   -> Divide[A', k]
 * Divide[k, A]   -> Times[Divide[-k, Power[A, 2]], A']
 * Power[A, k]    -> Times[Power[A, k], Times[Divide[k, A], A']]
 * Power[k, A]    -> Times[Power[k, A], Times[Log[k], A']]
 *
 * (If you properly called summerizeValue(Node *), TwoArgumentFunction which has no Xenos
 *  does not exist.)
 *
 * Sin[A] -> Times[Cos[A], A']
 * Cos[A] -> Times[-1, Times[Sin[A], A']]
 * Exp[A] -> Times[Exp[A], A']
 * Log[A] -> Divide[A', A]
 */
static Node *differentiateFormulaWithXSub(Node *node)
{
    nodeType nType = node->type;
    oneArgumentFunctionType oAFType;
    twoArgumentsFunctionType tAFType;
    Node *newNode[15];
    bool hasV;
    bool hasX;

    switch(nType) {
        case Value:
            newNode[0] = createValueTypeNode(0.);
            freeAllNodes(node);
            return newNode[0];
        case Xenos:
            newNode[0] = createValueTypeNode(1.);
            freeAllNodes(node);
            return newNode[0];
        case OneArgumentFunction:
            oAFType = getOneArgumentFunctionType(node->str);
            switch(oAFType) {
                case Sin:
                    /* Sin[A] -> Times[Cos[A], A'] */
                    /* A */
                    newNode[3] = duplicateNode(node->lNode);
                    /* Cos[A] */
                    newNode[1] = createOneArgumentFunctionNode(Cos, node->hasValue, node->hasXenos, newNode[3]);
                    /* A' */
                    newNode[2] = differentiateFormulaWithXSub(node->lNode);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = newNode[1]->hasXenos || newNode[2]->hasXenos;
                    newNode[0] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Cos:
                    /* Cos[A] -> Times[-1, Times[Sin[A], A']] */
                    /* -1 */
                    newNode[1] = createValueTypeNode(-1);
                    /* A */
                    newNode[5] = duplicateNode(node->lNode);
                    /* Sin[A] */
                    newNode[3] = createOneArgumentFunctionNode(Sin, node->hasValue, node->hasXenos, newNode[5]);
                    /* A' */
                    newNode[4] = differentiateFormulaWithXSub(node->lNode);
                    /* Times[Sin[A], A'] */
                    hasV = newNode[3]->hasValue || newNode[4]->hasValue;
                    hasX = newNode[3]->hasXenos || newNode[4]->hasXenos;
                    newNode[2] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[3], newNode[4]);

                    hasV = true; /* has -1 */
                    hasX = true; /* A hasXenos */
                    newNode[0] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Exp:
                    /* Exp[A] -> Times[Exp[A], A'] */
                    /* Exp[A] */
                    newNode[1] = duplicateNode(node);
                    /* A' */
                    newNode[2] = differentiateFormulaWithXSub(node->lNode);

                    hasV = node->hasValue || newNode[2]->hasValue;
                    hasX = true; /* A hasXenos */
                    newNode[0] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Log:
                    /* Log[A] -> Divide[A', A] */
                    /* A */
                    newNode[2] = duplicateNode(node->lNode);
                    /* A' */
                    newNode[1] = differentiateFormulaWithXSub(node->lNode);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = true; /* A hasXenos */
                    newNode[0] = createTwoArgumentsFunctionNode(Divide, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                default:
                    fprintf(stderr, "unknown OneArgumentFunction(line:%d)", __LINE__);
                    exit(1);
            } 
        case TwoArgumentFunction:
            tAFType = getTwoArgumentsFunctionType(node->str);
            switch(tAFType) {
                case Plus:
                    /* Plus[A, B]     -> Plus[A', B'] */
                    /* A' */
                    newNode[1] = differentiateFormulaWithXSub(node->lNode);
                    /* B' */
                    newNode[2] = differentiateFormulaWithXSub(node->rNode);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = newNode[1]->hasXenos || newNode[2]->hasXenos;
                    newNode[0] = createTwoArgumentsFunctionNode(Plus, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Times:
                    /* Times[A, B]    -> Plus[Times[A', B], Times[A, B']] */
                    /* A */
                    newNode[5] = duplicateNode(node->lNode);
                    /* B */
                    newNode[4] = duplicateNode(node->rNode);
                    /* A' */
                    newNode[3] = differentiateFormulaWithXSub(node->lNode);
                    /* B' */
                    newNode[6] = differentiateFormulaWithXSub(node->rNode);
                    /* Times[A', B] */
                    hasV = newNode[3]->hasValue || newNode[4]->hasValue;
                    hasX = newNode[3]->hasXenos || newNode[4]->hasXenos;
                    newNode[1] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[3], newNode[4]);
                    /* Times[A, B'] */
                    hasV = newNode[5]->hasValue || newNode[6]->hasValue;
                    hasX = newNode[5]->hasXenos || newNode[6]->hasXenos;
                    newNode[2] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[5], newNode[6]);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = true; /* A hasXenos */
                    newNode[0] = createTwoArgumentsFunctionNode(Plus, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Subtract:
                    /* Subtract[A, B] -> Subtract[A', B'] */
                    /* A' */
                    newNode[1] = differentiateFormulaWithXSub(node->lNode);
                    /* B' */
                    newNode[2] = differentiateFormulaWithXSub(node->rNode);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = newNode[1]->hasXenos || newNode[2]->hasXenos;
                    newNode[0] = createTwoArgumentsFunctionNode(Subtract, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Divide:
                    /* Divide[A, B]   -> Divide[Subtract[Times[A', B], Times[A, B']], Power[B, 2]] */
                    /* index             0      1        3     7   8   4     9  10    2     5  6   */
                    /* A */
                    newNode[9] = duplicateNode(node->lNode);
                    /* B */
                    newNode[8] = duplicateNode(node->rNode);
                    /* B */
                    newNode[5] = duplicateNode(node->rNode);
                    /* A' */
                    newNode[7] = differentiateFormulaWithXSub(node->lNode);
                    /* B' */
                    newNode[10] = differentiateFormulaWithXSub(node->rNode);
                    /* Times[A', B] */
                    hasV = newNode[7]->hasValue || newNode[8]->hasValue;
                    hasX = newNode[7]->hasXenos || newNode[8]->hasXenos;
                    newNode[3] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[7], newNode[8]);
                    /* Times[A, B'] */
                    hasV = newNode[9]->hasValue || newNode[10]->hasValue;
                    hasX = newNode[9]->hasXenos || newNode[10]->hasXenos;
                    newNode[4] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[9], newNode[10]);
                    /* 2 */
                    newNode[6] = createValueTypeNode(2);
                    /* Power[B, 2] */
                    hasV = true;
                    hasX = newNode[5]->hasXenos; /* B may be Value */
                    newNode[2] = createTwoArgumentsFunctionNode(Power, hasV, hasX, newNode[5], newNode[6]);
                    /* Subtract[Times[A', B], Times[A, B']] */
                    hasV = newNode[3]->hasValue || newNode[4]->hasValue;
                    hasX = true; /* A or B hasXenos */
                    newNode[1] = createTwoArgumentsFunctionNode(Subtract, hasV, hasX, newNode[3], newNode[4]);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue; /* newNode[2] hasValue */
                    hasX = newNode[1]->hasXenos || newNode[2]->hasXenos; /* newNode[1] hasXenos */
                    newNode[0] = createTwoArgumentsFunctionNode(Divide, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                case Power:
                    /* Power[A, B]    -> Times[Power[A, B], Plus[Times[B', Log[A]], Times[Divide[B, A], A']]] */
                    /* index             0     1     3  4   2    5     7   8   11   6     9      12 13  10    */
                    /* A */
                    newNode[3] = duplicateNode(node->lNode);
                    /* A */
                    newNode[11] = duplicateNode(node->lNode);
                    /* A */
                    newNode[13] = duplicateNode(node->lNode);
                    /* B */
                    newNode[4] = duplicateNode(node->rNode);
                    /* B */
                    newNode[12] = duplicateNode(node->rNode);
                    /* A' */
                    newNode[10] = differentiateFormulaWithXSub(node->lNode);
                    /* B' */
                    newNode[7] = differentiateFormulaWithXSub(node->rNode);
                    /* Log[A] */
                    hasV = newNode[11]->hasValue;
                    hasX = newNode[11]->hasXenos;
                    newNode[8] = createOneArgumentFunctionNode(Log, hasV, hasX, newNode[11]);
                    /* Divide[B, A] */
                    hasV = node->hasValue;
                    hasX = node->hasXenos;
                    newNode[9] = createTwoArgumentsFunctionNode(Divide, hasV, hasX, newNode[12], newNode[13]);
                    /* Times[B', Log[A]] */
                    hasV = newNode[7]->hasValue || newNode[8]->hasValue;
                    hasX = newNode[7]->hasXenos || newNode[8]->hasXenos;
                    newNode[5] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[7], newNode[8]);
                    /* Times[Divide[B, A], A'] */
                    hasV = newNode[9]->hasValue || newNode[10]->hasValue;
                    hasX = newNode[9]->hasXenos || newNode[10]->hasXenos;
                    newNode[6] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[9], newNode[10]);
                    /* Power[A, B] */
                    hasV = node->hasValue;
                    hasX = true;
                    newNode[1] = createTwoArgumentsFunctionNode(Power, hasV, hasX, newNode[3], newNode[4]);
                    /* Plus[Times[B', Log[A]], Times[Divide[B, A], A']] */
                    hasV = newNode[5]->hasValue || newNode[6]->hasValue;
                    hasX = newNode[5]->hasXenos || newNode[6]->hasXenos;
                    newNode[2] = createTwoArgumentsFunctionNode(Plus, hasV, hasX, newNode[5], newNode[6]);

                    hasV = newNode[1]->hasValue || newNode[2]->hasValue;
                    hasX = newNode[1]->hasXenos || newNode[2]->hasXenos;
                    newNode[0] = createTwoArgumentsFunctionNode(Times, hasV, hasX, newNode[1], newNode[2]);

                    free(node->str);
                    free(node);

                    return newNode[0];

                default:
                    printAllNodesInList(node);
                    fprintf(stderr, "unknown TwoArgumentFunction(line:%d)", __LINE__);
                    exit(1);
            }
        default:
            fprintf(stderr, "unknown nodeType(line:%d)\n", __LINE__);
            exit(1);
    }
}

Node *differentiateFormulaWithX(Node *node)
{
    Node *newNode;
    newNode = duplicateNode(node);
    newNode = summerizeValue(newNode);
    newNode = differentiateFormulaWithXSub(newNode);
    newNode = summerizeValue(newNode);
    return newNode;
}
