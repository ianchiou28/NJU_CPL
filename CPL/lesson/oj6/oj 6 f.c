#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, m, d;
    scanf("%d %d %d", &n, &m, &d);
    int grid[601][601] = {0};
    int prefix[601][601] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            prefix[i][j] = grid[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    int maxValue = INT_MIN, count = 0;
    int results[601 * 601][2];
    for (int x0 = 1; x0 <= n; ++x0) {
        for (int y0 = 1; y0 <= m; ++y0) {
            int sum = 0;
            for (int dx = -d; dx <= d; ++dx) {
                int x1 = x0 + dx, y1_start = y0 - (d - abs(dx)), y1_end = y0 + (d - abs(dx));
                x1 = (x1 < 1 || x1 > n) ? -1 : x1;
                y1_start = (y1_start < 1) ? 1 : y1_start;
                y1_end = (y1_end > m) ? m : y1_end;
                if (x1 != -1 && y1_start <= y1_end) {
                    sum += prefix[x1][y1_end] 
                         - (y1_start > 1 ? prefix[x1][y1_start - 1] : 0)
                         - (x1 > 1 ? prefix[x1 - 1][y1_end] : 0)
                         + (x1 > 1 && y1_start > 1 ? prefix[x1 - 1][y1_start - 1] : 0);
                }
            }
            if (sum > maxValue) {
                maxValue = sum;
                count = 0;
                results[count][0] = x0;
                results[count][1] = y0;
                count++;
            } else if (sum == maxValue) {
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
