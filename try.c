#include <stdio.h>
void main(){
    int x=4;
    int y=7;
    x=y++;
    y=x++;
    printf("%d%d",--x,"  ",--y);
}