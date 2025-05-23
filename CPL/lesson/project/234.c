#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_TOKENS 1024
#define MAX_VAR_COUNT 128
#define MAX_STR_LEN 32
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
            token_count = 0;
            return;
        }

        Token token;
        if (isdigit(input[i]) || input[i] == '.' || 
            (input[i] == '-' && (i == 0 || 
             tokens[token_count-1].type == TOKEN_OPERATOR || 
             tokens[token_count-1].type == TOKEN_ASSIGNMENT || 
             tokens[token_count-1].str[0] == '('))) {
            int start = i;
            int dot_count = 0;  // 记录小数点数量
            int leading_zero = 0;  // 记录前导零
            
            if (input[i] == '-') {
                // 判断是否是数字的负号
                if (i == 0 || tokens[token_count-1].type == TOKEN_OPERATOR || 
                    tokens[token_count-1].type == TOKEN_ASSIGNMENT) {
                    // 看看后面是否直接跟数字
                    if (i + 1 < len && isdigit(input[i + 1])) {
                        // 作为数字的一部分处理
                        start = i;
                        i++;
                        while (i < len && (isdigit(input[i]) || input[i] == '.')) i++;
                        strncpy(token.str, &input[start], i - start);
                        token.str[i - start] = '\0';
                        token.type = TOKEN_NUMBER;
                    } else {
                        // 作为一元负号处理
                        token.str[0] = '-';
                        token.str[1] = '\0';
                        token.type = TOKEN_OPERATOR;
                        i++;
                    }
                } else {
                    // 作为减法运算符处理
                    token.str[0] = '-';
                    token.str[1] = '\0';
                    token.type = TOKEN_OPERATOR;
                    i++;
                }
            } else {
                // 检查前导零
                if (input[i] == '0' && i + 1 < len && isdigit(input[i + 1])) {
                    token_count = 0;  // 错误：小数点前没有数字
                    return;
                }
                
                // 检查数字格式
                int first_digit = 1;  // 标记是否是第一个数字
                while (i < len && (isdigit(input[i]) || input[i] == '.')) {
                    if (input[i] == '.') {
                        // 小数点前必须有数字
                        if (first_digit) {
                            token_count = 0;  // 错误：小数点前没有数字
                            return;
                        }
                        dot_count++;
                        if (dot_count > 1) {  // 多于一个小数点
                            token_count = 0;
                            return;
                        }
                    }
                    if (first_digit && input[i] == '0' && i + 1 < len && isdigit(input[i + 1])) {
                        token_count = 0;  // 前导零错误
                        return;
                    }
                    if (isdigit(input[i])) {
                        first_digit = 0;
                    }
                    i++;
                }
                
                // 检查小数点后是否有数字
                if (dot_count == 1) {
                    char *dot_pos = strchr(&input[start], '.');
                    if (dot_pos != NULL && !isdigit(*(dot_pos + 1))) {
                        token_count = 0;  // 小数点后没有数字
                        return;
                    }
                }
                
                strncpy(token.str, &input[start], i - start);
                token.str[i - start] = '\0';
                token.type = TOKEN_NUMBER;
            }
            need_space = 1;
        } else if (isalpha(input[i]) || input[i] == '_') {
            int start = i;
            while (i < len && (isalnum(input[i]) || input[i] == '_')) i++;
            strncpy(token.str, &input[start], i - start);
            token.str[i - start] = '\0';
            token.type = TOKEN_VARIABLE;
            need_space = 1;  // 变量后需要空格
        } else if (strchr("+-*/()=", input[i])) {
            // 检查连续运算符
            if (token_count > 0 && 
                tokens[token_count-1].type == TOKEN_OPERATOR && 
                tokens[token_count-1].str[0] != ')' && 
                input[i] != '(' && 
                !(input[i] == '-' && (token_count == 0 || 
                  tokens[token_count-1].type == TOKEN_OPERATOR || 
                  tokens[token_count-1].type == TOKEN_ASSIGNMENT))) {  // 修改这里的条件
                token_count = 0;
                return;
            }
            
            token.str[0] = input[i];
            token.str[1] = '\0';
            token.type = (input[i] == '=') ? TOKEN_ASSIGNMENT : TOKEN_OPERATOR;
            i++;
            need_space = 1;
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

    // 在函数末尾添加表达式完整性检查
    if (token_count > 0) {
        Token last_token = tokens[token_count - 1];
        // 检查最后一个token是否是运算符（除了右括号）
        if (last_token.type == TOKEN_OPERATOR && last_token.str[0] != ')') {
            token_count = 0;  // 表达式不完整
            return;
        }
        // 检查最后一个token是否是赋值符号
        if (last_token.type == TOKEN_ASSIGNMENT) {
            token_count = 0;  // 表达式不完整
            return;
        }
    }
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
    int index = find_variable(name);
    if (index == -1) {
        if (variable_count >= MAX_VAR_COUNT) {
            fprintf(stderr, "Error\n");
            exit(1);
        }
        strncpy(variables[variable_count].name, name, MAX_STR_LEN);
        variables[variable_count].value = value;
        variable_count++;
    } else {
        variables[index].value = value;  // 更新已有变量的值
    }
}


