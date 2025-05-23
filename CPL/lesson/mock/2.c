#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(){
    int w, n, d;
    scanf("%d %d %d\n", &w, &n, &d);
    int a[1000];
    for(int i=0; i<w; i++){
        scanf("%d ", &a[i]);
    }
    int flag;
    if(w%2==0){
        flag = w/2;
    }
    else{
        flag = (w-1)/2;
    }
    int sum = 0;
    for(int j=0; j<flag; j++){
        if(abs(a[j]-a[-j-1])==0){
            sum+=0;
        }
        else if(abs(a[j]-a[-j-1])%3==0){
            sum += (abs(a[j]-a[-j-1])/3);
        }
        else{
            for(int k=1; k<n*d; k++){
                if((a[j]+d*k)%n == a[-j-1]){
                    sum+=k;
                    break;
                }
                else if((a[j]+d*k)%n == a[j]){
                    printf("Impossible");
                    break;
                }
            }
            
        }
    }
    printf("%d", sum);
    
}