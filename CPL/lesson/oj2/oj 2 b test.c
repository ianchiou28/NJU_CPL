#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int numbers[20005];
    for (int i = 0; i < 2 * n - 1; i++) {
        scanf("%d", &numbers[i]);
    }

    int j, k;
    k = 2 * n - 2;  // Initialize k to the last index

    for (j = 0; j < k; j++) {
        while (k > j && numbers[j] != numbers[k]) {
            k--;
        }

        if (k == j + 1) {
            printf("%d\n", numbers[j]);
            break;
        }
    }

    return 0;
}