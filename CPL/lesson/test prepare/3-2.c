#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1; i*i<n; i++){
        printf("%d ", i*i);
    }
}