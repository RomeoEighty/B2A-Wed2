/*
 * 540479c
 * Ryutaro Yamaguchi
 * 2016/12/14
 * kadai01.c
 * kadai02.c
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define VER0

#ifndef VER0
#define VER1
#endif

typedef struct node {
    char value;
    struct node *left;
    struct node *right;
} node_t;

bool isOperant(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    } else {
        return false;
    }
}

void traverse(node_t *node)
{
    putchar(node->value);
    if (isOperant(node->value)) {
        traverse(node->left);
        traverse(node->right);
    } else if (isdigit(node->value)) {
        return;
    } else {
        fprintf(stderr, "unknown state\n");
        exit(1);
    }
    return;
}

void traverse_forWA(node_t *node)
{
    char c = node->value;
    if(isOperant(c)) {
        switch(c) {
            case '+':
                printf("Plus[");
                traverse_forWA(node->left);
                printf(", ");
                traverse_forWA(node->right);
                break;
            case '-':
                printf("Subtract[");
                traverse_forWA(node->left);
                printf(", ");
                traverse_forWA(node->right);
                break;
            case '*':
                printf("Times[");
                traverse_forWA(node->left);
                printf(", ");
                traverse_forWA(node->right);
                break;
            case '/':
                printf("Divide[");
                traverse_forWA(node->left);
                printf(", ");
                traverse_forWA(node->right);
                break;
            default:
                fprintf(stderr, "unknown state\n");
                exit(1);
        }
        printf("]");
    } else if (isdigit(c)) {
        printf("%c", c);
        return;
    } else {
        fprintf(stderr, "unknown state\n");
        exit(1);
    }
    return;
}

node_t *create_node(int *pos, char *s)
{
    node_t *newnode = NULL;
    newnode = malloc(sizeof(node_t));
    if (newnode == NULL) {
        fprintf(stderr, "malloc failure\n");
        exit(1);
    }
    if (isOperant(s[*pos])) {
        newnode->value = s[*pos];
        *pos = *pos + 1;
        newnode->left = create_node(pos, s);
        *pos = *pos + 1;
        newnode->right = create_node(pos, s);
    } else if (isdigit(s[*pos])) {
        newnode->value = s[*pos];
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    } else {
        fprintf(stderr, "unknown state\n");
        exit(1);
    }
    return newnode;
}

double parse(node_t *node)
{
    char c = node->value;
    if (isOperant(c)) {
        switch(c) {
            case '+':
                return (double)(parse(node->left) + parse(node->right));
            case '-':
                return (double)(parse(node->left) - parse(node->right));
            case '*':
                return (double)(parse(node->left) * parse(node->right));
            case '/':
                return (double)(parse(node->left) / parse(node->right));
            default:
                fprintf(stderr, "unknown operant\n");
                exit(1);
        }
    } else if (isdigit(c)) {
        return (double)(c - '0');
    } else {
        fprintf(stderr, "unknown state\n");
        exit(1);
    }
}

int main(void)
{
    //char str[] = "+/9*84-*84+73";
    char str[] = "+-8*2+-8/27-*5*3+-8*2+-8/22-*2*315//2/9755/*2/945";
    int pos = 0;
    node_t *root = create_node(&pos, str);
    traverse(root);
    printf(" = %lf\n", parse(root));
    traverse_forWA(root);
    return 0;
}
