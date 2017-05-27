#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "createNode.h"

//#define DEBUG
#define NEARLYZERO 0.000000001

bool isNearlyZero(double x)
{
    return fabs(x) < NEARLYZERO;
}

#define TEMPMEMORYSIZE 128

static void printAllNodesInListSub(Node *node, int level)
{
    if (level == 0) {
        IOLog1("----------------- Node List -----------------\n");
    }
    IOLog1("[%s]\n"          , node->str);
    IOLog1("\ttype     :%d\n", node->type);
    if (node->hasValue) {
        IOLog1("\t[hasValue]\n");
    }
    if (node->hasXenos) {
        IOLog1("\t[hasXenos]\n");
    }

    if (node->lNode != NULL) {
        IOLog1("\tleft :%s\n", node->lNode->str);
    }
    if (node->rNode != NULL) {
        IOLog1("\trignt:%s\n", node->rNode->str);
    }
    if (node->lNode != NULL) {
        printAllNodesInListSub(node->lNode, level + 1);
    }
    if (node->rNode != NULL) {
        printAllNodesInListSub(node->rNode, level + 1);
    }
    if (level == 0) {
        IOLog1("----------------- --------- -----------------\n\n");
    }
    return;
}
void printAllNodesInList(Node *node)
{
    printAllNodesInListSub(node, 0);
}

static void printAllNodesInOriginalFormSub(Node *node, int level)
{
    if (level == 0) {
        IOLog1("--------------- Original Form ---------------\n");
    }
    switch(node->type) {
        case Value:
            IOLog1("%s", node->str);
            break;
        case Xenos:
            IOLog1("x");
            break;
        case OneArgumentFunction:
            IOLog1("%s[", node->str);
            printAllNodesInOriginalFormSub(node->lNode, level + 1);
            IOLog1("]");
            break;
        case TwoArgumentFunction:
            IOLog1("%s[", node->str);
            printAllNodesInOriginalFormSub(node->lNode, level + 1);
            IOLog1(", ");
            printAllNodesInOriginalFormSub(node->rNode, level + 1);
            IOLog1("]");
            break;
        default:
            exit(1);
    }
    if (level == 0) {
        IOLog1("\n");
        IOLog1("--------------- ------------- ---------------\n");
    }
}

void printAllNodesInOriginalForm(Node *node)
{
    printAllNodesInOriginalFormSub(node, 0);
}

void mallocForStringSafely(char **dest, size_t size, int lineNum)
{
    *dest = malloc(sizeof(char) * size);
    if (*dest == NULL) {
        fprintf(stderr, "malloc error (line:%d)\n", lineNum);
        exit(1);
    }
}

void mallocForNodeSafely(Node **dest, size_t size, int lineNum)
{
    *dest = malloc(sizeof(Node) * size);
    if (*dest == NULL) {
        fprintf(stderr, "malloc error (line:%d)\n", lineNum);
        exit(1);
    }
}

int getIntegerValue(char *integerString)
{
    // integerString is supposed to be an integer
    int integerValue = atoi(integerString);
    char extractedValue[128];
    snprintf(extractedValue, strlen(integerString) + 1, "%d", integerValue);
    if (strcmp(extractedValue, integerString) == 0) {
        return integerValue;
    } else {
        fprintf(stderr, "\n"
                        "[[[INVALID VALUE DETECTED.]]]\n"
                        "extractedValue: \"%s\"\n"
                        "integerValue: \"%d\"\n"
                        "\n", extractedValue, integerValue);
        return integerValue;
    }
}

double getDoubleValue(char *doubleString)
{
    // doubleString is supposed to be an double
    double doubleValue = atof(doubleString);
    char extractedValue[128];
    snprintf(extractedValue, strlen(doubleString) + 1, "%lf", doubleValue);
    if (strcmp(extractedValue, doubleString) == 0) {
        return doubleValue;
    } else {
        fprintf(stderr, "\n"
                        "[[[INVALID VALUE DETECTED.]]]\n"
                        "extractedValue: \"%s\"\n"
                        "doubleValue: \"%lf\"\n"
                        "\n", extractedValue, doubleValue);
        return doubleValue;
    }
}

