#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_DIGITS 32

int convert(int x, int y[]) {
    int index = 0;
    int abs_x = abs(x);
    while (abs_x > 0) {
        y[index++] = abs_x % 3;
        abs_x /= 3;
    }
    return index;
}

void convertBalanced(int a[], int size, char b[]) {
    int carry = 0;
    for (int i = 0; i < size; i++) {
        a[i] += carry;
        carry = 0;
        if (a[i] == 2) {
            b[i] = 'Z';
            carry = 1;
        } else if (a[i] == 3) {
            b[i] = '0';
            carry = 1;
        } else {
            b[i] = '0' + a[i];
        }
    }
    if (carry == 1){
        b[size] = '1';
        size++;
    }
    b[size] = '\0';
}

int valid(const char *str) {
    int len = strlen(str);
    if (str[0] == '-') {
        for (int i = 1; i < len; i++) {
            if (!isdigit(str[i])) return 0;
        }
    } else {
        for (int i = 0; i < len; i++) {
            if (!isdigit(str[i])) return 0;
        }
    }
    return 1;
}

void Nagative(char b[]) {
    for (int i = 0; b[i] != '\0'; i++) {
        if (b[i] == '1') {
            b[i] = 'Z';
        } else if (b[i] == 'Z') {
            b[i] = '1';
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char input[MAX_DIGITS];
        scanf("%s", input);
        if (!valid(input)) {
            printf("Radix Error\n");
            continue;
        }
        int dec = atoi(input);
        if (dec == 0) {
            printf("0\n");
            continue;
        }
        int a[MAX_DIGITS] = {0};
        char b[MAX_DIGITS] = {0};
        int ternary_size = convert(dec, a);
        convertBalanced(a, ternary_size, b);
        if (dec < 0) {
            Nagative(b);
        }
        int len = strlen(b);
        for (int i = len - 1; i >= 0; i--) {
            printf("%c", b[i]);
        }
        printf("\n");
    }
    return 0;
}