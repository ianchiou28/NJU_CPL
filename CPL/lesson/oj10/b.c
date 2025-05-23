#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char s[21];
    int target;
}node;

int find_start(node a[], int n){
    int front = 1;
    int back = 1;
    while(front != 0 && a[front].target != 0){
        back = a[back].target;
        front = a[a[front].target].target;
        if(front == back){
            int start = 0;
            while(start != back){
                start = a[start].target;
                back = a[back].target;
            }
            return start;
        }
    }
    return -1;
}

int main(){
    int n;
    scanf("%d", &n);
    node p[n+1];
    for(int i=1; i<=n; i++){
        scanf("%s %d", p[i].s, &p[i].target);
    }
    int index = find_start(p, n);
    if(index!=-1){
        printf("%s", p[index].s);
    }
    else{
        printf("-1");
    }
}