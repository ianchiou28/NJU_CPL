#include <stdio.h>
#include <math.h>

int calzhi(int n, int m[n][n]) {
    if (n == 1) {
        return m[0][0];
    } else if (n == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    } else {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int temp[n - 1][n - 1];
            for (int j = 1; j < n; j++) {
                for (int k = 0, l = 0; k < n; k++) {
                    if (k != i) {
                        temp[j - 1][l++] = m[j][k];
                    }
                }
            }
            sum += m[0][i] * pow(-1, i) * calzhi(n - 1, temp);
        }
        return sum;
    }
}

void yuzi(int n, int m[n][n], int t[n - 1][n - 1], int p, int q) {
    int i = 0, j = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r != p && c != q) {
                t[i][j++] = m[r][c];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void bansui(int n, int m[n][n], int adj[n][n]) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }

    int temp[n - 1][n - 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            yuzi(n, m, temp, i, j);
            adj[j][i] = pow(-1, i + j) * calzhi(n - 1, temp);
        }
    }
}

void ni(int n, int m[n][n], int adj[n][n]) {
    int det = calzhi(n, m);
    if (det == 0) {
        printf("Äæ¾ØÕó²»´æÔÚ\n");
        return;
    }

    int temp[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = adj[i][j] / det;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", temp[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int det = calzhi(n, matrix);
    printf("ÐÐÁÐÊ½Öµ£º %d\n", det);
    int adj[n][n];
    bansui(n, matrix, adj);
    printf("°éËæ¾ØÕó£º\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", adj[i][j]);
        }
        printf("\n");
    }
    printf("Äæ¾ØÕó£º\n");
    ni(n, matrix, adj);


    return 0;
}