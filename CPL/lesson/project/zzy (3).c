#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct ele{//定义结构体
    char tag[100];
    char color[100];
    char src[10000];//图片内容
    int e, i, u, w, h;//是否加粗，是否斜体，是否下划线，宽度，高度
    char dir[100], align[200], justify[200];//方向，对齐，对齐方式
    char content[10000];//内容
    int offset_x, offset_y;//偏移量，x，y
    int flagx;
    struct ele *child[104];//子元素
    int size;//子元素个数
} element;//结构体名
char image[10][50];
element *txt[10][50];
int flag[10][50];//用于在一个一个文段的末尾表示要输出\033[0m
int pos_x = 0, pos_y= 0;
void tian(element *e, int pos_x, int pos_y) {//填充到txt和image和flag中
    int i=0;
    if(e->tag[0] == 'h' || e->tag[0] == 'p') {//还未使用offset_xy
        txt[pos_x + e->offset_x][pos_y + e->offset_y] = e;
        for(i=0;i<e->w;i++) {
            image[pos_x + e->offset_x][pos_y + e->offset_y + i] = e->content[i];
            if(i==e->w-1&&e->flagx==1) {
                flag[pos_x + e->offset_x][pos_y + e->offset_y + i] = 1;
            }
        }
    }else if(e->tag[0] == 'i') {
        txt[pos_x + e->offset_x][pos_y + e->offset_y] = e;
        for(i=0;i<e->h;i++) {
            for(int j=0;j<e->w;j++) {
                image[pos_x + e->offset_x + i][pos_y + e->offset_y + j] = e->src[i*e->w + j];
            }
        }
    }

    for(int i=0; i<e->size; i++){
        tian(e->child[i], pos_x + e->offset_x, pos_y + e->offset_y);
    }
    
}
element *read(element *inherit){//读取元素
        char c=getchar();

        while(c=='\n'||c==' ') {//必须有这一步，不知道为啥，否则下面那个EOF判定会不起作用
            c=getchar();
        }
        if(c==EOF) {
            return NULL;
        }
        while(c != '<') {
            c=getchar();
        }
        char str[100];
        int i = 0;
        c=getchar();
        while(c != ' '&&c!='>') {
            str[i++] = c;
            c=getchar();
        }//读取标签
        str[i] = '\0';
        element *e = calloc(1, sizeof(element));
        if(strcmp(str, "h") == 0) {
            e->tag[0] = 'h';
            e->tag[1] = '\0';
            while(c!= '>') {
                char str1[100];
                int i = 0;
                while((c = getchar()) == ' ') {

                }
                if(c=='>') {
                    break;
                }
                e->flagx=1;
                while(c!= '='&&c!=' '&&c!='>') {
                    str1[i++] = c;
                    c=getchar();
                }//属性名
                str1[i] = '\0';
                if(strcmp(str1, "color") == 0) {
                    getchar();//此处假设了=后紧跟双引号
                    i = 0;
                    while((c = getchar()) != '"') {
                        e->color[i++] = c;
                    }
                    e->color[i] = '\0';
                }else if(strcmp(str1, "em") == 0) {
                    e->e = 1;
                }else if(strcmp(str1, "i") == 0) {
                    e->i = 1;
                }else if(strcmp(str1, "u") == 0) {
                    e->u = 1;
                }
            }
            i = 0;
            c=getchar();
            while(c  != '<') {
                e->content[i++] = toupper(c);
                c=getchar();
            }
            e->content[i] = '\0';
            e->w = strlen(e->content);
            e->h = 1;
            e->offset_x=0;
            e->offset_y=0;
            while(c!='/') {
                c=getchar();
            }
            while(c!='>') {
                c=getchar();
            }
        }else if(strcmp(str,"p")==0) {
            e->tag[0] = 'p';
            e->tag[1] = '\0';
            while(c!= '>') {
                char str1[100];
                int i = 0;
                while((c = getchar()) == ' ') {

                }
                if(c=='>') {
                    break;
                }
                e->flagx=1;
                while(c!= '='&&c!=' '&&c!='>') {
                    str1[i++] = c;
                    c=getchar();
                }//属性名
                str1[i] = '\0';
                if(strcmp(str1, "color") == 0) {
                    getchar();//此处假设了=后紧跟双引号
                    i = 0;
                    while((c = getchar()) != '"') {
                        e->color[i++] = c;
                    }
                    e->color[i] = '\0';
                }else if(strcmp(str1, "em") == 0) {
                    e->e = 1;
                }else if(strcmp(str1, "i") == 0) {
                    e->i = 1;
                }else if(strcmp(str1, "u") == 0) {
                    e->u = 1;
                }
            }
            i = 0;
            c=getchar();
            while(c  != '<') {
                e->content[i++] = c;
                c=getchar();
            }
            e->content[i] = '\0';
            e->w = strlen(e->content);
            e->h = 1;
            e->offset_x=0;
            e->offset_y=0;
            while(c!='/') {
                c=getchar();
            }
            while(c!='>') {
                c=getchar();
            }
        }else if(strcmp(str,"img")==0) {
            e->tag[0] = 'i';
            e->tag[1] = 'm';
            e->tag[2] = 'g';
            e->tag[3] = '\0';
            while(c!= '>') {
                char str1[100];
                int i = 0;
                while((c = getchar()) == ' ') {

                }
                if(c=='>') {
                    break;
                }
                while(c!= '='&&c!=' ') {
                    str1[i++] = c;
                    c=getchar();
                }//属性名
                str1[i] = '\0';
                if(strcmp(str1, "src") == 0) {
                    getchar();//此处假设了=后紧跟双引号
                    i = 0;
                    while((c = getchar()) != '"') {
                        e->src[i++] = c;
                    }
                    e->src[i] = '\0';
                }else if(strcmp(str1, "width") == 0) {
                    getchar();
                    i = 0;
                    while((c = getchar()) != '"') {
                        e->w = e->w * 10 + c - '0';
                    }
                }
            }
            e->h = strlen(e->src)/e->w;
            e->offset_x=0;
            e->offset_y=0;
            while(c!='/') {
                c=getchar();
            }
            while(c!='>') {
                c=getchar();
            }
        }
        // 处理 div 和其子元素布局
        if(strcmp(str, "div") == 0) {
            e->tag[0] = 'd';
            e->tag[1] = 'i';
            e->tag[2] = 'v';
            e->tag[3] = '\0';

            // 解析 div 的属性
            while(c != '>') {
                char str1[1000];
                int i = 0;
                while((c = getchar()) == ' ') {} // 跳过空格
                if(c == '>') break; // 结束标记
                while(c != '=' && c != ' ' && c != '>') {
                    str1[i++] = c;
                    c = getchar();
                }
                str1[i] = '\0';
                
                if(strcmp(str1, "h") == 0) {
                    getchar(); // 跳过等号
                    i = 0;
                    while((c = getchar()) != '"') {} // 跳过引号
                    e->h = 0;
                    while((c = getchar()) != '"') {
                        e->h = e->h * 10 + (c - '0');
                    }
                } else if(strcmp(str1, "w") == 0) {
                    getchar(); // 跳过等号
                    i = 0;
                    while((c = getchar()) != '"') {} // 跳过引号
                    e->w = 0;
                    while((c = getchar()) != '"') {
                        e->w = e->w * 10 + (c - '0');
                    }
                } else if(strcmp(str1, "direction") == 0) {
                    i = 0;
                    while((c = getchar()) != '"') {}
                    while((c = getchar()) != '"') {
                        e->dir[i++] = c;
                    }
                    e->dir[i] = '\0';
                } else if(strcmp(str1, "align-items") == 0) {
                    i = 0;
                    while((c = getchar()) != '"') {}
                    while((c = getchar()) != '"') {
                        e->align[i++] = c;
                    }
                    e->align[i] = '\0';
                } else if(strcmp(str1, "justify-content") == 0) {
                    i = 0;
                    while((c = getchar()) != '"') {}
                    while((c = getchar()) != '"') {
                        e->justify[i++] = c;
                    }
                    e->justify[i] = '\0';
                }
            }

            // 读取子元素
            int max_h = 0, max_w = 0;
            int total_h = 0, total_w = 0;

            while(1) {
                element *child = read(e);  // 递归读取子元素
                if(child == NULL) break;

                max_h = (max_h > child->h ? max_h : child->h);
                max_w = (max_w > child->w ? max_w : child->w);
                total_h += child->h;
                total_w += child->w;
                e->child[e->size++] = child;
            }

            // 确定 div 的宽度和高度
            if(e->h == 0) {
                if(strcmp(e->dir, "column") == 0) e->h = max_h;
                else e->h = total_h;
            }
            if(e->w == 0) {
                if(strcmp(e->dir, "column") == 0) e->w = total_w;
                else e->w = max_w;
            }

            // 计算子元素的偏移量
            int of = 0;
            for(int i = 0; i < e->size; i++) {
                if(strcmp(e->dir, "column") == 0) {
                    e->child[i]->offset_x = of;
                    if(strcmp(e->align, "center") == 0) {
                        e->child[i]->offset_y = (e->w - e->child[i]->w) / 2;
                    } else if(strcmp(e->align, "end") == 0) {
                        e->child[i]->offset_y = e->w - e->child[i]->w;
                    } else {
                        e->child[i]->offset_y = 0;
                    }
                    of += e->child[i]->h;
                } else {
                    e->child[i]->offset_y = of;
                    if(strcmp(e->align, "center") == 0) {
                        e->child[i]->offset_x = (e->h - e->child[i]->h) / 2;
                    } else if(strcmp(e->align, "end") == 0) {
                        e->child[i]->offset_x = e->h - e->child[i]->h;
                    } else {
                        e->child[i]->offset_x = 0;
                    }
                    of += e->child[i]->w;
                }
            }
        }

        //把内容填充到txt和image和flag中
        return e;
}


