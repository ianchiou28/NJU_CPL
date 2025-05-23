#include <stdio.h>
#include <string.h>
#include <math.h>

int prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int test(int n) {
    int original = n;
    int reversed = 0;
    while (n != 0) {
        int remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    if (prime(original) && prime(reversed)) {
        return 1;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += test(i);
    }
    
    printf("%d\n", sum);
    return 0;
}