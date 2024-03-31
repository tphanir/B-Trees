#include "B.h"


/*-------------------------------*/
/*----------PRINT NODE-----------*/
/*-------------------------------*/
void PRINT_NODE(Node *root)
{
    int i;
    for(i=0; i<root->count; i++)
    {
        printf("%d ", root->data[i]);
    }
}
/*-------------------------------*/
/*-----------PRINT TREE----------*/
/*-------------------------------*/
void PRINT_TREE(Node *root)
{
    if(root != NULL)
    {
        PRINT_NODE(root);
        printf("\n");
        for(int i=0; i<=root->count; i++)
        {
            PRINT_TREE(root->children[i]);
        }
    }
}



/*-------------------------------*/
/*---------BINARY SEARCH---------*/
/*-------------------------------*/
int BINARY_SEARCH(int data[], int target, int start, int end)
{
    int RETURN_VALUE;
    if(start <= end)
    {
        int mid = (start + end) / 2;
        if(data[mid] == target)
        {
            RETURN_VALUE= mid;
        }
        else if(data[mid] > target)
        {
            RETURN_VALUE= BINARY_SEARCH(data, target, start, mid - 1);
        }
        else
        {
            RETURN_VALUE= BINARY_SEARCH(data, target, mid + 1, end);
        }
    }
    else
    {
        RETURN_VALUE= start;
    }
    return RETURN_VALUE;
}
/*-------------------------------*/
/*----------SEARCH NODE----------*/
/*-------------------------------*/
Boolean SEARCH_NODE(int target, Node *current, int *pos)
{
    Boolean RETURN_VALUE= FALSE;
    *pos = BINARY_SEARCH(current->data, target, 0, current->count-1);
    if(current->data[*pos] == target)
    {
        RETURN_VALUE= TRUE;
    }
    return RETURN_VALUE;
}
/*-------------------------------*/
/*----------SEARCH TREE----------*/
/*-------------------------------*/
Node *SEARCH_TREE(int target, Node *root, int *targetPosition)
{
    Node *RETURN_VALUE= NULL;
    if(root != NULL)
    {

        if(SEARCH_NODE(target, root, targetPosition))
        {
            RETURN_VALUE= root;
        }
        else
        {
            RETURN_VALUE = SEARCH_TREE(target, root->children[*targetPosition], targetPosition);
        }
    }
    return RETURN_VALUE;
}



/*-------------------------------*/
/*------------PUSH IN------------*/
/*-------------------------------*/
void PUSH_IN(int median, Node *medianRight, Node *current, int pos)
{
    int i;
    for (i=current->count; i>pos; i--)
    {
        current->data[i] = current->data[i - 1];
        current->children[i + 1] = current->children[i];
    }
    current->data[pos] = median;
    current->children[pos + 1] = medianRight;
    current->count++;
}
/*-------------------------------*/
/*-------------SPLIT-------------*/
/*-------------------------------*/
void SPLIT(int median, Node *medianRight, Node *current, int pos, int *newMedian, Node **newMedianRight)
{
   int i;
   int m;

   if(pos <= MIN)
   {
       m = MIN;
   }
   else
   {
       m = MIN + 1;
   }

   *newMedianRight = (Node *)malloc(sizeof(Node));

   for(i = m; i < MAX; i++)
   {
       (*newMedianRight)->data[i - m] = current->data[i];
       (*newMedianRight)->children[i - m + 1] = current->children[i + 1];
   }

   (*newMedianRight)->count = MAX - m;
   current->count = m;

   if(pos <= MIN)
   {
       PUSH_IN(median, medianRight, current, pos);
   }
   else
   {
       PUSH_IN(median, medianRight, *newMedianRight, pos - m);
   }

   *newMedian = current->data[current->count - 1];
   (*newMedianRight)->children[0] = current->children[current->count];

   current->count--;
}
/*-------------------------------*/
/*-----------PUSH DOWN-----------*/
/*-------------------------------*/
Boolean PUSH_DOWN(int value, Node *current, int *median, Node **medianRight)
{
    Boolean RETURN_VALUE= FALSE;
    int pos;
    if(current == NULL)
    {
        *median = value;
        *medianRight = NULL;
        RETURN_VALUE= TRUE;
    }
    else
    {
        SEARCH_NODE(value, current, &pos);
        if(PUSH_DOWN(value, current->children[pos], median, medianRight))
        {
            if(current->count < MAX)
            {
                PUSH_IN(*median, *medianRight, current, pos);
                RETURN_VALUE= FALSE;
            }
            else
            {
                SPLIT(*median, *medianRight, current, pos, median, medianRight);
                RETURN_VALUE= TRUE;
            }
        }
    }
    return RETURN_VALUE;
}
/*-------------------------------*/
/*----------INSERT TREE----------*/
/*-------------------------------*/
Node *INSERT_TREE(int value, Node *root)
{
    int median;
    Node *medianRight;
    Node *newRoot;

    Node *RETURN_VALUE= root;

    if(PUSH_DOWN(value, root, &median, &medianRight))
    {
        newRoot = (Node *)malloc(sizeof(Node));
        newRoot->count = 1;
        newRoot->data[0] = median;
        newRoot->children[0] = root;
        newRoot->children[1] = medianRight;

        RETURN_VALUE= newRoot;
    }
    return  RETURN_VALUE;
}



