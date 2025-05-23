#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct MyToken {
    enum {
        Variable,
        Integer,
        Operator,
        Float
    } type;
    char str[32];
} MyToken;
MyToken tokens[1025];
char *operators[7] = {"+", "-", "*", "/", "(", ")", "="};

typedef struct MyOp {
    char operator;
    int location;
    bool sign;
} MyOp;

typedef struct MyAssignment {
    union {
        int iVal;
        double fVal;
    } val;
    enum {
        INT_var,
        FLOAT_var
    } type;
    char name[32];
} MyAssignment;
MyAssignment assignments[1025]; 
int count_variables = 0;  

typedef struct MyValue {
    enum {
        INT,
        FLOAT,
        ERROR
    } type;
    union {
        int iVal;
        double fVal;
    } val;
} MyValue;

bool IsInteger(const char *s) {
    char *endptr;
    long num = strtol(s, &endptr, 10);
    if (*endptr != '\0') {
        return false;
    }
    return true;
}

bool IsIdentifier(const char *s) {
    if (isalpha(s[0]) || s[0] == '_') {
        size_t len = strspn(s + 1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
        return s[len + 1] == '\0';
    }
    return false;
}

bool IsOperator(const char *s) {
    if (strlen(s) != 1) return false;
    for (int i = 0; i < 7; i++) {
        if (strstr(s, operators[i])) return true;
    }
    return false;
}

bool IsFloat(const char *s) {
    char *endptr;
    strtod(s, &endptr);
    if (*endptr != '\0') {
        return false;
    }
    return true;
}

bool checkParentheses(int l, int r) {
    int count = 0;
    if (tokens[l].str[0] != '(' || tokens[r].str[0] != ')') return false;
    for (int i = 0; i <= r - l; i++) {
        if (tokens[l + i].str[0] == '(') count++;
        else if (tokens[l + i].str[0] == ')') count--;
        if (count == 0 && i != r - l) {
            return false;
        }
    }
    return count == 0;
}

typedef struct {
    char op;
    int precedence;
} OperatorMap;
OperatorMap opMap[] = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};
int opMapSize = sizeof(opMap) / sizeof(opMap[0]);

MyOp mainOperator(const int l, const int r) {
    int maxPrecedence = -1;
    MyOp op = {};
    int numofkuohao = 0;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '(') {
            numofkuohao++;
            continue;
        }
        if (tokens[i].str[0] == ')') {
            numofkuohao--;
            continue;
        }
        if (numofkuohao == 0) {
            for (int j = 0; j < opMapSize; j++) {
                if (tokens[i].str[0] == opMap[j].op) {
                    if (opMap[j].precedence > maxPrecedence) {
                        maxPrecedence = opMap[j].precedence;
                        op.operator = opMap[j].op;
                        op.location = i;
                        op.sign = true;
                    }
                }
            }
        }
    }
    return op;
}

bool checkMinus(int l, int r) {
    if (l == 0) return true; 
    if (tokens[l].str[0] == '-' && tokens[l - 1].type == Operator) return true;
    return false;
}

MyValue meetValue(MyValue v1, MyValue v2, const MyOp op) {
    if (v1.type == ERROR || v2.type == ERROR) {
        MyValue v = {.type = ERROR};
        return v;
    }
    if (v1.type != v2.type) {
        if (v1.type == INT) {
            v1.type = FLOAT;
            v1.val.fVal = (double)v1.val.iVal;
        }
        if (v2.type == INT) {
            v2.type = FLOAT;
            v2.val.fVal = (double)v2.val.iVal;
        }
    }
    switch (op.operator) {
        case '+': {
            if (v1.type == INT) {
                MyValue v = {.val.iVal = v1.val.iVal + v2.val.iVal, .type = INT};
                return v;
            } else if (v1.type == FLOAT) {
                MyValue v = {.val.fVal = v1.val.fVal + v2.val.fVal, .type = FLOAT};
                return v;
            }
            break;
        }
        case '-': {
            if (v1.type == INT) {
                MyValue v = {.val.iVal = v1.val.iVal - v2.val.iVal, .type = INT};
                return v;
            } else if (v1.type == FLOAT) {
                MyValue v = {.val.fVal = v1.val.fVal - v2.val.fVal, .type = FLOAT};
                return v;
            }
            break;
        }
        case '/': {
            if (v1.type == INT) {
                MyValue v = {.val.iVal = v1.val.iVal / v2.val.iVal, .type = INT};
                return v;
            } else if (v1.type == FLOAT) {
                MyValue v = {.val.fVal = v1.val.fVal / v2.val.fVal, .type = FLOAT};
                return v;
            }
            break;
        }
        case '*': {
            if (v1.type == INT) {
                MyValue v = {.val.iVal = v1.val.iVal * v2.val.iVal, .type = INT};
                return v;
            } else if (v1.type == FLOAT) {
                MyValue v = {.val.fVal = v1.val.fVal * v2.val.fVal, .type = FLOAT};
                return v;
            }
            break;
        }
        default: break;
    }
    MyValue errorValue = {.type = ERROR};
    return errorValue;
}

