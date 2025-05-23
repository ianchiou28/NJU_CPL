#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    int d, y, h, m, s;
    char mon[100], week[100];
    scanf("%s %d %d %s %d %d %d", &mon, &d, &y, &week, &h, &m, &s);
    printf("%c%c%c %c%c%c %d %.2d:%.2d:%.2d %d", week[0],week[1],week[2], mon[0],mon[1],mon[2], d, h, m, s, y);
    return 0;
}