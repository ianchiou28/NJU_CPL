#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_sorted(int *arr, int n){
    for(int i=0; i<n-1; i++){
        if(arr[i]>arr[i+1]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int t;
    scanf("%d\n", &t);
    while(t--){
        int n, m;
        scanf("%d %d\n", &n, &m);
        int *a = (int*)malloc(n * sizeof(int));
        int *b = (int*)malloc(m * sizeof(int));
        for(int i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < m; i++){
            scanf("%d", &b[i]);
        }
        for(int i=0; i<m; i++){
            int x = b[i]-1;
            int temp = a[x];
            for(int j=x; j>0; j--){
                a[j] = a[j-1];
            }
            a[0] = temp;
        }
        if(is_sorted(a, n)){
            printf("I love C programming language\n");
        } else {
            printf("mayi is a good teacher\n");
        }

        free(a);
        free(b);
    }

    return 0;
}

