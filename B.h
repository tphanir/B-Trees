#ifndef B_TREES_B_H
#define B_TREES_B_H

#include <stdio.h>
#include <stdlib.h>

#define M 5
#define MAX 4
#define MIN 2

typedef enum {FALSE, TRUE} Boolean;
typedef struct node_tag
{
    int data[MAX];
    int count;
    struct node_tag *children[M];
}Node;

void PRINT_NODE(Node *root);
void PRINT_TREE(Node *root);

int BINARY_SEARCH(int data[], int target, int start, int end);
Boolean SEARCH_NODE(int target, Node *current, int *pos);
Node *SEARCH_TREE(int target, Node *root, int *targetPosition);

void SPLIT(int median, Node *medianRight, Node *current, int pos, int *newMedian, Node **newMedianRight);
void PUSH_IN(int median, Node *medianRight, Node *current, int pos);
Boolean PUSH_DOWN(int value, Node *current, int *median, Node **medianRight);
Node *INSERT_TREE(int value, Node *root);

Node *DELETE_TREE(int target, Node *root);


#endif //B_TREES_B_H
