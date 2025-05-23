#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_last(char *str, int n) {
    int len = strlen(str);
    if (n == len) {
        *str = '\0';
    } else {
        *(str + len - n) = '\0';
    }
    return str;
}

int min(int x, int y){
    return (x >= y) ? y : x;
}

int main() {
    int t;
    scanf("%d\n", &t);

    for (int i = 0; i < t; i++) {
        char *s1 = (char *)malloc(1005 * sizeof(char));
        char *s2 = (char *)malloc(1005 * sizeof(char));

        scanf("%s %s\n", s1, s2);
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int flag = 0;
        for (int j = 0; j < min(len1, len2); j++) {
            int result = strncmp(s1, s2, j + 1);
            if (result == 0) {
                flag = j + 1;
            }
        }
        remove_last(s1, flag);
        strcat(s1, s2);
        printf("%s\n", s1);
        free(s1);
        free(s2);
    }
    return 0;
}
