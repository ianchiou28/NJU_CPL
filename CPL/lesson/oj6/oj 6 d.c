#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 602

char map[MAXN][MAXN][MAXN];
int count[MAXN][MAXN][MAXN];
int n;
int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

int valid(int x, int y, int z) {
    return x > 0 && x <= n && y > 0 && y <= n && z > 0 && z <= n;
}
void new(int x, int y, int z, int delta) {
    for (int d = 0; d < 6; d++) {
        int nx = x + dx[d], ny = y + dy[d], nz = z + dz[d];
        if (valid(nx, ny, nz)) {
            count[nx][ny][nz] += delta;
        }
    }
}

int main() {
    scanf("%d", &n);

    int qx = 0, qy = 0, qz = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                scanf(" %c", &map[i][j][k]);
                if (map[i][j][k] == '*') {
                    new(i, j, k, 1);
                } else if (map[i][j][k] == '?') {
                    qx = i, qy = j, qz = k;
                }
            }
        }
    }

    int without = 1, with = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (map[i][j][k] >= '0' && map[i][j][k] <= '6') {
                    if (count[i][j][k] != map[i][j][k] - '0') {
                        without = 0;
                    }
                }
            }
        }
    }

    new(qx, qy, qz, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (map[i][j][k] >= '0' && map[i][j][k] <= '6') {
                    if (count[i][j][k] != map[i][j][k] - '0') {
                        with = 0;
                    }
                }
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
        }//??地雷
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
        }//假?？?地雷，flag1?0即?情?合法
        for(int i=0;i<count;i++) {
            if(map[i_num[i]][j_num[i]][k_num[i]]-'0'!=is_mines_num2(i_num[i],j_num[i],k_num[i],n)) {
                flag2++;
            }
        }//假?？不?地雷，flag2?0即?情?合法
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