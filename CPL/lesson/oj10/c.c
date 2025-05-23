#include <stdio.h>
#include <string.h>
#include <ctype.h>
char text[2000001], lower_stack[2000001], upper_stack[2000001];
int text_len = 0, lower_top = 0, upper_top = 0;
void append_text(const char *input_text) {
    for (int i = 0; input_text[i] != '\0'; i++) {
        char ch = input_text[i];
        if (ch == 'm') {
            if (lower_top > 0) {
                char last_lower = lower_stack[lower_top - 1];
                for (int j = text_len - 1; j >= 0; j--) {
                    if (text[j] == last_lower && islower(text[j])) {
                        for (int k = j; k < text_len - 1; k++) text[k] = text[k + 1];
                        text_len--;
                        break;
                    }
                } lower_top--;
            }
        } else if (ch == 'M') {
            if (upper_top > 0) {
                char last_upper = upper_stack[upper_top - 1];
                for (int j = text_len - 1; j >= 0; j--) {
                    if (text[j] == last_upper && isupper(text[j])) {
                        for (int k = j; k < text_len - 1; k++) text[k] = text[k + 1];
                        text_len--;
                        break;
                    }
                }
                upper_top--;
            }
        } else {
            text[text_len++] = ch;
            if (islower(ch)) lower_stack[lower_top++] = ch;
            else if (isupper(ch)) upper_stack[upper_top++] = ch;
        }
    }
}
void query(int k) {
    for (int i = text_len - k; i < text_len; i++) putchar(text[i]);
    putchar('\n');
}
int main() {
    int q;
    scanf("%d", &q);
    char command[2000001];
    while (q--) {
        scanf("%s", command);
        if (command[0] == '?') {
            int k;
            scanf("%d", &k);
            query(k);
        } 
        else append_text(command);
    }
    return 0;
}