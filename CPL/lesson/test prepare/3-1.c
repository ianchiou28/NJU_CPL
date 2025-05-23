#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d\n", &n);
    char a[n];
    int ret = 0;
    for(int i=0; i<n; i++){
        scanf("%c", &a[i]);
    }
    for(int i=0; i<n; i++){
        if(a[i] == a[n-i-1]){
            ret = -1;
            break;
        }
        else{
            ret = 0;
        }
    }
    if(ret == -1){
        printf("NO");
    }
    else{
        printf("YES");
    }

    return 0;
}