#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_method(int *c, int d, char *s) {
    int first = 1;
    for (int i = d; i >= 0; i--) {
        if (c[i] != 0) {
            if (!first && c[i] > 0) {
                printf("+");
            }
            if (i == 0) {
                printf("%d", c[i]);
            } else if (c[i] == 1) {
                if (i > 1) printf("%s^%d", s, i);
                else printf("%s", s);
            } else if (c[i] == -1) {
                printf("-");
                if (i > 1) printf("%s^%d", s, i);
                else printf("%s", s);
            } else {
                if (i > 1) printf("%d%s^%d", c[i], s, i);
                else printf("%d%s", c[i], s);
            }
            first = 0;
        }
    }
    if (first) {
        printf("0");
    }
    printf("\n");
}

int main() {
    int p1, p2;
    scanf("%d %d", &p1, &p2);

    char s[11];
    scanf("%s", s);

    int a[10005] = {0}, b[10005] = {0};
    int sum[10005] = {0}, diff[10005] = {0}, prod[20005] = {0};

    for (int i = 0; i <= p1; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i <= p2; i++) {
        scanf("%d", &b[i]);
    }

    int maxi = (p1 > p2) ? p1 : p2;

    for (int i = 0; i <= maxi; i++) {
        int c1 = (i <= p1) ? a[p1 - i] : 0;
        int c2 = (i <= p2) ? b[p2 - i] : 0;
        sum[i] = c1 + c2;
        diff[i] = c1 - c2;
    }

    for (int i = 0; i <= p1; i++) {
        for (int j = 0; j <= p2; j++) {
            prod[(i + j)] += a[p1 - i] * b[p2 - j];
        }
    }


    print_method(sum, maxi, s);
    print_method(diff, maxi, s);
    print_method(prod, p1 + p2, s);

    return 0;
}
