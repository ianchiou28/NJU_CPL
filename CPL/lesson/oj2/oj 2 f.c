#include <stdio.h>

int main() {
    int n, current = 0, total = 0;
    int counts[100001];
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        scanf("%d", &counts[i]);
    }

    for (int s = 0; s <= n; s++) {
        if (current < s) {
            int need = s - current;
            total += need;
            current += need;
        }
        current += counts[s];
    }

    printf("%d\n", total);

    return 0;
}