twoArgumentsFunctionType getTwoArgumentsFunctionType(char *str)
{
    if (strcmp(str, "Plus") == 0) {
        return Plus;
    } else if (strcmp(str, "Times") == 0) {
        return Times;
    } else if (strcmp(str, "Subtract") == 0) {
        return Subtract;
    } else if (strcmp(str, "Divide") == 0) {
        return Divide;
    } else if (strcmp(str, "Power") == 0) {
        return Power;
    } else {
        return eof2;
    }
}

char *getTwoArgumentsFunctionTypeString(twoArgumentsFunctionType tAFType)
{
    switch(tAFType) {
        case Plus:
            return "Plus";
        case Times:
            return "Times";
        case Subtract:
            return "Subtract";
        case Divide:
            return "Divide";
        case Power:
            return "Power";
        default:
            fprintf(stderr, "unknown twoArgumentsFunctionType(line:%d)\n", __LINE__);
            exit(1);
    }
}

oneArgumentFunctionType getOneArgumentFunctionType(char *str)
{
    if (strcmp(str, "Sin") == 0) {
        return Sin;
    } else if (strcmp(str, "Cos") == 0) {
        return Cos;
    } else if (strcmp(str, "Exp") == 0) {
        return Exp;
    } else if (strcmp(str, "Log") == 0) {
        return Log;
    } else {
        return eof1;
    }
}

char *getOneArgumentFunctionTypeString(oneArgumentFunctionType oAFType)
{
    switch(oAFType) {
        case Sin:
            return "Sin";
        case Cos:
            return "Cos";
        case Exp:
            return "Exp";
        case Log:
            return "Log";
        default:
            fprintf(stderr, "unknown oneArgumentFunctionType(line:%d)\n", __LINE__);
            exit(1);
    }
}


