#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[n];

    for (int j = 0; j < n; j++) {
        scanf("%c", &s[j]);
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            s[i] = s[n - i];
        }
    }

    printf("%s\n", s);

    return 0;
}