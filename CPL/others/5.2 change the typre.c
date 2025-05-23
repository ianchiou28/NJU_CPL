/*在算术表达式中，可转换表达类型*/
#include <stdio.h>
void main()
{
    int a=1,b=6,c=9;
    float x=13.565, y=84582.658, z;
    z=(x+a)/c+(int)y%c*1.38+b;
    printf("%f\n",z);
}