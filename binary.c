#include <stdio.h>
void main(){
    int index=0;
    int remainder;
    int arr[100];
    int num;
    printf("Enter a number: ");
    scanf("%d",&num);   
    while(num>0){
        remainder=num%2;
        arr[index]=remainder;
        num=num/2;
        index++;
    }
    printf("Binary representation: ");
    for(int i=index-1; i>=0; i--){
        printf("%d",arr[i]);
    }
    printf("\n");
}