int main(){

    for(int i=0; i<10; i++){
        for(int j=0; j<50; j++){
            txt[i][j] = NULL;
            image[i][j] = ' ';
            flag[i][j] = 0;
        }
    }
    while(1){
        element *e = read(NULL);
        if(e == NULL) break;
        tian(e, pos_x, pos_y);
        pos_x += e->h;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 50; j++) {
            if (txt[i][j] != NULL) {
                element *el = txt[i][j];
                if (el->tag[0] == 'i' && el->tag[1] == 'm' && el->tag[2] == 'g') {
                    // 处理图片的多行输出
                    for (int img_row = 0; img_row < el->h; img_row++) {
                        for (int img_col = 0; img_col < el->w; img_col++) {
                            printf("%c", el->src[img_row * el->w + img_col]);
                        }
                        printf("\n");
                    }
                    j += el->w - 1; // 跳过已处理的宽度部分
                } else {
                    // 处理文本颜色和格式
                    if (el->color[0] != '\0') {
                        if (strcmp(el->color, "red") == 0) {
                            printf("\033[31m");
                        } else if (strcmp(el->color, "blue") == 0) {
                            printf("\033[34m");
                        } else if (strcmp(el->color, "green") == 0) {
                            printf("\033[32m");
                        }
                    }
                    if (el->e) {
                        printf("\033[1m");
                    }
                    if (el->i) {
                        printf("\033[3m");
                    }
                    if (el->u) {
                        printf("\033[4m");
                    }
                    printf("%c", image[i][j]);
                    if (flag[i][j] == 1) {
                        printf("\033[0m");
                    }
                }
            } else {
                printf("%c", image[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}