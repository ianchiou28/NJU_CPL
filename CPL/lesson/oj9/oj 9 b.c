#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **strsplit(char *str, char *d, int *count) {
    char **result = malloc(10 * sizeof(char *));
    int capacity = 10;
    char *token;
    int idx = 0;

    token = strtok(str, d);
    while (token != NULL) {
        if (idx >= capacity) {
            capacity *= 2;
            result = realloc(result, capacity * sizeof(char *));
        }
        result[idx] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(result[idx], token);
        idx++;
        token = strtok(NULL, d);
    }

    *count = idx;
    return result;
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char input[1024];
    char d[2];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    fgets(d, sizeof(d), stdin);
    d[strcspn(d, "\n")] = '\0';
    int count;
    char **tokens = strsplit(input, d, &count);
    qsort(tokens, count, sizeof(char *), compare);
    for (int i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
        free(tokens[i]);
    }

    free(tokens);
    return 0;
}
