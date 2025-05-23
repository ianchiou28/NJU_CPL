#include <stdio.h>

void main() {
    int x;
    scanf("%d", &x);

    if (x > 20) {
        printf("大了\n");
    } else if (x < 20) {
        printf("小了\n");
    } else {
        printf("猜对了\n");
    }

    return 0;
}