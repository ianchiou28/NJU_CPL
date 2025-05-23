#include <stdio.h>

int main(){
    int a;

    scanf("%d", &a);
    char ascii_char = (char)a;

    printf("%d %c", a, ascii_char);
    return 0;
}