MyValue eval(int l, int r) {
    if (l > r) {
        MyValue v = {.type = ERROR};
        return v;
    } else if (l == r) {
        if (tokens[l].type == Variable) {
            for (int i = 0; i < count_variables; i++) {
                if (strcmp(tokens[l].str, assignments[i].name) == 0) {
                    if (assignments[i].type == FLOAT_var) {
                        MyValue v = {.val.fVal = assignments[i].val.fVal, .type = FLOAT};
                        return v;
                    }
                    if (assignments[i].type == INT_var) {
                        MyValue v = {.val.iVal = assignments[i].val.iVal, .type = INT};
                        return v;
                    }
                }
            }
            MyValue v = {.type = ERROR};
            return v;
        }
        if (tokens[l].type == Float) {
            MyValue v = {.val.fVal = atof(tokens[l].str), .type = FLOAT};
            return v;
        }
        if (tokens[l].type == Integer) {
            MyValue v = {.val.iVal = atoi(tokens[l].str), .type = INT};
            return v;
        }
        MyValue v = {.type = ERROR};
        return v;
    } else if (checkParentheses(l, r)) {
        return eval(l + 1, r - 1); 
    } else if (checkMinus(l, r)) {
        MyValue v = eval(l + 1, r);
        if (v.type == FLOAT) {
            v.val.fVal = -v.val.fVal;
        }
        if (v.type == INT) {
            v.val.iVal = -v.val.iVal;
        }
        return v;
    } else {
        MyOp op = mainOperator(l, r);
        MyValue val1 = eval(l, op.location - 1);
        MyValue val2 = eval(op.location + 1, r);
        return meetValue(val1, val2, op);
    }
}

void PrintValue(MyValue v) {
    switch (v.type) {
        case INT: {
            printf("%d\n", v.val.iVal);
            break;
        }
        case FLOAT: {
            printf("%.6f\n", v.val.fVal);
            break;
        }
        case ERROR: {
            printf("Error\n");
            break;
        }
    }
}

MyValue evalAssign(int l, int r) {
    int flag = 0;
    int position = 0;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '=') {
            flag = 1;
            position = i;
            if (l > 1) {
                if (tokens[i - 2].str[0] != '=') {
                    MyValue v = {.type = ERROR};
                    return v;
                }
            }
            break;
        }
    }
    if (flag) {
        MyValue type_and_num = evalAssign(position + 1, r);
        int flag1 = 0;
        for (int i = 0; i < count_variables; i++) {
            if (strcmp(tokens[position - 1].str, assignments[i].name) == 0) {
                switch (type_and_num.type) {
                    case INT: {
                        assignments[i].type = INT_var;
                        assignments[i].val.iVal = type_and_num.val.iVal;
                        break;
                    }
                    case FLOAT: {
                        assignments[i].type = FLOAT_var;
                        assignments[i].val.fVal = type_and_num.val.fVal;
                        break;
                    }
                    default: break;
                }
                return type_and_num;
            }
        }
        strcpy(assignments[count_variables].name, tokens[position - 1].str);
        switch (type_and_num.type) {
            case INT: {
                assignments[count_variables].type = INT_var;
                assignments[count_variables].val.iVal = type_and_num.val.iVal;
                break;
            }
            case FLOAT: {
                assignments[count_variables].type = FLOAT_var;
                assignments[count_variables].val.fVal = type_and_num.val.fVal;
                break;
            }
            default: break;
        }
        count_variables++;
        return type_and_num;
    } else {
        return eval(l, r);
    }
}

void processInput() {
    char line[1025];
    while (fgets(line, 1025, stdin) != NULL) {
        bool flag = true;
        int n = 0;
        int j = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                tokens[n].str[j] = '\0';
                if (IsIdentifier(tokens[n].str)) {
                    tokens[n].type = Variable;
                } else if (IsOperator(tokens[n].str)) {
                    tokens[n].type = Operator;
                } else if (IsInteger(tokens[n].str)) {
                    tokens[n].type = Integer;
                } else if (IsFloat(tokens[n].str)) {
                    tokens[n].type = Float;
                } else {
                    flag = false;
                    break;
                }
                n++;
                j = 0;
                continue;
            }
            tokens[n].str[j++] = line[i];
        }
        if (flag == false) {
            printf("Error\n");
            continue;
        }  
        int l = 0;
        int r = n - 1;
        int counter = 0;
        for (int i = l; i <= r; i++) {
            if (tokens[i].str[0] == '(') {
                counter++;
            } else if (tokens[i].str[0] == ')') {
                counter--;
            }
        }
        if (counter != 0) {
            printf("Error\n");
            continue;
        }
        PrintValue(evalAssign(l, r));
    }
}

int main() {
    processInput();
}
