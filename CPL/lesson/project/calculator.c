#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct token {
    enum { Variable, Integer, Operator, Float } type;
    char str[32];
} Token;

Token tokens[1025];
char *operators[7] = {"+", "-", "*", "/", "(", ")", "="};

typedef struct Op {
    char operator;
    int location;
    bool sign;
} Op;

typedef struct assignment {
    union { int iVal; double fVal; } val;
    enum { INT_var, FLOAT_var } type;
    char name[32];
} Assignment;

Assignment assignments[1025];
int count_variables = 0;

typedef struct value {
    enum { INT, FLOAT, ERROR } type;
    union { int iVal; double fVal; } val;
} Value;

bool Is_int(const char *s) {
    if (s[0] == '0' && strlen(s) > 1) return false;
    for (int i = 0; s[i]; i++) if (!isdigit(s[i])) return false;
    return true;
}

bool Is_variable(const char *s) {
    if (isalpha(s[0]) || s[0] == '_') {
        for (int i = 1; s[i]; i++) if (s[i] != '_' && !isalnum(s[i])) return false;
        return true;
    }
    return false;
}

bool Is_operator(const char *s) {
    if (strlen(s) != 1) return false;
    for (int i = 0; i < 7; i++) if (strstr(s, operators[i])) return true;
    return false;
}

bool Is_float(const char *s) {
    if (s[0] == '.' || (s[0] == '0' && s[1] != '.') || s[strlen(s)-1] == '.') return false;
    int count = 0;
    for (int i = 0; s[i]; i++) if (s[i] == '.') count++;
    if (count > 1) return false;
    for (int i = 0; s[i]; i++) if (!isdigit(s[i]) && s[i] != '.') return false;
    return true;
}

bool check_parentheses(int l, int r) {
    int count = 0;
    if (tokens[l].str[0] != '(' || tokens[r].str[0] != ')') return false;
    for (int i = 0; i <= r - l; i++) {
        if (tokens[l + i].str[0] == '(') count++;
        else if (tokens[l + i].str[0] == ')') count--;
        if (count == 0 && i != r - l) return false;
    }
    return count == 0;
}

Op main_operator(int l, int r) {
    Op op = {};
    bool flag1 = false;
    int numofkuohao = 0;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '(') numofkuohao++;
        else if (tokens[i].str[0] == ')') numofkuohao--;
        else if (numofkuohao == 0) {
            if (tokens[i].str[0] == '+' || tokens[i].str[0] == '-' || tokens[i].str[0] == '*' || tokens[i].str[0] == '/') {
                if (tokens[i].str[0] == '-' && (tokens[i-1].type != Operator || tokens[i-1].str[0] == ')') && i != l)
                    op.operator = '-';
                else op.operator = tokens[i].str[0];
                op.location = i;
                flag1 = true;
            }
        }
    }
    op.sign = flag1;
    return op;
}

Value eval(int l, int r) {
    if (l > r) return (Value){.type = ERROR};
    if (l == r) {
        if (tokens[l].type == Variable) {
            for (int i = 0; i < count_variables; i++) {
                if (strcmp(tokens[l].str, assignments[i].name) == 0)
                    return assignments[i].type == FLOAT_var
                        ? (Value){.val.fVal = assignments[i].val.fVal, .type = FLOAT}
                        : (Value){.val.iVal = assignments[i].val.iVal, .type = INT};
            }
            return (Value){.type = ERROR};
        }
        if (tokens[l].type == Float) return (Value){.val.fVal = atof(tokens[l].str), .type = FLOAT};
        if (tokens[l].type == Integer) return (Value){.val.iVal = atoi(tokens[l].str), .type = INT};
        return (Value){.type = ERROR};
    }
    if (check_parentheses(l, r)) return eval(l + 1, r - 1);
    if (tokens[l].str[0] == '-' && main_operator(l + 1, r).sign == false) {
        Value v = eval(l + 1, r);
        return v.type == INT ? (Value){.val.iVal = -v.val.iVal, .type = INT} : (Value){.val.fVal = -v.val.fVal, .type = FLOAT};
    }
    Op op = main_operator(l, r);
    Value val1 = eval(l, op.location - 1);
    Value val2 = eval(op.location + 1, r);
    return (Value){.type = val1.type == INT
        ? (op.operator == '+' ? (val1.val.iVal + val2.val.iVal) : (op.operator == '-' ? (val1.val.iVal - val2.val.iVal)
            : (op.operator == '*' ? (val1.val.iVal * val2.val.iVal) : (val1.val.iVal / val2.val.iVal))))), .val.iVal = 0} : 
        (op.operator == '+' ? (val1.val.fVal + val2.val.fVal) : (op.operator == '-' ? (val1.val.fVal - val2.val.fVal)
            : (op.operator == '*' ? (val1.val.fVal * val2.val.fVal) : (val1.val.fVal / val2.val.fVal))))};
}

void PrintValue(Value v) {
    switch (v.type) {
        case INT: printf("%d\n", v.val.iVal); break;
        case FLOAT: printf("%.6f\n", v.val.fVal); break;
        case ERROR: printf("Error\n"); break;
    }
}

int main() {
    char line[1025];
    while (fgets(line, sizeof(line), stdin)) {
        int n = 0, j = 0;
        bool flag = true;
        for (int i = 0; line[i]; i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                tokens[n].str[j] = '\0';
                if (Is_variable(tokens[n].str)) tokens[n].type = Variable;
                else if (Is_operator(tokens[n].str)) tokens[n].type = Operator;
                else if (Is_int(tokens[n].str)) tokens[n].type = Integer;
                else if (Is_float(tokens[n].str)) tokens[n].type = Float;
                else { flag = false; break; }
                n++; j = 0; continue;
            }
            tokens[n].str[j++] = line[i];
        }
        if (!flag) { printf("Error\n"); continue; }
        int l = 0, r = n - 1, counter = 0;
        for (int i = l; i <= r; i++) if (tokens[i].str[0] == '(') counter++;
        else if (tokens[i].str[0] == ')') counter--;
        if (counter != 0) { printf("Error\n"); continue; }
        PrintValue(eval(l, r));
    }
}