static void skipSpaces(char *str, int *pos)
{
    /*
     * skip spaces
     */
    for (;isspace(str[*pos]); (*pos)++) {
    }
}
static bool isTerminator(char c)
{
    return c == '\0' ||
           c == ']' ||
           c == ',' ||
           isspace(c);
}
static Node *createNodeSub(int *pos, char *str)
{

#ifdef DEBUG
    static int callCount = 1;
    printf("createNodeSub:%d\n", callCount++);
#endif

    Node *newNode;
    char temp[TEMPMEMORYSIZE];

    mallocForNodeSafely(&(newNode), 1, __LINE__);

    skipSpaces(str, pos);

    /*
     * some types have a special character at first character
     */
    temp[0] = str[*pos];
    (*pos)++;
    if (isdigit(temp[0]) || temp[0] == '-') {
        newNode->type = Value;
        int i = 1;
        /*
         * only when input data is jest a number, 
         * '\0', ' ', ']', ',' are the terminators.
         */
        for (; i < TEMPMEMORYSIZE || isTerminator(str[*pos]) || isdigit(str[*pos]) || str[*pos] == '.'; i++, (*pos)++) {
            temp[i] = str[*pos];
            if (isTerminator(str[*pos])) {
                temp[i] = '\0';
                break;
            }
        }

        /*
         * too large value
         */
        if (i == TEMPMEMORYSIZE) {
            fprintf(stderr, "%s is too large.\n", temp);
            exit(1);
        } else if (!isTerminator(str[*pos])) {
            fprintf(stderr, "invalid input.([%d]\"%c\"(ASCII no.%d) is strange for a numeral string)\n", *pos, str[*pos], str[*pos]);
            exit(1);
        }

        mallocForStringSafely(&(newNode->str), strlen(temp) + 1, __LINE__);
        strcpy(newNode->str, temp);

        newNode->lNode = NULL;
        newNode->rNode = NULL;
        return newNode;
    } else if (temp[0] == 'x') {
        newNode->type = Xenos;
        mallocForStringSafely(&(newNode->str), strlen("x") + 1, __LINE__);
        strcpy(newNode->str, "x");
        newNode->lNode = NULL;
        newNode->rNode = NULL;
        return newNode;
    }

    /*
     * OneArgumentFunction or TwoArgumentFunction
     */
    if (newNode->type == OneArgumentFunction ||
        newNode->type == TwoArgumentFunction) {
        /* sometimes initialized in this way (this causes bug) */
        newNode->type = Value;
    }
    int i = 1;

    for (; i < TEMPMEMORYSIZE; i++, (*pos)++) {
        /*
         * special characters ('[' , ',' , ']', ' ')
         * all of them are not loaded in temp
         */
        if (str[*pos] == '[') {
            /*
             * '[' is skipped
             */
            temp[i] = '\0';
            (*pos)++;
            newNode->lNode = createNodeSub(pos, str);
            break;
        }

        temp[i] = str[*pos];
    }

    mallocForStringSafely(&(newNode->str), strlen(temp) + 1, __LINE__);
    strcpy(newNode->str, temp);

    skipSpaces(str, pos);
    if (str[*pos] == ',') {
        newNode->type = TwoArgumentFunction;
        (*pos)++;

        skipSpaces(str, pos);

        newNode->rNode = createNodeSub(pos, str);
    }

    skipSpaces(str, pos);

    if (str[*pos] == ']') {
        if (newNode->type != TwoArgumentFunction) {
            newNode->type = OneArgumentFunction;
            newNode->rNode = NULL;
        }
        (*pos)++;
        return newNode;
    }

    /* 
     * something wrong is happening
     * there is a unpaired bracket
     */
    fprintf(stderr, "a unpaired bracket is detected(pos:%d, str:%s)\n", *pos, str);
    exit(1);
}

static bool configureHasXenosFlag(Node *node)
{
    bool flag[2];
    switch (node->type) {
        case Value:
            return node->hasXenos = false;
        case Xenos:
            return node->hasXenos = true;
        case OneArgumentFunction:
            return node->hasXenos = configureHasXenosFlag(node->lNode);
        case TwoArgumentFunction:
            flag[0] = configureHasXenosFlag(node->lNode);
            flag[1] = configureHasXenosFlag(node->rNode);
            //(node->hasXenos = (configureHasXenosFlag(node->lNode) || configureHasXenosFlag(node->rNode)));
            return node->hasXenos = flag[0] || flag[1];
        default:
            fprintf(stderr, "something wrong(line:%d)\n", __LINE__);
            exit(1);
    }
}

static bool configureHasValueFlag(Node *node)
{
    bool flag[2];
    switch (node->type) {
        case Value:
            return node->hasValue = true;
        case Xenos:
            return node->hasValue = false;
        case OneArgumentFunction:
            return node->hasValue = configureHasValueFlag(node->lNode);
        case TwoArgumentFunction:
            flag[0] = configureHasValueFlag(node->lNode);
            flag[1] = configureHasValueFlag(node->rNode);
            return node->hasValue = flag[0] || flag[1];
        default:
            fprintf(stderr, "something wrong(line:%d)\n", __LINE__);
            exit(1);
    }
}

static void configureNodeFlag(Node *node)
{
    node->hasXenos = configureHasXenosFlag(node);
    node->hasValue = configureHasValueFlag(node);
    return;
}

Node *createNode(char *str)
{
    int pos = 0;
    Node *newNode;
    newNode = createNodeSub(&pos, str);
    configureNodeFlag(newNode);
    return newNode;
}

