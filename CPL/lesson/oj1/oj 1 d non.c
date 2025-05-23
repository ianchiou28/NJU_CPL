#include <stdio.h>
#include <math.h>

int main(){
    double m;
    double R;
    scanf("%lf %lf", &m, &R);
    double gravity = (6.674e-11) * 77.15 * m /(R*R);    
    printf("%.3e", gravity);
    return 0;
}