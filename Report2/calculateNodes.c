#include <stdio.h>
#include <string.h>
#include <math.h>
#include "createNode.h"
#include "calculateNodes.h"

static double calculateTwoArgumentsFunction(twoArgumentsFunctionType fType, double val1, double val2)
{
    switch(fType) {
        case Plus:
            return val1 + val2;
        case Times:
            return val1 * val2;
        case Subtract:
            return val1 - val2;
        case Divide:
            if (val2 == 0) {
                fprintf(stderr, "error: divided by 0\n");
                exit(1);
            }
            return val1 / val2;
        case Power:
            return pow(val1, val2);
        default:
            fprintf(stderr, "unknown two arguments function\n");
            exit(1);
    }
}

static double calculateOneArgumentFunction(oneArgumentFunctionType fType, double val)
{
    switch(fType) {
        case Sin:
            return sin(val);
        case Cos:
            return cos(val);
        case Exp:
            return exp(val);
        case Log:
            if (isNearlyZero(val)) {
                printf("WARNING:Log[0] called(line:%d)\n", __LINE__);
            }
            return log(val);
        default:
            fprintf(stderr, "unknown one argument function\n");
            exit(1);
    }
}

double calculateNodesAssignValueToX(Node *node, double x)
{
    nodeType nType = node->type;
    oneArgumentFunctionType oFType;
    twoArgumentsFunctionType tFType;
    switch(nType) {
        case Xenos:
            return x;
        case Value:
            if (strchr(node->str, '.') == NULL) {
                return getIntegerValue(node->str);
            } else {
                return getDoubleValue(node->str);
            }
        case OneArgumentFunction:
            oFType = getOneArgumentFunctionType(node->str);
            if (oFType == eof1) {
                fprintf(stderr, "unknown one argument function: %s\n", node->str);
                exit(1);
            }
            return calculateOneArgumentFunction(oFType, calculateNodesAssignValueToX(node->lNode, x));
        case TwoArgumentFunction:
            tFType = getTwoArgumentsFunctionType(node->str);
            if (tFType == eof2) {
                fprintf(stderr, "unknown two arguments function: %s\n"
                                "Log\n", node->str);
                printAllNodesInList(node);
                exit(1);
            }
            return calculateTwoArgumentsFunction(tFType, calculateNodesAssignValueToX(node->lNode, x), calculateNodesAssignValueToX(node->rNode, x));
        default:
            printAllNodesInOriginalForm(node);
            fprintf(stderr, "error(Line:%d)\n", __LINE__);
            exit(1);
    }
}
double calculateNodes(Node *node)
{
    if (node->hasXenos) {
        fprintf(stderr, "WARNING: This function structure contains the unknown quantities (x).\n"
                        "         Temporarily, 0 is assigned to x.\n");
    }
    return calculateNodesAssignValueToX(node, 0);
}
