#include <stdio.h>
#include <math.h>

int main() {
    int num, ori, weishu;
    int sum = 0;
    int count = 0;

    scanf("%d", &num);
    ori = num;

    while (num != 0) {
        num /= 10;
        count++;
    }

    int ncount=count;

    num = ori;

    while (num != 0) {
        weishu = num % 10;
        sum += pow(weishu, count);
        num /= 10;
    }

    if (sum == ori) {
        printf("%d", ncount);
    } else {
        printf("0");
    }

    return 0;
}