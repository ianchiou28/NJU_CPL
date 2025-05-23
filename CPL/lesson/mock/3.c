#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    int n, m;
    scanf("%d %d\n", &n, &m);
    int a[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char p;
            scanf("%c", &p);
            if(p == 'L'){
                a[i][j] = 1;
            }
            else if(p=='R'){
                a[i][j] = -1;
            }
            else if(p=='U'){
                a[i][j]=2;
            }
            else if(p == 'D'){
                a[i][j] = -2;
            }
            else{
                a[i][j] = 0;
            }
        }
    }
    int sum = 0;
    int flag = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]!=0){
                flag = flag*(-1);
            }
            sum+=a[i][j];
        }                                                                                                                                          
    }

    if(flag!=1){
        printf("-1");
        return 0;
    }
    int result = abs(sum);
    printf("%d", result);
    
    return 0;

}