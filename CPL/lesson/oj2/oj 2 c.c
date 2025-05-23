#include <stdio.h>
#include <math.h>

int main(){
    int sum = 0;
    int f = 1;
    int n;
    scanf("%d", &n);
    for(int i = 1; i<=n; i++){
        f = (f*i)%10007;
        sum = (sum + f) % 10007;
    }
    
    printf("%d", sum);
    return 0;
}