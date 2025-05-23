#include <stdio.h>
#include <math.h>


int main() {
    double pi1, pi2;
    double a = pow(640320.0 ,3.0), b=sqrt(163);

    pi2 = log(a+744)/b;

    pi1 = 4 * (4 * atan(1.0 / 5) - atan(1.0 / 239));

    printf("%.15lf\n", pi1);
    printf("%.15lf\n", pi2);

    return 0;
}