Value perform_operation(Value left, Value right, char op) {
    Value result;
    
    // 特殊处理一元负号的情况
    if (op == '-' && left.type == VALUE_INT && left.val.iVal == 0) {
        result.type = right.type;
        if (right.type == VALUE_INT) {
            result.val.iVal = -right.val.iVal;
        } else {
            result.val.fVal = -right.val.fVal;
        }
        return result;
    }
    
    // 如果两个操作数都是整数，结果必须是整数
    if (left.type == VALUE_INT && right.type == VALUE_INT) {
        result.type = VALUE_INT;
        switch (op) {
            case '+': 
                result.val.iVal = left.val.iVal + right.val.iVal; 
                break;
            case '-': 
                result.val.iVal = left.val.iVal - right.val.iVal; 
                break;
            case '*': 
                result.val.iVal = left.val.iVal * right.val.iVal; 
                break;
            case '/': 
                if (right.val.iVal == 0) {
                    result.type = VALUE_ERROR;
                } else {
                    // 整数除法
                    result.type = VALUE_INT;
                    result.val.iVal = left.val.iVal / right.val.iVal;
                }
                break;
            default: 
                result.type = VALUE_ERROR;
        }
        return result;
    }

    // 如果有一个操作数是浮点数，结果才是浮点数
    result.type = VALUE_FLOAT;
    double left_val = (left.type == VALUE_INT) ? left.val.iVal : left.val.fVal;
    double right_val = (right.type == VALUE_INT) ? right.val.iVal : right.val.fVal;
    
    switch (op) {
        case '+': 
            result.val.fVal = left_val + right_val; 
            break;
        case '-': 
            result.val.fVal = left_val - right_val; 
            break;
        case '*': 
            result.val.fVal = left_val * right_val; 
            break;
        case '/': 
            if (right_val == 0) {
                result.type = VALUE_ERROR;
            } else {
                result.val.fVal = left_val / right_val;
            }
            break;
        default: 
            result.type = VALUE_ERROR;
    }

    // 如果结果恰好是整数，转换为整数类型
    if (result.type == VALUE_FLOAT && result.val.fVal == (int)result.val.fVal) {
        result.type = VALUE_INT;
        result.val.iVal = (int)result.val.fVal;
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
                Value error = { .type = VALUE_ERROR };
                return error;
            }
            return variables[index].value;
        }
    }

    // 寻找主运算符（在非括号内的最低优先级运算符）
    int parens = 0;
    int main_op = -1;
    int mul_div_op = -1;  // 记录乘除运算符位置

    // 先处理括号表达式
    if (tokens[l].type == TOKEN_OPERATOR && tokens[l].str[0] == '(' &&
        tokens[r].type == TOKEN_OPERATOR && tokens[r].str[0] == ')') {
        // 验证这对括号是否匹配
        int temp_parens = 1;
        for (int i = l + 1; i < r; i++) {
            if (tokens[i].type == TOKEN_OPERATOR) {
                if (tokens[i].str[0] == '(') temp_parens++;
                else if (tokens[i].str[0] == ')') {
                    temp_parens--;
                    if (temp_parens == 0 && i != r) break;
                }
            }
        }
        if (temp_parens == 1) {
            return eval(l + 1, r - 1);
        }
    }

    // 从右向左扫描，找运算符
    for (int i = r; i >= l; i--) {
        if (tokens[i].type == TOKEN_OPERATOR) {
            char op = tokens[i].str[0];
            if (op == ')') {
                parens++;
            } else if (op == '(') {
                parens--;
            } else if (parens == 0) {  // 只处理非括号内的运算符
                // 处理加减运算符
                if (op == '+' || op == '-') {
                    // 检查是否是二元运算符
                    if (i > l && i < r &&  // 不是在开头或结尾
                        !(tokens[i-1].type == TOKEN_OPERATOR && tokens[i-1].str[0] != ')') &&  // 前面不是运算符（除了右括号）
                        !(tokens[i+1].type == TOKEN_OPERATOR && tokens[i+1].str[0] != '(' && tokens[i+1].str[0] != '-')) {  // 后面不是运算符（除了左括号和负号）
                        main_op = i;
                        break;
                    }
                }
                // 记录乘除运算符
                else if ((op == '*' || op == '/') && mul_div_op == -1) {
                    mul_div_op = i;
                }
            }
        }
    }

    // 如果找到了加减运算符，处理它
    if (main_op != -1) {
        Value left = eval(l, main_op - 1);
        if (left.type == VALUE_ERROR) return left;
        
        Value right = eval(main_op + 1, r);
        if (right.type == VALUE_ERROR) return right;
        
        return perform_operation(left, right, tokens[main_op].str[0]);
    }

    // 如果找到了乘除运算符，处理它
    if (mul_div_op != -1) {
        Value left = eval(l, mul_div_op - 1);
        if (left.type == VALUE_ERROR) return left;
        
        Value right = eval(mul_div_op + 1, r);
        if (right.type == VALUE_ERROR) return right;
        
        return perform_operation(left, right, tokens[mul_div_op].str[0]);
    }

    // 处理一元负号
    if (tokens[l].type == TOKEN_OPERATOR && tokens[l].str[0] == '-') {
        Value right = eval(l + 1, r);
        if (right.type == VALUE_ERROR) return right;
        
        Value zero;
        zero.type = VALUE_INT;
        zero.val.iVal = 0;
        return perform_operation(zero, right, '-');
    }

    Value error;
    error.type = VALUE_ERROR;
    return error;
}

