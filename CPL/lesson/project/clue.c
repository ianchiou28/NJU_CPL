#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {
    NUM,
    OPERATOR,
    LEFT,
    RIGHT,
    VARIABLE
} TokenType;

typedef struct {
    TokenType type;
    char str[35];
} Token;

typedef struct {
    char name[35];
    int value;
} Assignment;

Token tokens[105];
int count = 0;

Assignment variables[105];
int var_count = 0;

int find_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("Error\n");
    exit(1);
}

void add_variable(const char *name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    if (var_count >= 105) {
        printf("Error\n");
        exit(1);
    }
    strcpy(variables[var_count].name, name);
    variables[var_count].value = value;
    var_count++;
}

bool is_valid_variable_name(const char *name) {
    if (!isalpha(name[0])) return false;
    for (int i = 1; name[i] != '\0'; i++) {
        if (!isalnum(name[i])) return false;
    }
    return true;
}

void tokenize(const char *expr) {
    int i = 0, len = strlen(expr);
    count = 0;

    while (i < len) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isdigit(expr[i]) || 
            (expr[i] == '-' && (i == 0 || tokens[count - 1].type == OPERATOR || tokens[count - 1].type == LEFT))) {
            int start = i;
            if (expr[i] == '-') i++;
            while (i < len && isdigit(expr[i])) i++;
            strncpy(tokens[count].str, expr + start, i - start);
            tokens[count].str[i - start] = '\0';
            tokens[count].type = NUM;
            count++;
            continue;
        }
        if (strchr("+-*/", expr[i])) {
            tokens[count].str[0] = expr[i];
            tokens[count].str[1] = '\0';
            tokens[count].type = OPERATOR;
            count++;
            i++;
            continue;
        }
        if (expr[i] == '(') {
            tokens[count].str[0] = '(';
            tokens[count].str[1] = '\0';
            tokens[count].type = LEFT;
            count++;
            i++;
            continue;
        }
        if (expr[i] == ')') {
            tokens[count].str[0] = ')';
            tokens[count].str[1] = '\0';
            tokens[count].type = RIGHT;
            count++;
            i++;
            continue;
        }
        if (isalpha(expr[i])) {
            int start = i;
            while (i < len && isalnum(expr[i])) i++;
            strncpy(tokens[count].str, expr + start, i - start);
            tokens[count].str[i - start] = '\0';
            tokens[count].type = VARIABLE;
            count++;
            continue;
        }
        printf("Error\n");
        exit(1);
    }
}

int find_main_operator(int l, int r) {
    int level = 0;
    int main_op = -1;
    for (int i = l; i <= r; i++) {
        if (tokens[i].type == LEFT) {
            level++;
        } else if (tokens[i].type == RIGHT) {
            level--;
        } else if (tokens[i].type == OPERATOR && level == 0) {
            if (main_op == -1 || 
                (tokens[i].str[0] == '+' || tokens[i].str[0] == '-') ||
                (tokens[main_op].str[0] == '*' || tokens[main_op].str[0] == '/')) {
                main_op = i;
            }
        }
    }
    return main_op;
}

bool check_parentheses(int l, int r) {
    int count = 0;
    if (tokens[l].str[0] != '(' || tokens[r].str[0] != ')') return false;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '(') count++;
        else if (tokens[i].str[0] == ')') count--;
        if (count == 0 && i != r) return false;
    }
    return count == 0;
}

int get_priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int eval(int l, int r) {
    if (l > r) {
        printf("Error\n");
        exit(1);
    }

    if (l == r) {
        if (tokens[l].type == NUM) {
            return atoi(tokens[l].str);
        } else if (tokens[l].type == VARIABLE) {
            return find_variable(tokens[l].str);
        }
        printf("Error\n");
        exit(1);
    }

    if (check_parentheses(l, r)) {
        return eval(l + 1, r - 1);
    }

    if (tokens[l].type == OPERATOR && tokens[l].str[0] == '-') {
        return -eval(l + 1, r);
    }

    int op = find_main_operator(l, r);
    if (op == -1) {
        printf("Error\n");
        exit(1);
    }

    int val1 = eval(l, op - 1);
    int val2 = eval(op + 1, r);

    switch (tokens[op].str[0]) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/': 
            if (val2 == 0) {
                printf("Error\n");
                exit(1);
            }
            return val1 / val2;
        default:
            printf("Error\n");
            exit(1);
    }
}

void process(const char *expr) {
    char var_name[35];
    int value;

    // If there is an assignment (e.g., "x = 3 + 5")
    if (sscanf(expr, "%s = %s", var_name, tokens[0].str) == 2) {
        tokenize(tokens[0].str); // Tokenize the expression on the right-hand side
        int result = eval(0, count - 1);
        add_variable(var_name, result);
        printf("%d\n", result);
    } else {
        // If it is a direct assignment (e.g., "x = 5")
        if (sscanf(expr, "%s = %d", var_name, &value) != 2 || !is_valid_variable_name(var_name)) {
            printf("Error\n");
            exit(1);
        }
        add_variable(var_name, value);
        printf("%d\n", value);
    }
}

int main() {
    char expr[256];
    char var_name[35];
    int value;

    while (fgets(expr, sizeof(expr), stdin)) {
        expr[strcspn(expr, "\n")] = '\0';
        if (strlen(expr) == 0) break;

        if (strchr(expr, '=')) {
            process(expr); // Process assignment or expression evaluation
        } else {
            tokenize(expr);
            if (count == 0) {
                printf("Error\n");
                continue;
            }
            int result = eval(0, count - 1);
            printf("%d\n", result);
        }
    }

    return 0;
}
