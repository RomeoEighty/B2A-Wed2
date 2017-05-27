#ifndef CREATENODE_H
#define CREATENODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//#define DEBUG
#ifdef DEBUG

#define IOLog1(...) { printf(__VA_ARGS__); fflush(stdout); }
#define IOLog2(args...) { printf(args...); fflush(stdout); }

#endif /* DEBUG */

#ifndef IOLog1
#define IOLog1(...) { printf(__VA_ARGS__); }
#endif
#ifndef IOLog2
#define IOLog2(args...)
#endif


typedef enum {
    Plus    ,
    Times   ,
    Subtract,
    Divide  ,
    Power   ,
    eof2    , // error flag
} twoArgumentsFunctionType;

typedef enum {
    Sin ,
    Cos ,
    Exp ,
    Log ,
    eof1, // error flag
} oneArgumentFunctionType;

typedef enum {
    Xenos              ,
    Value              ,
    OneArgumentFunction,
    TwoArgumentFunction,
} nodeType;

typedef struct Node {
    char     *str;
    nodeType type;
    bool     hasXenos; /* if Node has Xenos somewhere below */
    bool     hasValue; /* if Node has Value somewhere below */
    struct Node *lNode;
    struct Node *rNode;
} Node;

bool isNearlyZero(double x);

void printAllNodesInList(Node *node);
void printAllNodesInOriginalForm(Node *node);
void mallocForStringSafely(char **dest, size_t size, int lineNum);
void mallocForNodeSafely(Node **dest, size_t size, int lineNum);

int getIntegerValue(char *integerString);
double getDoubleValue(char *doubleString);

twoArgumentsFunctionType getTwoArgumentsFunctionType(char *str);
char *getTwoArgumentsFunctionTypeString(twoArgumentsFunctionType tAFType);

oneArgumentFunctionType getOneArgumentFunctionType(char *str);
char *getOneArgumentFunctionTypeString(oneArgumentFunctionType oAFType);

Node *createNode(char *str);

void freeAllNodes(Node *node);

Node *createValueTypeNode(double value);
Node *createOneArgumentFunctionNode(oneArgumentFunctionType oAFType, bool hasV, bool hasX, Node *leftNode);
Node *createTwoArgumentsFunctionNode(twoArgumentsFunctionType tAFType, bool hasV, bool hasX, Node *leftNode, Node *rightNode);

Node *duplicateNode(Node *node);
#endif
