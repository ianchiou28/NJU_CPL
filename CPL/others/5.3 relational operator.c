/*优先级：算数运算符>关系运算符>赋值运算符*/
/*关系判定，结果为真输出“1"，结果为错输出”0"*/
#include <stdio.h>
void main()
{
    float a=2*2<8;
    int x=1, y=3, z=5;
    printf("%f\n",a);
    printf("%f\n",y==z>x);
}