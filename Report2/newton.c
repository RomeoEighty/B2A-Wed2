#include <math.h>
#include "createNode.h"
#include "differentiateNodes.h"
#include "calculateNodes.h"
#include "newton.h"

#define SUFFICIENT_SMALL 0.0000000001

double isConvex(double x, Node *node)
{
    Node *d2Node = differentiateFormulaWithX(differentiateFormulaWithX(node));
    return calculateNodesAssignValueToX(d2Node, x);
}
double calculateXAtNodeBecomesExtremeSub(double x, Node *node, Node *dNode)
{
    double nextX = x - calculateNodesAssignValueToX(node, x) / calculateNodesAssignValueToX(dNode, x);
    if (fabs(x - nextX) <= SUFFICIENT_SMALL) {
        return nextX;
    } else {
        return calculateXAtNodeBecomesExtremeSub(nextX, node, dNode);
    }
}
double calculateXAtNodeBecomesExtreme(Node *node)
{
    Node *dNode;
    Node *d2Node;
    dNode = differentiateFormulaWithX(node);
    //printf("dNode"); printAllNodesInOriginalForm(dNode);
    d2Node = differentiateFormulaWithX(dNode);
    //printf("d2Node");fflush(stdout); printAllNodesInOriginalForm(d2Node);
    return calculateXAtNodeBecomesExtremeSub(1.0, dNode, d2Node);
}
double calculateXAtNodeBecomesExtremeFrom(Node *node, double initVal)
{
    Node *dNode;
    Node *d2Node;
    dNode = differentiateFormulaWithX(node);
    //printf("dNode"); printAllNodesInOriginalForm(dNode);
    d2Node = differentiateFormulaWithX(dNode);
    //printf("d2Node");fflush(stdout); printAllNodesInOriginalForm(d2Node);
    return calculateXAtNodeBecomesExtremeSub(initVal, dNode, d2Node);
}
