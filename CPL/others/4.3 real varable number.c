#include <stdio.h>
#include <math.h>
/*float 单精度浮点数在机内占 4 个字节，用 32 位二进制描述。
double 双精度浮点数在机内占 8 个字节，用 64 位二进制描述。*/
/*float:32bit,小数点6-7位*/
/*double:64bit,小数点15-16位*/
/*long double:128bit,小数点18-19位*/
void main()
{
    float a,b,c;
    a=8,b=1,c=3;
    float x;/*单精度（float)变量*/
    x=a/c;/*赋值*/

    double y;
    y=a/c;

    printf("%f,%.100f\n", x,y);
}

