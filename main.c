#include "B.h"
void generateDOT(Node *root, FILE *fp) {
    if (root == NULL) {
        return;
    }

    fprintf(fp, "node%d [label=\"", (int)root);
    fprintf(fp, "<data>");
    fprintf(fp, "%d", root->data[0]);
    for (int i = 1; i < root->count; i++) {
        fprintf(fp, "|%d", root->data[i]);
    }
    fprintf(fp, "\"];\n");

    for (int i = 0; i <= root->count; i++) {
        if (root->children[i] != NULL) {
            fprintf(fp, "node%d:data -> node%d [arrowhead=\"normal\", color=\"black\", style=\"solid\", penwidth=1, tailport=\"s\", headport=\"n\"];\n", (int)root, (int)root->children[i]);
            generateDOT(root->children[i], fp);
        }
    }
}

void main()
{
    Node *root = NULL;
    FILE *fptr = fopen("tree.dot","w");

    int arr[] = {18, 93, 42, 70, 11, 56, 85, 37, 64, 29, 51, 9, 88, 75, 3, 47, 24, 63, 14, 97};
            for(int i=0; i<20;i++)
    {
        root = INSERT_TREE(arr[i], root);
    }

    //PRINT_TREE(root);
    root = DELETE_TREE(47, root);
    root = DELETE_TREE(56, root);



    fprintf(fptr, "digraph G {\n");
    fprintf(fptr, "node [shape=record];\n");
    generateDOT(root, fptr);
    fprintf(fptr,"graph [layout=\"dot\", size=\"200,200\"]\n");
    fprintf(fptr, "}\n");
}