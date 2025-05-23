#include <stdio.h>
#include <stdbool.h>

int min(int a, int b) {
    return a > b ? b : a;
}

bool islin(char grid[][101], int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        if (grid[x + i][y - i] != '/' || grid[x + i][y + i + 1] != '\\') {
            return false;
        }
        if (grid[x + i + size][y - size + i + 1] != '\\' || grid[x + i + size][y + size - i] != '/') {
            return false;
        }
    }
    return true;
}

int countt(char grid[][101], int R, int C) {
    int count = 0;
    int minSize = min(R, C) / 2;

    for (int size = 1; size <= minSize; size++) {
        for (int i = 0; i <= R - size*2; i++) {
            for (int j = size-1; j < C - size; j++) {
                if (islin(grid, i, j, size)) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    int R, C;
    char grid[101][101];

    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", grid[i]);
    }

    // for(int i=0; i<R; i++)
    //     printf("%s\n", grid[i]);

    int result = countt(grid, R, C);
    printf("%d\n", result);

    return 0;
}