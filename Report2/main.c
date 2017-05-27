#include <stdio.h>
#include <stdlib.h>


#include "createNode.h"
#include "calculateNodes.h"
#include "differentiateNodes.h"
#include "newton.h"

#define BUFSIZE 256

int main(void)
{
    printf("[kadai1]\n");
    char kadai1_1[] = "Plus[Times[Sin[13.4], 3], 2]";
    printf("input data: %s\n", kadai1_1);
    Node *newNode1_1 = createNode(kadai1_1);
    printAllNodesInList(newNode1_1);
    puts("");
    char kadai1_2[] = "Power[Exp[Times[5, x]], Subtract[3, Sin[Cos[9302]]]]";
    printf("input data: %s\n", kadai1_2);
    Node *newNode1_2 = createNode(kadai1_2);
    printAllNodesInList(newNode1_2);
    puts("");
    puts("");
    puts("");

    printf("[kadai2]\n");
    char kadai2_1[] = "Exp[Cos[x]]";
    Node *newNode2_1 = createNode(kadai2_1);
    printAllNodesInOriginalForm(newNode2_1);
    Node *dNode2_1 = differentiateFormulaWithX(newNode2_1);
    printAllNodesInOriginalForm(dNode2_1);
    puts("");
    char kadai2_2[] = "Power[Cos[x], Sin[x]]";
    Node *newNode2_2 = createNode(kadai2_2);
    printAllNodesInOriginalForm(newNode2_2);
    Node *dNode2_2 = differentiateFormulaWithX(newNode2_2);
    printAllNodesInOriginalForm(dNode2_2);
    puts("");
    puts("");
    puts("");

    printf("[kadai3]\n");


    char kadai3_1[] = "Plus[Exp[Times[-1, x]], Power[x, 2]]";
    Node *newNode3_1 = createNode(kadai3_1);
    double x3_1 = calculateXAtNodeBecomesExtreme(newNode3_1);
    printf("%s\n"
           "becomes an extreme value at x = %lf\n"
           "And at that time, the function is %lf and, ", kadai3_1, x3_1, calculateNodesAssignValueToX(newNode3_1, x3_1));
    double c = isConvex(x3_1, newNode3_1);
    if (isNearlyZero(c)) {
        printf("flat\n");
    } else if (c > 0) {
        printf("downward-convex\n");
    } else {
        printf("convex\n");
    }
    puts("");

    char kadai3_2[] = "Plus[Log[Plus[1, Power[x, 2]]], Power[Plus[x, 1],2]]";
    Node *newNode3_2 = createNode(kadai3_2);
    double x3_2 = calculateXAtNodeBecomesExtreme(newNode3_2);
    printf("%s\n"
           "becomes an extreme value at x = %lf\n"
           "And at that time, the function is %lf and, ", kadai3_2, x3_2, calculateNodesAssignValueToX(newNode3_2, x3_2));
    c = isConvex(x3_2, newNode3_2);
    if (isNearlyZero(c)) {
        printf("flat\n");
    } else if (c > 0) {
        printf("downward-convex\n");
    } else {
        printf("convex\n");
    }
    puts("");
    puts("");
    puts("");

/*
 * input formula from standard input
 */
    char buf[BUFSIZE];
    char buf2[BUFSIZE];
    char *newline;
    double initVal;
    printf("input formula:");
    while (fgets(buf, BUFSIZE, stdin) != NULL) {
        if ((newline = strrchr(buf, '\n')) != NULL) {
            *newline = '\0';
        }
        Node *newNode = createNode(buf);

        do {
            printf("input initial value: ");
        } while (fgets(buf2, BUFSIZE, stdin) == NULL);
        if ((newline = strrchr(buf2, '\n')) != NULL) {
            *newline = '\0';
        }
        initVal = atof(buf2);


        double x = calculateXAtNodeBecomesExtremeFrom(newNode, initVal);
        printf("%s\n"
               "becomes an extreme value at x = %lf\n"
               "And at that time, the function is %lf and, ", buf, x, calculateNodesAssignValueToX(newNode, x));
        c = isConvex(x, newNode);
        if (isNearlyZero(c)) {
            printf("flat\n");
        } else if (c > 0) {
            printf("downward-convex\n");
        } else {
            printf("convex\n");
        }
        puts("");
        puts("");
        puts("");

        printf("input formula:");
    }


    return 0;
}
