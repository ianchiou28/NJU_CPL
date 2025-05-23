#include <stdio.h>
#include <math.h>

int ant(int n, int a[99999]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    return 1;
}

int fw(int n, int a[99999]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 2; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    return 1;
}

int main() {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
        int n;
        int a[99999];
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        int max_val = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] > max_val) {
                max_val = a[i];
            }
        }

        if (a[n - 1] == max_val) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}

