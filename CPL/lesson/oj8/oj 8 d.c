#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *s = malloc(4096);
    char *output = malloc(20000);
    char *reserved[] = {"break", "char", "const", "double", "enum", "extern", "float", "goto", "int", "long", "return", "static", "struct", "typedef", "union", "void"};
    char *operators[] = {"+", "-", "*", "/", ">", "<", ">=", "<=", "==", "=", "!="};

    while (scanf("%s", s) != EOF) {
        for (char *pos = strchr(s, ';'); pos; s = pos + 1, pos = strchr(s, ';')) {
            *pos = 0;

            // Check for integer
            int i;
            for (i = 0; s[i] != '\0'; i++) {
                if (!isdigit(s[i])) {
                    break;
                }
            }
            if (s[i] == '\0') {
                strcat(output, "integer ");
                goto next_token;
            }

            // Check for reserved word
            for (int i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++) {
                if (strcmp(s, reserved[i]) == 0) {
                    strcat(output, "reserved ");
                    goto next_token;
                }
            }

            // Check for operator
            for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
                if (strcmp(s, operators[i]) == 0) {
                    strcat(output, "operator ");
                    goto next_token;
                }
            }

            // Check for float
            int dot_count = 0;
            for (int i = 0; s[i] != '\0'; i++) {
                if (isdigit(s[i])) {
                    continue;
                } else if (s[i] == '.') {
                    dot_count++;
                    if (dot_count > 1) {
                        break;
                    }
                } else {
                    break;
                }
            }
            if (dot_count == 1 && s[strlen(s) - 1] != '.') {
                strcat(output, "float ");
                goto next_token;
            }

            // Check for variable
            if (isalpha(s[0]) || s[0] == '_') {
                for (int i = 1; s[i] != '\0'; i++) {
                    if (!isalnum(s[i]) && s[i] != '_') {
                        break;
                    }
                }
                strcat(output, "variable ");
                goto next_token;
            }

            printf("Compile Error\n");
            exit(EXIT_SUCCESS);

        next_token:
            strcat(output, "\n");
        }

        // Process the last token if it doesn't end with a semicolon
        if (*s) {
            // Same logic as above to check token type
            // ...
        }
    }

    if (*s) {
        printf("Compile Error\n");
        exit(1);
    }

    printf("%s", output);

    free(s);
    free(output);
    return 0;
}