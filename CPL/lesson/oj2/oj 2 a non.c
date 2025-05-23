#include <stdio.h>
#include <math.h>

int main(){
    int h, m;
    scanf("%d:%d", &h, &m);
    if(h==12){
        printf("%.2d:%.2d p.m.", h, m);
    }
    else if(h>12){
        printf("%.2d:%.2d p.m.", (h-12), m);
    }
    else{
        printf("%.2d:%.2d a.m.", h, m);
    }
}