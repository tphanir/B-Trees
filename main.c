#include "B.h"

void main()
{
    int arr[] = {10, 20, 30, 40, 50, 60};
    printf("%d %d %d", BINARY_SEARCH(arr, 5, 0, 5),
                    BINARY_SEARCH(arr, 699, 0, 5),
                    BINARY_SEARCH(arr, 34, 0, 5)
           );
}