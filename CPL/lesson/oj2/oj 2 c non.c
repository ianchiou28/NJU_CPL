#include <stdio.h>
#include <math.h>

int main(){
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long m = (n%400)+(k%400);
    int i=1;
    while(i>0){
        i=i-1;
        if(n%400==0){
            printf("Leap year!\n");
        }
        else if(n%100==0){
            printf("Normal year!\n");
        }
        else if(n%4==0){
            printf("Leap year!\n");
        }
        else{
            printf("Normal year!\n");
        }
    }
    while(i==0){
        i=i-1;
        if(m%400==0){
            printf("Leap year!\n");
        }
        else if(m%100==0){
            printf("Normal year!\n");
        }
        else if(m%4==0){
            printf("Leap year!\n");
        }
        else{
            printf("Normal year!\n");
        }
        
    }
}