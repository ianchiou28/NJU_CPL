#include <stdio.h>
int c , a=4;
int func(int a, int b)/*自定义函数*/
{
    c=a*b;
    a=b-1;
    b++;
    return(a+b+1); 
}
void main()/*程式运行起始点*/
{
    int b=2, p=0;
    c=1;
    p=func(b, a);
    printf("%d,%d,%d,%d\n", a,b,c,p);
}