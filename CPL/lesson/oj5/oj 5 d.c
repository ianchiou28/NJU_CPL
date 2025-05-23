#include <stdio.h>
#include <string.h>

char *ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
char *thousands[] = {"", "thousand", "million", "billion"};

void numberToWordsHelper(int num) {
    if (num == 0) return;
    if (num >= 100) {
        printf("%s hundred", ones[num / 100]);
        num %= 100;
        if (num != 0) printf(" and ");
    }
    if (num >= 20) {
        printf("%s", tens[num / 10]);
        if (num % 10 != 0) printf("-%s", ones[num % 10]);
    } else if (num > 0) {
        printf("%s", ones[num]);
    }
}

void numberToWords(int num) {
    if (num == 0) {
        printf("zero");
        return;
    }
    if (num < 0) {
        printf("minus ");
        num = -num;
    }

    int segments[4] = {0}, i = 0;
    while (num > 0) {
        segments[i++] = num % 1000;
        num /= 1000;
    }

    for (int j = i - 1; j >= 0; j--) {
        if (segments[j] != 0) {
            numberToWordsHelper(segments[j]);
            if (strlen(thousands[j]) > 0) printf(" %s", thousands[j]);
            if (j > 0) printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int num;
    scanf("%d", &num);
    numberToWords(num);
    return 0;
}
