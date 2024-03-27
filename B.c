#include "B.h"

/*-------------------------------*/
/*---------BINARY SEARCH---------*/
/*-------------------------------*/
int BINARY_SEARCH(int data[], int target, int start, int end)
{
    int RETVAL;
    if(start <= end)
    {
        int mid = (start + end) / 2;
        if(data[mid] == target)
        {
            RETVAL = mid;
        }
        else if(data[mid] > target)
        {
            RETVAL = BINARY_SEARCH(data, target, start, mid - 1);
        }
        else
        {
            RETVAL = BINARY_SEARCH(data, target, mid + 1, end);
        }
    }
    else
    {
        RETVAL = start;
    }

    return RETVAL;
}



/*-------------------------------*/
/*----------SEARCH NODE----------*/
/*-------------------------------*/
Boolean SEARCH_NODE(int target, Node *current, int *pos)
{
    Boolean RETVAL = FALSE;
    *pos = BINARY_SEARCH(current->data, target, 0, MAX - 1);
    if(current->data[pos] == target)
    {
        RETVAL = TRUE;
    }
    return RETVAL;
}



/*-------------------------------*/
/*----------SEARCH TREE----------*/
/*-------------------------------*/
Node *SEARCH_TREE(int target, Node *root, int *targetPosition)
{
    Node *RETVAL = NULL;
    if(root != NULL)
    {

        if(SEARCH_NODE(target, root, targetPosition))
        {
            RETVAL = root;
        }
        else
        {
            SEARCH_NODE(target, root->children[*targetPosition], targetPosition);
        }
    }
    return RETVAL;
}