#include <stdio.h>

void main() {
    FILE *fp;
    char ch;
    fp = fopen("Quine.c", "r");
    if (fp == NULL) {
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);

    return 0;
}