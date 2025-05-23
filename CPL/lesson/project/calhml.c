#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_TOKENS 1027
#define MAX_VAR_COUNT 130
#define MAX_STR_LEN 34
#define ERROR_MSG "Error"

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_VARIABLE,
    TOKEN_ASSIGNMENT,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char str[MAX_STR_LEN];
} Token;

typedef enum {
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_ERROR
} ValueType;

typedef struct {
    ValueType type;
    union {
        int iVal;
        double fVal;
    } val;
} Value;

typedef struct {
    char name[MAX_STR_LEN];
    Value value;
} Variable;

Token tokens[MAX_TOKENS];
int token_count = 0;

Variable variables[MAX_VAR_COUNT];
int variable_count = 0;

void tokenize(const char *input);
Value eval(int l, int r);
int find_variable(const char *name);
void set_variable(const char *name, Value value);
Value eval_assignment(int l, int r);
Value eval_expression(int l, int r);
Value perform_operation(Value left, Value right, char op);

void tokenize(const char *input) {
    token_count = 0;
    int len = strlen(input);
    int i = 0;
    int need_space = 0;  // 标记是否需要空格

    while (i < len) {
        // 跳过空格
        while (i < len && isspace(input[i])) {
            i++;
        }
        if (i >= len) break;

        // 检查是否缺少必要的空格
        if (need_space && !isspace(input[i-1])) {
            token_count = 0;  // 清空tokens
            Value error = { .type = VALUE_ERROR };
            return;
        }

        Token token;
        if (isdigit(input[i]) || input[i] == '.' || 
            (input[i] == '-' && (i == 0 || 
             tokens[token_count-1].type == TOKEN_OPERATOR || 
             tokens[token_count-1].type == TOKEN_ASSIGNMENT || 
             tokens[token_count-1].str[0] == '('))) {
            int start = i;
            
            if (input[i] == '-') {
                // 计算连续的负号个数
                int negative_count = 0;
                while (i < len && input[i] == '-') {
                    negative_count++;
                    i++;
                }
                
                if (i < len && isdigit(input[i])) {
                    // 如果负号后面是数字，根据负号个数决定符号
                    while (i < len && (isdigit(input[i]) || input[i] == '.')) i++;
                    if (negative_count % 2 == 1) {  // 奇数个负号
                        token.str[0] = '-';
                        strncpy(token.str + 1, &input[start + negative_count], i - (start + negative_count));
                        token.str[i - start - negative_count + 1] = '\0';
                    } else {  // 偶数个负号
                        strncpy(token.str, &input[start + negative_count], i - (start + negative_count));
                        token.str[i - start - negative_count] = '\0';
                    }
                    token.type = TOKEN_NUMBER;
                } else {
                    // 如果负号后面不是数字，只处理第一个负号
                    token.str[0] = '-';
                    token.str[1] = '\0';
                    token.type = TOKEN_OPERATOR;
                    i = start + 1;
                }
            } else {
                while (i < len && (isdigit(input[i]) || input[i] == '.')) i++;
                strncpy(token.str, &input[start], i - start);
                token.str[i - start] = '\0';
                token.type = TOKEN_NUMBER;
            }
            need_space = 1;  // 数字后需要空格
        } else if (isalpha(input[i]) || input[i] == '_') {
            int start = i;
            while (i < len && (isalnum(input[i]) || input[i] == '_')) i++;
            strncpy(token.str, &input[start], i - start);
            token.str[i - start] = '\0';
            token.type = TOKEN_VARIABLE;
            need_space = 1;  // 变量后需要空格
        } else if (strchr("+-*/()=", input[i])) {
            token.str[0] = input[i];
            token.str[1] = '\0';
            token.type = (input[i] == '=') ? TOKEN_ASSIGNMENT : TOKEN_OPERATOR;
            i++;
            need_space = 1;  // 运算符后需要空格
        } else {
            token_count = 0;  // 遇到未知字符，清空tokens
            Value error = { .type = VALUE_ERROR };
            return;
        }

        tokens[token_count++] = token;
        if (token_count >= MAX_TOKENS) {
            token_count = 0;  // 超出最大token数，清空tokens
            Value error = { .type = VALUE_ERROR };
            return;
        }
    }
}

bool Is_variable(const char *s) {
    if(isalpha(s[0])||s[0]=='_') {
        int i=1;
        while(s[i]!='\0') {
            if(s[i]!='_' && !isalnum(s[i])) return false;
            i++;
        }
        return true;
    }
    return false;
}

int find_variable(const char *name) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void set_variable(const char *name, Value value) {
    if(Is_variable(name)){
        int index = find_variable(name);
        variables[index].value = value;
    }
    else{
        if (variable_count >= MAX_VAR_COUNT) {
            fprintf(stderr, "Error\n");
            exit(1);
        }
        strncpy(variables[variable_count].name, name, MAX_STR_LEN);
        variables[variable_count].value = value;
        variable_count++;
    }
}