/*-------------------------------*/
/*-----------COMBINE-------------*/
/*-------------------------------*/
void COMBINE(Node *current, int pos)
{
    int c;
    Node *right;
    Node *left;
    right = current->children[pos];
    left = current->children[pos-1];
    left->count++;
    left->data[left->count-1] = current->data[pos-1];
    left->children[left->count] = right->children[0];
    for(c=1; c<=right->count; c++)
    {
        left->count++;
        left->data[left->count -1] = right->data[c-1];
        left->children[left->count] = right->children[c];
    }
    for(c=pos; c<current->count; c++)
    {
        current->data[c-1] = current->data[c];
        current->children[c] = current->children[c+1];
    }

    current->count--;
    free(right);
}
/*-------------------------------*/
/*----------MOVE RIGHT-----------*/
/*-------------------------------*/
void MOVE_RIGHT(Node *current, int pos)
{
    int c;
    Node *t;
    t = current->children[pos];
    for(c = t->count; c>0; c--)
    {
        t->data[c] = t->data[c-1];
        t->children[c+1] = t->children[c];
    }
    t->children[1] = t->children[0];
    t->count++;
    t->data[0] = current->data[pos -1];
    t = current->children[pos - 1];
    current->data[pos - 1] = t->data[t->count - 1];
    current->children[pos]->children[0] = t->children[t->count];
    t->count--;
}
/*-------------------------------*/
/*-----------MOVE LEFT-----------*/
/*-------------------------------*/
void MOVE_LEFT(Node *current, int pos)
{
    int c;
    Node *t;

    t=current->children[pos-1];
    t->count++;
    t->data[t->count-1] = current->data[pos -1];
    t->children[t->count] = (current->children[pos])->children[0];
    t = current->children[pos];
    current->data[pos-1] = t->data[0];
    t->children[0] = t->children[1];
    t->count--;
    for(c=1; c<=t->count; c++)
    {
        t->data[c-1] = t->data[c];
        t->children[c] = t->children[c+1];
    }
}
/*-------------------------------*/
/*-----------RESTORE-------------*/
/*-------------------------------*/
void RESTORE(Node *current, int pos)
{
    if(pos == 0)
    {
        if(current->children[1]->count > MIN)
        {
            MOVE_LEFT(current, 1);
        }
        else
        {
            COMBINE(current, 1);
        }
    }
    else if(pos == current->count)
    {
        if(current->children[pos -1]->count > MIN)
        {
            MOVE_RIGHT(current, pos);
        }
        else
        {
            COMBINE(current, pos);
        }
    }
    else if(current->children[pos - 1]->count > MIN)
    {
        MOVE_RIGHT(current, pos);
    }
    else if(current->children[pos + 1]->count > MIN)
    {
        MOVE_LEFT(current, pos+1);
    }
    else
    {
        COMBINE(current, pos);
    }
}
/*-------------------------------*/
/*-----------SUCCESSOR-----------*/
/*-------------------------------*/
void SUCCESSOR(Node *current, int pos)
{
    Node *leaf;
    for(leaf = current->children[pos + 1]; leaf->children[0] != NULL; leaf = leaf->children[0])
    {

    }
    current->data[pos] = leaf->data[0];
}
/*-------------------------------*/
/*-------------REMOVE------------*/
/*-------------------------------*/
void REMOVE(Node *current, int pos)
{
    int i;
    for(i=pos; i<current->count - 1; i++)
    {
        current->data[i] = current->data[i+1];
        current->children[i] = current->children[i+1];
    }
    current->children[i] = current->children[i+1];
    current->count--;
}
/*-------------------------------*/
/*--------REC DELETE TREE--------*/
/*-------------------------------*/
void REC_DELETE_TREE(int target, Node *current)
{
    int pos;
    if(current != NULL)
    {
        if(SEARCH_NODE(target, current, &pos))
        {
            if(current->children[pos] != NULL)
            {
                SUCCESSOR(current, pos);
                REC_DELETE_TREE(current->data[pos], current->children[pos+1]);
            }
            else
            {
                REMOVE(current, pos);
            }
        }
        else
        {
            REC_DELETE_TREE(target, current->children[pos]);
        }

        if(current->children[pos])
        {
            if(current->children[pos]->count < MIN)
            {
                RESTORE(current, pos);
            }
        }
        if (pos < current->count && current->children[pos+1])
        {
            if(current->children[pos+1]->count < MIN)
            {
                RESTORE(current, pos+1);
            }
        }

    }
}
/*-------------------------------*/
/*----------DELETE TREE----------*/
/*-------------------------------*/
Node *DELETE_TREE(int target, Node *root)
{
    Node *oldRoot;
    REC_DELETE_TREE(target, root);
    if(root->count == 0)
    {
        oldRoot = root;
        root = root->children[0];
        free(oldRoot);
    }
    return  root;
}