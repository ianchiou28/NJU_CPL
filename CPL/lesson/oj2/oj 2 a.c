#include <stdio.h>
#include <math.h>

int main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if(a+b<c){
        printf("not triangle");
    }
    else if(a==b, b==c){
        printf("equilateral triangle");
    }
    else if((a*a+b*b)==c*c){
        printf("right triangle");
    }
    else if((a*a+b*b)>c*c){
        printf("acute ");
        if(a==b){
            printf("isosceles ");
        }
        printf("triangle");
    }
    else if((a*a+b*b)<c*c){
        printf("obtuse ");
        if(a==b){
            printf("isosceles ");
        }
        printf("triangle");
    }
    return 0;
}