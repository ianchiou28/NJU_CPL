#include <stdio.h>
#include <ctype.h>

char map[605][605][605];


int vectors[6][3]={{0,0,1},{0,1,0},{1,0,0},{0,-1,0},{-1,0,0},{0,0,-1}};

int  is_valid (int i,int j,int k, const int n) {
    for(int x=0;x<6;x++) {
        int new_i=vectors[x][0]+i;
        int new_j=vectors[x][1]+j;
        int new_k=vectors[x][2]+k;
        if(new_i >= 0 && new_i < n && new_j >= 0 &&new_j < n && new_k >=0&& new_k < n && isdigit(map[new_i][new_j][new_k])!=0) {
            return 0;
        }
    }
    return 1;
}
int is_mines_num1(int i,int j,int k, const int n) {
    int count=0;
    for(int x=0;x<6;x++) {
        int new_i=vectors[x][0]+i;
        int new_j=vectors[x][1]+j;
        int new_k=vectors[x][2]+k;
        if(new_i >= 0 && new_i < n && new_j >= 0 &&new_j < n && new_k >=0&& new_k < n && map[new_i][new_j][new_k] == '*') {
            count++;}
        else if(new_i >= 0 && new_i < n && new_j >= 0 &&new_j < n && new_k >=0&& new_k < n && map[new_i][new_j][new_k] == '?') {
            count++;
        }
    }
    return count;
}

int is_mines_num2(int i,int j,int k, const int n) {
    int count=0;
    for(int x=0;x<6;x++) {
        int new_i=vectors[x][0]+i;
        int new_j=vectors[x][1]+j;
        int new_k=vectors[x][2]+k;
        if(new_i >= 0 && new_i < n && new_j >= 0 &&new_j < n && new_k >=0&& new_k < n && map[new_i][new_j][new_k] == '*') {
            count++;}
    }
    return count;
}

int i_num[43200001],j_num[43200001],k_num[43200001];
int i_what,j_what,k_what;
char scene_str[217000005];

int main() {
    int n;
    scanf("%d\n", &n);
    scanf("%s", scene_str);
    int count = 0;
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                map[i][j][k] = scene_str[index];
                if (isdigit(scene_str[index])) {
                    i_num[count] = i;
                    j_num[count] = j;
                    k_num[count] = k;
                    count++;
                }
                else if (scene_str[index] == '?') {
                    i_what = i;
                    j_what = j;
                    k_what = k;
                }
                index++;
            }
        }
    }
    int flag1=0;
    int flag2=0;
    if(is_valid(i_what,j_what,k_what,n)) {
        for(int i=0;i<count;i++) {
            if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num1(i_num[i],j_num[i],k_num[i],n)) {
                flag1++;
            }
        }
        if(flag1==0) {
            printf("valid\n");
            printf("%d\n",is_mines_num1(i_what,j_what,k_what,n));
        }
        else {
            printf("invalid\n");
            for(int i=0;i<count;i++) {
                if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num1(i_num[i],j_num[i],k_num[i],n)) {
                    printf("%d %d %d\n",i_num[i]+1,j_num[i]+1,k_num[i]+1);
                }
            }
        }
    }
    else {
        for(int i=0;i<count;i++) {
            if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num1(i_num[i],j_num[i],k_num[i],n)) {
                flag1++;
            }
        }
        for(int i=0;i<count;i++) {
            if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num2(i_num[i],j_num[i],k_num[i],n)) {
                flag2++;
            }
        }
        if(flag2==0) {
            printf("valid\n");
            printf("%d\n",is_mines_num2(i_what,j_what,k_what,n));
        }
        else if(flag1==0) {
            printf("valid\n");
            printf("*\n");
        }
        else {
            printf("invalid\n");
            for(int i=0;i<count;i++) {
                if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num1(i_num[i],j_num[i],k_num[i],n)) {
                    printf("%d %d %d\n",i_num[i]+1,j_num[i]+1,k_num[i]+1);
                }
            }
        }
    }
    return 0;
}