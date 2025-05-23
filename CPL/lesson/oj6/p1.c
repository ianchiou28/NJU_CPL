#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);
    int grid[601][601];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    int maxValue = INT_MIN, count = 0;
    int results[601 * 601][2];
    for (int x0 = 1; x0 <= n; ++x0) {
        for (int y0 = 1; y0 <= m; ++y0) {
            int value = 0;
            for (int dx = -d; dx <= d; ++dx) {
                for (int dy = -d; dy <= d; ++dy) {
                    if (abs(dx) + abs(dy) <= d) {
                        int x = x0 + dx;
                        int y = y0 + dy;
                        if (x >= 1 && x <= n && y >= 1 && y <= m){
                            value += grid[x][y];
                        }
                    }
                }
            }
            if (value > maxValue) {
                maxValue = value;
                count = 0;
                results[count][0] = x0;
                results[count][1] = y0;
                count++;
            } else if (value == maxValue) {
                results[count][0] = x0;
                results[count][1] = y0;
                count++;
            }
        }
    }
    printf("%d %d\n", maxValue, count);
    for (int i = 0; i < count; ++i) {
        printf("%d %d\n", results[i][0], results[i][1]);
    }

    return 0;
}
