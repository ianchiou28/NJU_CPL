#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char stack[100001];
int top = -1;

void push(char s) {
    top++;
    stack[top] = s;
}

char out(){
    if (top == -1) {
        return '\0';
    } else {
        char popped = stack[top];
        top--;
        return popped;
    }
}

bool same(char left, char right) {
    return (left == '(' && right == ')') || (left == '[' && right == ']') || (left == '{' && right == '}');
}

int main() {
    int n;
    scanf("%d\n", &n);

    while (n > 0) {
        n--;
        char s[100001];
        scanf("%s", s);
        top = -1;
        bool flag = true;
        int len = strlen(s);
        for (int i = 0; i < len; i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                push(s[i]);
            } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
                char last_open = out();
                if (last_open == '\0' || !same(last_open, s[i])) {
                    flag = false;
                    break;
                }
            }
        }

        if (flag && top == -1) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    
    return 0;
}
