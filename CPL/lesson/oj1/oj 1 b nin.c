#include <stdio.h>

int main(){
    int a;
    scanf("%d",&a);
    int b = a/100;
    int c = (a-100*b)/10;
    int d = a%10;
    int e =d*100+c*10+b;
    printf("%d", e);

    return 0;
}