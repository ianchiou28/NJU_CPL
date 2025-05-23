#include <stdio.h>
#include <math.h>

int main() {
    float P, L, T;

    scanf("%g %g %g", &P, &L, &T);
    float n = (P * pow(L, 3))/(8.314 * T);

    printf("%.4e\n", n);

    return 0;
}