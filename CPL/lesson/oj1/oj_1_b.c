#include <stdio.h>

int main(){
    int a;
    scanf("%d", &a);
    int b = a/50;
    int c = (a-50*b)/20;
    int d = (a-50*b-20*c)/10;
    int e = (a-50*b-20*c-10*d)/5;
    int f = a%5;
    printf("%d\n%d\n%d\n%d\n%d\n", b,c,d,e,f);
    return 0;
}