Value eval_assignment(int l, int r) {
    // 查找赋值符号的位置
    int assignment_pos = -1;
    for (int i = l; i <= r; i++) {
        if (tokens[i].str[0] == '=') {
            assignment_pos = i;
            break;
        }
    }

    if (assignment_pos == -1) {
        // 如果没有找到赋值符号，直接计算表达式
        return eval(l, r);
    }

    // 处理赋值操作符两边的表达式
    // 左侧是变量名，右侧是表达式
    Token var_token = tokens[assignment_pos - 1];
    if (var_token.type != TOKEN_VARIABLE) {
        // 左侧不是变量名，返回错误
        Value error = { .type = VALUE_ERROR };
        return error;
    }

    // 计算右侧的表达式
    Value right_value = eval(assignment_pos + 1, r);
    if (right_value.type == VALUE_ERROR) {
        // 右侧表达式计算失败，返回错误
        return right_value;
    }

    // 赋值给变量
    set_variable(var_token.str, right_value);
    
    // 返回赋值后的结果
    return right_value;
}



int main() {
    char input[1024];
    while (fgets(input, sizeof(input), stdin)) {
        tokenize(input);
        Value result = eval_assignment(0, token_count - 1);
        if (result.type == VALUE_ERROR) {
            printf("%s\n", ERROR_MSG);
        } else if (result.type == VALUE_INT) {
            printf("%d\n", result.val.iVal);
        } else {
            printf("%.6f\n", result.val.fVal);
        }
    }
    return 0;
}



