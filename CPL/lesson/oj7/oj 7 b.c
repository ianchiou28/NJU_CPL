#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int is_first = 1;

    while ((ch = getchar()) != EOF) {
        if (is_first) {
            putchar(toupper(ch));
            is_first = 0;
        } else {
            putchar(tolower(ch));
        }
    }
    return 0;
}