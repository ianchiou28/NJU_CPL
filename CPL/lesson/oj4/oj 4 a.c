#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int change(int n){
    int bi = 0;
    int r, i = 1, step = 1;
    while (n!=0){
        r = n%2;
        n /= 2;
        bi += r*i;
        i *= 10;
    }
    return bi;
}
int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", (a&b));
    printf("%d\n", (a|b));
    printf("%d\n", (a^b));
    printf("%d\n", (~a));
    printf("%d\n", (a<<b));
    printf("%d\n", (a>>b));
    printf("%d\n", (a >> b) & 1);
    int c = 0;
    while (a) {
        c += a & 1;
        a >>= 1;
    }
    printf("%d", c);

    return 0;
}