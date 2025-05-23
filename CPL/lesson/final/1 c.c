#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool win(char s[20][20], char color) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (s[i][j] == color) {
                if (i + 4 < 20 && s[i + 1][j] == color && s[i + 2][j] == color && s[i + 3][j] == color && s[i + 4][j] == color) {
                    return true;
                }
                if (j + 4 < 20 && s[i][j + 1] == color && s[i][j + 2] == color && s[i][j + 3] == color && s[i][j + 4] == color) {
                    return true;
                }
                if (i + 4 < 20 && j + 4 < 20 && s[i + 1][j + 1] == color && s[i + 2][j + 2] == color && s[i + 3][j + 3] == color && s[i + 4][j + 4] == color) {
                    return true;
                }
                if (i + 4 < 20 && j - 4 >= 0 && s[i + 1][j - 1] == color && s[i + 2][j - 2] == color && s[i + 3][j - 3] == color && s[i + 4][j - 4] == color) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char s[20][20];
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                scanf(" %c", &s[i][j]);
            }
        }
        char black = '#';
        char white = '*';
        bool found_result = false;
        for (int i = 0; i < 20 && !found_result; i++) {
            for (int j = 0; j < 20 && !found_result; j++) {
                if (s[i][j] == '_') {
                    s[i][j] = black;
                    if (win(s, black)) {
                        printf("Win\n");
                        found_result = true;
                        break;
                    }
                    for (int k = 0; k < 20 && !found_result; k++) {
                        for (int l = 0; l < 20 && !found_result; l++) {
                            if (s[k][l] == '_') {
                                s[k][l] = white;
                                if (win(s, white)) {
                                    printf("Lose\n");
                                    found_result = true;
                                    break;
                                }
                                for (int m = 0; m < 20 && !found_result; m++) {
                                    for (int n = 0; n < 20 && !found_result; n++) {
                                        if (s[m][n] == '_') {
                                            s[m][n] = black;
                                            if (win(s, black)) {
                                                printf("Win\n");
                                                found_result = true;
                                                break;
                                            }
                                            s[m][n] = '_';
                                        }
                                    }
                                }
                                s[k][l] = '_';
                            }
                        }
                    }
                    s[i][j] = '_';
                }
            }
        }
        if (!found_result) {
            printf("Not Sure\n");
        }
    }
    return 0;
}