Value perform_operation(Value left, Value right, char op) {
    Value result;
    if (left.type == VALUE_INT && right.type == VALUE_INT && op != '/') {
        result.type = VALUE_INT;
        switch (op) {
            case '+': result.val.iVal = left.val.iVal + right.val.iVal; break;
            case '-': result.val.iVal = left.val.iVal - right.val.iVal; break;
            case '*': result.val.iVal = left.val.iVal * right.val.iVal; break;
            default: result.type = VALUE_ERROR;
        }
        return result;
    }

    result.type = VALUE_FLOAT;
    double left_val = (left.type == VALUE_INT) ? (double)left.val.iVal : left.val.fVal;
    double right_val = (right.type == VALUE_INT) ? (double)right.val.iVal : right.val.fVal;
    
switch (op) {
    case '+': 
        result.val.fVal = left_val + right_val; 
        result.type = VALUE_FLOAT;
        break;
        
    case '-': 
        result.val.fVal = left_val - right_val; 
        result.type = VALUE_FLOAT;
        break;
        
    case '*': 
        result.val.fVal = left_val * right_val; 
        result.type = VALUE_FLOAT;
        break;
        
    case '/': 
        if (right_val == 0) {
            result.type = VALUE_ERROR;  // 除零错误
        } else {
            if (left.type == VALUE_INT && right.type == VALUE_INT) {
                // 整数除法，返回整数结果
                result.val.iVal = left.val.iVal / right.val.iVal;
                result.type = VALUE_INT;
            } else {
                // 浮点除法，保留六位小数
                result.val.fVal = (double) left_val / right_val;
                result.type = VALUE_FLOAT;
            }
        }
        break;
        
    default: 
        result.type = VALUE_ERROR;
}
return result;

}

Value eval(int l, int r) {
    if (l > r) {
        Value error = { .type = VALUE_ERROR };
        return error;
    }

    // 单个数字或变量的情况
    if (l == r) {
        Token token = tokens[l];
        if (token.type == TOKEN_NUMBER) {
            Value result;
            if (strchr(token.str, '.')) {
                result.type = VALUE_FLOAT;
                result.val.fVal = atof(token.str);
            } else {
                result.type = VALUE_INT;
                result.val.iVal = atoi(token.str);
            }
            return result;
        } else if (token.type == TOKEN_VARIABLE) {
            int index = find_variable(token.str);
            if (index == -1) {
                // 未定义变量，返回错误
                Value error = { .type = VALUE_ERROR };
                return error;
            }
            return variables[index].value;
        }
    }

    // 处理括号表达式
    if (tokens[l].type == TOKEN_OPERATOR && tokens[l].str[0] == '(' &&
        tokens[r].type == TOKEN_OPERATOR && tokens[r].str[0] == ')') {
        return eval(l + 1, r - 1);
    }

    // 寻找主运算符
    int parens = 0;
    int main_op = -1;
    int min_priority = 99;

    for (int i = l; i <= r; i++) {
        if (tokens[i].type == TOKEN_OPERATOR) {
            char op = tokens[i].str[0];
            if (op == '(') {
                parens++;
            } else if (op == ')') {
                parens--;
            } else if (parens == 0) {
                int current_priority;
                if (op == '=') current_priority = 3;
                else if (op == '+' || op == '-') current_priority = 2;
                else if (op == '*' || op == '/') current_priority = 1;
                else continue;

                if (main_op == -1 || current_priority >= min_priority) {
                    min_priority = current_priority;
                    main_op = i;
                }
            }
        }
    }

    if (main_op != -1) {
        Value left = eval(l, main_op - 1);
        if (left.type == VALUE_ERROR) return left;

        Value right = eval(main_op + 1, r);
        if (right.type == VALUE_ERROR) return right;

        return perform_operation(left, right, tokens[main_op].str[0]);
    }

    Value error = { .type = VALUE_ERROR };
    return error;
}


Value eval_assignment(int l, int r) {
    int position = -1;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '=' && tokens[i].type == TOKEN_ASSIGNMENT) {
            position = i;
            break;
        }
    }
    if (position != -1) {
        if (position == l || tokens[position - 1].type != TOKEN_VARIABLE) {
            Value error = { .type = VALUE_ERROR };
            return error;
        }

        Value right_value = eval(position + 1, r);
        if (right_value.type == VALUE_ERROR) {
            return right_value;
        }

        set_variable(tokens[position - 1].str, right_value);
        return right_value;
    }

    return eval(l, r);
}



int main() {
    char input[1030];
    while (fgets(input, sizeof(input), stdin)) {
        tokenize(input);
        Value result = eval_assignment(0, token_count - 1);
        if (result.type == VALUE_ERROR) {
            printf("%s\n", ERROR_MSG);
        } else {
            // 如果是整数，直接输出整数值
            if (result.type == VALUE_INT) {
                printf("%d\n", result.val.iVal);
            } else {
                double value = result.val.fVal;
                printf("%.6f\n", value);
            }
        }
    }
    return 0;
}




