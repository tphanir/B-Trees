#include "B.h"

void main()
{
    Node *root = NULL;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
    for(int i=0; i<14; i++)
    {
        root = INSERT_TREE(arr[i], root);
    }
    PRINT_TREE(root);
}