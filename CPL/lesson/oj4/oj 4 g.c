#include <stdio.h>
#include <stdbool.h>

#define MAX_N 501
#define MAX_M 501
#define MAX_VAL 250001

int input[MAX_N][MAX_M];
int output[MAX_VAL] = {0};

typedef struct {
    int row, col;
} at;

at p[MAX_VAL][2];
int count_p[MAX_VAL] = {0};

void processed(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val = input[i][j];
            if (val > 0 && count_p[val] < 2) {
                p[val][count_p[val]].row = i;
                p[val][count_p[val]].col = j;
                count_p[val]++;
            }
        }
    }
}

bool left(int i, int j) {
    for (int k = j - 1; k > 0; k--) {
        if (input[i][k] != 0) return false;
    }
    return true;
}

bool right(int i, int j, int m) {
    for (int k = j + 1; k <= m; k++) {
        if (input[i][k] != 0) return false;
    }
    return true;
}

bool up(int i, int j) {
    for (int k = i - 1; k > 0; k--) {
        if (input[k][j] != 0) return false;
    }
    return true;
}

bool down(int i, int j, int n) {
    for (int k = i + 1; k <= n; k++) {
        if (input[k][j] != 0) return false;
    }
    return true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &input[i][j]);
        }
    }

    processed(n, m);

    for (int x = 1; x <= (n * m) / 2; x++) {
        if (count_p[x] < 2) continue;

        int i1 = p[x][0].row;
        int j1 = p[x][0].col;
        int i2 = p[x][1].row;
        int j2 = p[x][1].col;

        bool left_clear = left(i1, j1) && left(i2, j2);
        bool right_clear = right(i1, j1, m) && right(i2, j2, m);
        bool up_clear = up(i1, j1) && up(i2, j2);
        bool down_clear = down(i1, j1, n) && down(i2, j2, n);

        if (left_clear || right_clear || up_clear || down_clear) {
            output[x] = 1;
            input[i1][j1] = 0;
            input[i2][j2] = 0;
        }
    }

    for (int b = 1; b <= (n * m) / 2; b++) {
        if (output[b] == 1) printf("%d ", b);
    }

    return 0;
}