#include <stdio.h>

int main(){
    int n,a,b,c,d,e;
    scanf("%d",&n);
    a=n/50;
    b=(n-50*a)/20;
    c=(n-50*a-20*b)/10;
    d=(n%10)/5;
    e=n%5;
    printf("%d\n",a);
    printf("%d\n",b);
    printf("%d\n",c);
    printf("%d\n",d);
    printf("%d\n",e);
    
    return 0;
}