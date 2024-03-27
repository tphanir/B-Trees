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
    *pos = BINARY_SEARCH(current->data, target, 0, MAX - 1);
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
            SEARCH_NODE(target, root->children[*targetPosition], targetPosition);
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
        current->data[i - 1] = current->data[i - 2];
        current->children[i] = current->children[i - 1];
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

   for(i = m + 1; i <= MAX; i++)
   {
       (*newMedianRight)->data[i - m - 1] = current->data[i - 1];
       (*newMedianRight)->children[i - m] = current->children[i];
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
        if(SEARCH_NODE(value, current, &pos))
        {
            printf("WARNING : inserting duplicate element.");
        }
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
