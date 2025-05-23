#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
typedef struct token {
    enum {
        Variable ,
        Integer ,
        Operator ,
        Float
    } type;
    char str[32];
} Token;
Token tokens[1025];
char *operators[7]={"+","-","*","/","(",")","="};
typedef struct Op {
    char operator;
    int location;
    bool sign;
} Op;
typedef struct assignment {
    union {
        int iVal;
        double fVal;
    } val;
    enum {
        INT_var,
        FLOAT_var
    } type;
    char name[32];
} Assignment;
Assignment assignments[1025];//赋值过的变量
int count_variables=0;//记录变量的个数
typedef struct value {
    enum {
        INT,
        FLOAT,
        ERROR
    } type;
    union {
        int iVal;
        double fVal;
    } val;
} Value;
bool Is_int(const char *s) {
    const int len = strlen(s);
    if (s[0] == '0'&&len>1) return false;
    int i=0;
    while(s[i]!='\0') {
        if(!isdigit(s[i++])) return false;
    }
    return true;
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
bool Is_operator(const char *s) {
    if(strlen(s)!=1 ) return false;
    for(int i=0;i<7;i++) {
        if(strstr(s,operators[i])) return true;
    }
    return false;
}
bool Is_float(const char *s) {
    if(s[0]=='.') return false;
    if(s[0]=='0'&&s[1]!='.') return false;
    const int len=strlen(s);
    if(s[len-1]=='.') return false;
    int count=0;
    for(int i=0;i<len;i++) {
        if(s[i]=='.') count++;
        if((!isdigit(s[i])&&s[i]!='.')||count>=2) return false;
    }
    return true;
}
bool check_parentheses(int l,int r) {
    int count=0;
    if(tokens[l].str[0]!='('||tokens[r].str[0]!=')') return false;
    for(int i=0;i<=r-l;i++) {
        if(tokens[l+i].str[0]=='(') count++;
        else if(tokens[l+i].str[0]==')') count--;
        if(count==0&&i!=r-l) {
            return false;
        }
    }
    if(count==0) return true;
    else return false;
}//括号判断
Op main_operator(const int l, const int r) {
    int flag=0;
    bool flag1=false;
    Op op = {};
    int numofkuohao=0;
    for(int i=l;i<=r;i++) {
        if(tokens[i].str[0]=='(') {
            numofkuohao++;
            continue;
        }
        if(tokens[i].str[0]==')') {
            numofkuohao--;
            continue;
        }
        if(numofkuohao==0) {
            if(tokens[i].str[0]=='+') {
                flag=1;
                op.operator=('+');
                op.location=i;
                flag1=true;
                continue;
            }
            if(tokens[i].str[0]=='-' &&
                (tokens[i-1].type!=Operator ||tokens[i-1].str[0]==')') &&
                i!=l)
                {
                flag=1;
                op.operator=('-');
                op.location=i;
                flag1=true;
                continue;
            }
            if(tokens[i].str[0]=='*'&&flag==0) {
                op.operator=('*');
                op.location=i;
                flag1=true;
                continue;
            }
            if(tokens[i].str[0]=='/'&&flag==0) {
                op.operator=('/');
                op.location=i;
                flag1=true;
                continue;
            }
        }
    }
    op.sign=flag1;
    return op;
}
bool check_minus(int l,int r) {
    if(main_operator(l+1,r).sign==false && tokens[l].str[0]=='-'  ) return true;
    return false;
}//负号判断
Value meetValue(Value v1, Value v2,const Op op) {
    if(v1.type== ERROR || v2.type== ERROR) {
        Value v = {.type = ERROR};
        return v;
    }
    if(v1.type!=v2.type) {
        if(v1.type==INT) {
            v1.type=FLOAT;
            double f=v1.val.iVal;
            v1.val.fVal=f;
        }
        if(v2.type==INT) {
            v2.type=FLOAT;
            double f=v2.val.iVal;
            v2.val.fVal=f;
        }
    }
    switch(op.operator) {
        case '+': {
            if(v1.type==INT) {
                Value v={
                    .val.iVal=v1.val.iVal+v2.val.iVal,
                    .type=INT
                };
                return v;
            }
            else if(v1.type==FLOAT) {
                Value v={
                .val.fVal=v1.val.fVal+v2.val.fVal,
                .type=FLOAT
                };
                return v;
            }
            break;
        }
        case '-': {
            if(v1.type==INT) {
                Value v= {
                    .val.iVal=v1.val.iVal-v2.val.iVal,
                    .type=INT
                };
                return v;
            }
            else if(v1.type==FLOAT) {
                Value v= {
                    .val.fVal=v1.val.fVal-v2.val.fVal,
                    .type=FLOAT
                    };
                return v;
            }
            break;
        }
        case '/': {
            if(v1.type==INT) {
                Value v= {
                    .val.iVal=v1.val.iVal/v2.val.iVal,
                    .type=INT
                };
                return v;
            }
            else if(v1.type==FLOAT) {
                Value v ={
                    .val.fVal=v1.val.fVal/v2.val.fVal,
                    .type=FLOAT
                    };
                return v;
            }
            break;
        }
        case '*': {
            if(v1.type==INT) {
                Value v = {
                    .val.iVal=v1.val.iVal*v2.val.iVal,
                    .type=INT
                };
                return v;
            }
            else if(v1.type==FLOAT) {
                Value v = {
                    .val.fVal=v1.val.fVal*v2.val.fVal,
                    .type=FLOAT
                    };
                return v;
            }
            break;
        }
        default: break;
    }
}
Value eval(int l,int r) {
    if ( l > r ) {
        Value v = { .type=ERROR };
        return v;
    }
    else if ( l == r ) {
            if(tokens[l].type == Variable) {
                for(int i=0;i<count_variables;i++) {
                    if(strcmp(tokens[l].str,assignments[i].name)==0) {
                        if(assignments[i].type == FLOAT_var) {
                            Value v = {
                                .val.fVal=assignments[i].val.fVal,
                                .type=FLOAT
                            };
                            return v;
                        }
                        if(assignments[i].type == INT_var) {
                            Value v = {
                            .val.iVal=assignments[i].val.iVal,
                            .type=INT
                            };
                            return v;
                        }
                    }
                }

                Value v = { .type=ERROR };
                return v;
            }
            if(tokens[l].type == Float) {
                Value v={
                    .val.fVal=atof(tokens[l].str),
                    .type=FLOAT};
                return v;
            }
            if(tokens[l].type == Integer) {
                Value v={
                    .val.iVal=atoi(tokens[l].str),
                    .type=INT
                };
                return v;
            }
        Value v= { .type=ERROR };
        return v;
    }
    else  if (check_parentheses(l,r)==true) {
        return eval(l+1,r-1);//删去包围表达式的匹配的括号
    }
    else if(check_minus(l,r)==true) {
        Value v=eval(l+1,r);
        if(v.type==FLOAT) {
            v.val.fVal=-v.val.fVal;
        }
        if(v.type==INT) {
            v.val.iVal=-v.val.iVal;
        }
        return v;
    }
    else {
        Op op = main_operator(l, r);
        Value val1 = eval(l,op.location-1);
        Value val2 = eval(op.location+1,r);
        return meetValue(val1,val2,op);
    }
}
void PrintValue(Value v) {
    switch(v.type) {
        case INT: {
            printf("%d\n",v.val.iVal);
            break;
        }
        case FLOAT: {
            printf("%.6f\n",v.val.fVal);
            break;
        }
        case ERROR: {
            printf("Error\n");
            break;
        }
    }
}
Value evalAssign(int l,int r) {
    int flag=0;
    int position=0;
    for(int i=l;i<=r;i++) {
        if(tokens[i].str[0]=='=') {
            flag=1;
            position=i;
            break;
        }
    }
    if(flag) {
        Value type_and_num=evalAssign(position+1,r);
        int flag1=0;
        for(int i=0;i < count_variables;i++) {
            if(strcmp(tokens[position-1].str,assignments[i].name)==0) {
                switch(type_and_num.type) {
                    case INT: {
                        assignments[i].type = INT_var;
                        assignments[i].val.iVal =type_and_num.val.iVal;
                        break;
                    }
                    case FLOAT: {
                        assignments[i].type = FLOAT_var;
                        assignments[i].val.fVal =type_and_num.val.fVal;
                        break;
                    }
                    default: break;
                }
                return type_and_num;
            }
        }
        strcpy( assignments[count_variables].name , tokens[position-1].str );
        switch(type_and_num.type) {
            case INT: {
                assignments[count_variables].type = INT_var;
                assignments[count_variables].val.iVal =type_and_num.val.iVal;
                break;
            }
            case FLOAT: {
                assignments[count_variables].type = FLOAT_var;
                assignments[count_variables].val.fVal =type_and_num.val.fVal;
                break;
            }
            default: break;
        }
        count_variables++;
        return type_and_num;
    } else {
        return eval(l,r);
    }
}//统一处理两种语句
int main() {
    char line[1025];
    while(fgets(line,1025,stdin)!=NULL) {
        bool flag=true;
        int n=0;
        int j=0;
        for(int i=0;line[i]!='\0';i++) {
            if(line[i]==' '||line[i]=='\n') {
                tokens[n].str[j]='\0';
                if(Is_variable(tokens[n].str)) {
                    tokens[n].type=Variable;
                }
                else if(Is_operator(tokens[n].str)) {
                    tokens[n].type=Operator;
                }
                else if(Is_int(tokens[n].str)) {
                    tokens[n].type=Integer;
                }
                else if(Is_float(tokens[n].str)) {
                    tokens[n].type=Float;
                }
                else {
                    flag=false;
                    break;
                }
                //printf("%s %d\n",tokens[n].str,tokens[n].type);
                n++;
                j=0;
                continue;
            }
            tokens[n].str[j++]=line[i];
        }
        if(flag==false) {
            printf("Error\n");
            continue;
        }//读取
        int l=0;
        int r=n-1;
        int counter=0;
        for(int i=l;i<=r;i++) {
            if(tokens[i].str[0]=='(') {
                counter++;
            }
            else if(tokens[i].str[0]==')') {
                counter--;
            }
        }
        if(counter!=0) {
            printf("Error\n");
            continue;
        }
        PrintValue(evalAssign(l,r));
    }
}