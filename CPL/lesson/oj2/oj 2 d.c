#include <stdio.h>
#include <string.h>

int main() {
    int num;
    char *ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten","eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    scanf("%d", &num);
    if (num == 0) {
        printf("zero");
        return 0;
    }
    if(num == 100){
        printf("one hundred");
        return 0;
    }
    if (num >= 100) {
        printf("%s hundred", ones[num / 100]);
        num %= 100;
        if (num > 0) {
            printf(" and ");
        }
    }
    if (num >= 20) {
        printf("%s", tens[(num / 10) - 2]);
        if (num % 10 != 0) {
            printf("-%s", ones[num % 10]);
        }
    } else {
        printf("%s", ones[num]);
    }
    return 0;
}