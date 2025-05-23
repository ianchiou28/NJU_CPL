#include <stdio.h>
#include <math.h>

int main(){
    int n;
    int a[18];
    int yu = 1;
    int huo = 0;
    int yihuo = 1;
    scanf("%d\n", &n);
    for(int i=0; i<n; i++){
        scanf("%d\n", &a[i]);
        if(a[i] == 1){
            a[i] = 0;
        }
        if(a[i] == 2){
            a[i] = 0;
        }
        if(a[i] == 4){
            a[i] = 0;
        }
        if(a[i] == 6){
            a[i] = 0;
        }
        if(a[i] == 8){
            a[i] = 0;
        }
        if(a[i] == 9){
            a[i] = 0;
        }
        if(a[i] == 10){
            a[i] = 0;
        }
        if(a[i] == 11){
            a[i] = 0;
        }
        if(a[i] == 13){
            a[i] = 0;
        }
        if(a[i] == 14){
            a[i] = 0;
        }
        if (i!=0){
            yu = a[i]&a[i-1];
            huo = a[i]|a[i-1];
            yihuo = a[i]^a[i-1];
        }
        else{
            yu = a[i];
            huo = a[i];
            yihuo = a[i];
        }

    }
    printf("%d %d %d", yu, huo, yihuo);
}