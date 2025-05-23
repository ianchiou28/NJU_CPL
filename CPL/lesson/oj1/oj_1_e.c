#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    int year, month, day;
    scanf("%d %d %d", &year, &month, &day);
    int a = floor((14-month)/12);
    int y = year+4800-a;
    int m = month+12*a-3;

    int JDN = day+floor((153*m+2)/5)+365*y+floor(y/4)-floor(y/100)+floor(y/400)-32045;

    printf("%d", JDN);

    return 0;
}