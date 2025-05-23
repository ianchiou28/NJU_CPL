#include <stdio.h>
#include <math.h>

int main() {
    double p, q, a, b, c, d, e, f, x1;
    scanf("%lf %lf", &p, &q);

    a = pow(q / 2.0, 2.0);
    b = pow(p / 3.0, 3.0);
    c = sqrt(a + b);
    d = -q / 2.0;
    e = cbrt(c + d);
    f = cbrt(d - c);
    x1 = e + f;

    printf("%.3lf", x1);

    return 0;
}