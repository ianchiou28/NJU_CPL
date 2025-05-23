#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    int a[n], b[m];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    qsort(b, m, sizeof(int), compare);

    long long result = -1;
    int j = m - 1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && b[j] > t - a[i]) {
            j--;
        }
        if (j >= 0) {
            long long diff = t - a[i] - b[j];
            if (result == -1 || diff < result) {
                result = diff;
            }
        }
    }

    printf("%lld\n", result);
    return 0;
}
