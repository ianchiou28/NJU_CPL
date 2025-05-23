#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>





int shi_to_three(const char*str){
    int num_str=atoi(str);
    int yu_num=0;
    int sanjinzhi=0;
    int  j=0;
    while(num_str>0){
        yu_num=num_str%3;
        num_str=num_str/3;
        sanjinzhi=sanjinzhi+yu_num*pow(10,j);
        j++;
    }
    return sanjinzhi;
}
char a[15];
void three_to_pinheng(int a[], int size, char b[]) {
    int carry = 0;
    for (int i = 0; i < size; i++) {
        a[i] += carry;
        carry = 0;
        if (a[i] == 2) {
            b[i] = 'Z';
            carry = 1;
        } else if (a[i] == 3) {
            b[i] = '0';
            carry = 1;
        } else {
            b[i] = '0' + a[i];
        }
    }
    if (carry == 1){
        b[size] = '1';
        size++;
    }
    b[size] = '\0';
}

int main(){
    
    scanf("%s",&a);
    int b=shi_to_three(a);
    char str_num=three_to_pinheng(b);
    printf("%s",str_num);
    return 0;
}