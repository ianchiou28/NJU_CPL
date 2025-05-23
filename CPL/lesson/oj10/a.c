#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int size;
    int parent;
} node;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    node a[100000];
    int out = 1;
    int m = 1 << n;

    a[0].id = 0;
    a[0].size = m;
    a[0].parent = -1;

    for (int i = 0; i < q; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'A') {
            int id, size;
            scanf("%d %d", &id, &size);

            int b = 1;
            while (b < size) {
                b *= 2;
            }

            int map = 0;
            for (int j = 0; j < out; j++) {
                if (a[j].id == 0 && a[j].size >= b) {
                    while (a[j].size > b) {
                        int new = a[j].size / 2;
                        for (int k = out; k > j + 1; k--) {
                            a[k] = a[k - 1];
                        }
                        a[j].size = new;
                        a[j + 1].id = 0;
                        a[j + 1].size = new;
                        a[j + 1].parent = j;
                        out++;
                    }
                    a[j].id = id;
                    map = 1;
                    break;
                }
            }
            if (!map) {
                printf(0);
            }
        } else if (op == 'Q') {
            printf("%d\n", out);
            for (int j = 0; j < out; j++) {
                printf("%d ", a[j].id);
            }
            printf("\n");
        }
    }

    return 0;
}
