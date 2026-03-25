#include <stdio.h>

int main()
{
    int arr[100], n, i, element,pos;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("enter the position to insert the element: ");
    scanf("%d", &pos);

    printf("Enter element to insert at position %d: ", pos);
    scanf("%d", &element);

    for(i = n; i > pos-1; i--)
    {
        arr[i] = arr[i-1];
    }

    arr[pos-1] = element;
    n++;

    printf("Array after insertion:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
 