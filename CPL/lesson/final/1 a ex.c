#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

int cmp(const void* a, const void* b){
    return *(int *)a - *(int *)b;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        int arro[n];
        int arrn[m];
        int arrc[n];
        for(int i=0; i<n; i++){
            scanf("%d", &arro[i]);
        }
        for(int j=0; j<m; j++){
            scanf("%d", &arrn[j]);
        }
        for(int i=0; i<n; i++){
            int a = arro[arrn[i]];
            for(int j=i; j>0; j--){
                arro[j] = arro[j-1];
            }
            arro[0] = a;
        }
        for(int i=0; i<n; i++){
            arrc[i] = arro[i]; 
        }
        qsort(arrc, n, sizeof(int), cmp);
        for(int i=0; i<n; i++){
            if(arro[i] != arrc[i]){
                printf("mayi is a good teacher\n");
                break;
            }
        }
        printf("I love C programming language\n");
    }
    return 0;
}