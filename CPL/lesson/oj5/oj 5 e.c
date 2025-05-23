#include <stdio.h>
#include <math.h>

int convert(int x, int B) {
    return (x / 10) * B + (x % 10);
}

int min_base(int B, int x) {
    int max = x % 10 > x / 10 ? x % 10 : x / 10;
    if (B <= max) {
        B = max + 1;
    }
    return B;
}

int main() {
    int p, q, r;
    scanf("%d%d%d", &p, &q, &r);
    
    int B = 2;
    B = min_base(B, p);
    B = min_base(B, q);
    B = min_base(B, r);

    while (B <= 40) {
        int p1 = convert(p, B);
        int q1 = convert(q, B);
        int r1 = convert(r, B);
        
        if (p1 * q1 == r1) {
            printf("%d", B);
            return 0;
        }
        B++;
    }
    
    printf("0");
    return 0;
}