void freeAllNodes(Node *node)
{
    if (node->type == Xenos || node->type == Value) {
        free(node->str);
        free(node);
        return;
    } else if (node->type == OneArgumentFunction) {
        freeAllNodes(node->lNode);
        free(node->str);
        free(node);
        return;
    } else if (node->type == TwoArgumentFunction) {
        freeAllNodes(node->lNode);
        freeAllNodes(node->rNode);
        free(node->str);
        free(node);
        return;
    }
}

Node *createValueTypeNode(double value)
{
    Node *newNode;
    mallocForNodeSafely(&(newNode), 1, __LINE__);
    char temp[TEMPMEMORYSIZE];
    sprintf(temp, "%lf", value);
    mallocForStringSafely(&(newNode->str), strlen(temp) + 1, __LINE__);
    strcpy(newNode->str, temp);
    newNode->type = Value;
    newNode->hasValue = true;
    newNode->hasXenos = false;
    newNode->lNode = NULL;
    newNode->rNode = NULL;
    return newNode;
}
Node *createOneArgumentFunctionNode(oneArgumentFunctionType oAFType, bool hasV, bool hasX, Node *leftNode)
{
    Node *newNode;
    mallocForNodeSafely(&(newNode), 1, __LINE__);
    mallocForStringSafely(&(newNode->str), strlen(getOneArgumentFunctionTypeString(oAFType)) + 1, __LINE__);
    strcpy(newNode->str, getOneArgumentFunctionTypeString(oAFType));
    newNode->type = OneArgumentFunction;
    newNode->hasValue = hasV;
    newNode->hasXenos = hasX;
    newNode->lNode = leftNode;
    newNode->rNode = NULL;
    return newNode;
}
Node *createTwoArgumentsFunctionNode(twoArgumentsFunctionType tAFType, bool hasV, bool hasX, Node *leftNode, Node *rightNode)
{
    Node *newNode;
    mallocForNodeSafely(&(newNode), 1, __LINE__);
    mallocForStringSafely(&(newNode->str), strlen(getTwoArgumentsFunctionTypeString(tAFType)) + 1, __LINE__);
    strcpy(newNode->str, getTwoArgumentsFunctionTypeString(tAFType));
    newNode->type = TwoArgumentFunction;
    newNode->hasValue = hasV;
    newNode->hasXenos = hasX;
    newNode->lNode = leftNode;
    newNode->rNode = rightNode;
    return newNode;
}
//Node *createOATypeNodeWithoutFlags(oneArgumentFunctionType oAFType, Node *leftNode)
//{
//    Node *newNode;
//    newNode = createOneArgumentFunctionNode(oAFType, false, false, leftNode);
//    return newNode;
//}
//Node *createTATypeNodeWithoutFlags(twoArgumentsFunctionType tAFType, Node *leftNode, Node *rightNode)
//{
//    Node *newNode;
//    newNode = createTwoArgumentsFunctionNode(tAFType, false, false, leftNode, rightNode);
//    return newNode;
//}

Node *duplicateNode(Node *node)
{
    Node *newNode;
    mallocForNodeSafely(&(newNode), 1, __LINE__);
    mallocForStringSafely(&(newNode->str), strlen(node->str) + 1, __LINE__);
    strcpy(newNode->str, node->str);
    newNode->type = node->type;
    newNode->hasValue = node->hasValue;
    newNode->hasXenos = node->hasXenos;
    switch(node->type) {
        case Value:
            newNode->lNode = NULL;
            newNode->rNode = NULL;
            break;
        case Xenos:
            newNode->lNode = NULL;
            newNode->rNode = NULL;
            break;
        case OneArgumentFunction:
            newNode->lNode = duplicateNode(node->lNode);
            newNode->rNode = NULL;
            break;
        case TwoArgumentFunction:
            newNode->lNode = duplicateNode(node->lNode);
            newNode->rNode = duplicateNode(node->rNode);
            break;
        default:
            fprintf(stderr, "unknown function type(Node *duplicateNode(Node *node); line:%d)\n", __LINE__);
            exit(1);
    }
    return newNode;
}
