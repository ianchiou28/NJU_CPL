#include <stdio.h>
#include <ctype.h>

#define MAX_N 605

char map[MAX_N][MAX_N][MAX_N];
int vectors[6][3] = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {0, -1, 0}, {-1, 0, 0}, {0, 0, -1}};
int i_num[43200001], j_num[43200001], k_num[43200001];
int i_what, j_what, k_what;
char scene_str[217000005];

int is_in_bounds(int i, int j, int k, int n) {
    return i >= 0 && i < n && j >= 0 && j < n && k >= 0 && k < n;
}

typedef int (*ConditionFunc)(char);

void neighgbor(int i, int j, int k, int n, int *count, ConditionFunc condition) {
    for (int x = 0; x < 6; x++) {
        int new_i = i + vectors[x][0];
        int new_j = j + vectors[x][1];
        int new_k = k + vectors[x][2];
        if (is_in_bounds(new_i, new_j, new_k, n) && condition(map[new_i][new_j][new_k])) {
            (*count)++;
        }
    }
}

int is_valid(int i, int j, int k, int n) {
    for (int x = 0; x < 6; x++) {
        int new_i = i + vectors[x][0];
        int new_j = j + vectors[x][1];
        int new_k = k + vectors[x][2];
        if (is_in_bounds(new_i, new_j, new_k, n) && isdigit(map[new_i][new_j][new_k])) {
            return 0;
        }
    }
    return 1;
}

int is_mine(char c) {
    return c == '*';
}

int mine_question(char c) {
    return c == '*' || c == '?';
}

int count_mines(int i, int j, int k, int n, char type) {
    int count = 0;
    if (type == '*') {
        neighgbor(i, j, k, n, &count, is_mine);
    } else {
        neighgbor(i, j, k, n, &count, mine_question);
    }
    return count;
}

int main() {
    int n;
    scanf("%d\n", &n);
    scanf("%s", scene_str);

    int count = 0, index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                map[i][j][k] = scene_str[index];
                if (isdigit(map[i][j][k])) {
                    i_num[count] = i;
                    j_num[count] = j;
                    k_num[count] = k;
                    count++;
                } else if (map[i][j][k] == '?') {
                    i_what = i;
                    j_what = j;
                    k_what = k;
                }
                index++;
            }
        }
    }

    int flag1 = 0, flag2 = 0;
    if (is_valid(i_what, j_what, k_what, n)) {
        for (int i = 0; i < count; i++) {
            if (map[i_num[i]][j_num[i]][k_num[i]] - '0' != count_mines(i_num[i], j_num[i], k_num[i], n, '?')) {
                flag1++;
            }
        }
        if (flag1 == 0) {
            printf("valid\n");
            printf("%d\n", count_mines(i_what, j_what, k_what, n, '?'));
        } else {
            printf("invalid\n");
            for (int i = 0; i < count; i++) {
                if (map[i_num[i]][j_num[i]][k_num[i]] - '0' != count_mines(i_num[i], j_num[i], k_num[i], n, '?')) {
                    printf("%d %d %d\n", i_num[i] + 1, j_num[i] + 1, k_num[i] + 1);
                }
            }
        }
    } else {
        for (int i = 0; i < count; i++) {
            if (map[i_num[i]][j_num[i]][k_num[i]] - '0' != count_mines(i_num[i], j_num[i], k_num[i], n, '?')) {
                flag1++;
            }
            if (map[i_num[i]][j_num[i]][k_num[i]] - '0' != count_mines(i_num[i], j_num[i], k_num[i], n, '*')) {
                flag2++;
            }
        }

        if (flag2 == 0) {
            printf("valid\n");
            printf("%d\n", count_mines(i_what, j_what, k_what, n, '*'));
        } else if (flag1 == 0) {
            printf("valid\n");
            printf("*\n");
        } else {
            printf("invalid\n");
            for (int i = 0; i < count; i++) {
                if (map[i_num[i]][j_num[i]][k_num[i]] - '0' != count_mines(i_num[i], j_num[i], k_num[i], n, '?')) {
                    printf("%d %d %d\n", i_num[i] + 1, j_num[i] + 1, k_num[i] + 1);
                }
            }
        }
    }

    return 0;
}