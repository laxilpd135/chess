#include <stdio.h>
void main(){    
    int num,count;        
    printf("Enter a number: ");
    scanf("%d",&num);   
    int arr[num];

    for(int i=0; i<num; i++){
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
        count++;
    }
    printf("Array before insertion: ");
    for(int i=0; i<num; i++){
        printf("%d ",arr[i]);
    }   
    printf("\nEnter the element to be inserted: ");
    int element;
    scanf("%d",&element);   
    for(int i=0; i<num; i++){
        arr[i+1]=arr[i];
    }   
    arr[0]=element;
    count++;
    printf("Array after insertion: ");
    for(int i=0; i<count; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}