#include <stdio.h>
#include <math.h>

int main(){
    int m;
    scanf("%d", &m);
    if(m>100){
        printf("Wrong score");
    }
    else if(m>=90){
        printf("A");
    }
    else if(m>=80){
        printf("B");
    }
    else if(m>=70){
        printf("C");
    }
    else if(m>=60){
        printf("D");
    }
    else{
        printf("F");
    }
}