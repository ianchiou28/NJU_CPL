#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RULE_LEN 128
#define MAX_CMD_LEN 1024

int none_option(const char *rules, char option);
int value(const char *rules, char option);
void parse(const char *rules, char *cmd);

int main() {
    char rules[MAX_RULE_LEN + 1];
    char command[MAX_CMD_LEN + 1];

    scanf("%s\n", rules);
    fgets(command, MAX_CMD_LEN, stdin);
    parse(rules, command);

    return 0;
}

int none_option(const char *rules, char option) {
    for (int i = 0; rules[i] != '\0'; i++) {
        if (rules[i] == option) {
            return 1;
        }
    }
    return 0;
}

int value(const char *rules, char option) {
    for (int i = 0; rules[i] != '\0'; ++i) {
        if (rules[i] == option && rules[i + 1] == ':') {
            return 1;
        }
    }
    return 0;
}

void parse(const char *rules, char *cmd) {
    char *tokens[256];
    int token_count = 0;
    char *prog_name = NULL;
    char *token = strtok(cmd, " \n");
    while (token) {
        tokens[token_count++] = token;
        token = strtok(NULL, " \n");
    }

    prog_name = tokens[0];
    printf("%s\n", prog_name);
    for (int i = 1; i < token_count; i++) {
        if (tokens[i][0] == '-') {
            char option = tokens[i][1];
            if (!none_option(rules, option)) {
                printf("%s: invalid option -- '%c'\n", prog_name, option);
                return;
            }
            if (value(rules, option)) {
                if  (tokens[i + 1][0] == '-') {
                    printf("%s: invalid option -- '%c'\n", prog_name, tokens[i + 1][1]);
                    return;
                } else if (i + 1 >= token_count || tokens[i + 1][0] == '-') {
                    printf("%s: option requires an argument -- '%c'\n", prog_name, option);
                    return;
                } else {
                    printf("%c=%s\n", option, tokens[++i]);
                }
            } else {
                printf("%c\n", option);
            }
        } else {
            continue;
        }
    }
}
