#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}
typedef struct element {
	char* type;
	char* color;
	char* src;
	int em;
	int i;
	int u;
	int width;
	int height;
	char* direction;
	char* align_items;
	char* justify_content;
    char* content;
	int x;
	int y;
	struct element* son[200];
	int son_length;
}element;
char img[10][50];
element* output[10][50];
int x = 0, y = 0;
int get_type(char** now) {
    *now = calloc(4, sizeof(char));
    int t = 0;
    while (1) {
        char input = getchar();
        if (input == EOF) {
            free(*now);
            *now = NULL;
            return 0;
        }
        if (input == '<') {
            t = 1;
            continue;
        }
        if (input == ' ' || input == '\n' || input == '\t') {
            if (t != 0) {
                return 1;
            }
            else {
                continue;
            }
        }
        if (input == '>') {
            return 0;
        }
        (*now)[t - 1] = input;
        t++;
    }
}
int get_attribute(char** item, char** digit) {
    bool flag = false;
    int i = 0;
    *item = calloc(20, sizeof(char));
    *digit = NULL;
    while (1) {
        char input = getchar();
        if (input == '=') {
            break;
        }
        if (input == '>') {
            return 0;
        }
        if (input == ' ' || input == '\n' || input == '\t') {
            if (flag == true) {
                return 1;
            }
            continue;
        }
        flag = true;
        (*item)[i++] = input;
    }
    i = 0;
    flag = false;
    *digit = calloc(10, sizeof(char));
    int size = 10;
    while (1) {
        char input = getchar();
        if (input == '\"') {
            if (flag == true) {
                break;
            }
            flag=true;
            continue;
        }
        if(flag==false){
            continue;
        }
        if (flag == false) {
            continue;
        }
        if (size == i) {
            *digit = realloc(*digit, size * 2);
            size *= 2;
        }
        (*digit)[i++] = input;
    }
    if (i == size) {
        *digit = realloc(*digit, size+2);
        size += 2;
    }
    (*digit)[i] = 0;
    return 1;
}
char* get_content() {
    char* s = (char*)malloc(sizeof(char) * 10);
    int size = 10, len = 0;
    int start = 0;
    while (1) {
        char input = getchar();
        if (input == '<') {
            break;
        }
        if (size == len) {
            s = realloc(s, size*2);
            size *= 2;
        }
        s[len++] = input;
    }
    if (size == len) {
        s = realloc(s, size+2);
        size += 2;
    }
    s[len] = 0;
    return s;
}
int get_position_offset(char* type, int height, int sum, int num) {
    if (type == NULL || strcmp(type, "start") == 0) {
        return 0;
    }
    else if (strcmp(type, "end") == 0) {
        return height - sum;
    }
    else if (strcmp(type, "center") == 0) {
        return (height - sum) / 2;
    }
    else if (strcmp(type, "space-evenly") == 0) {
        return (height - sum) / (num + 1);
    }
    return 0;
}
element* get_element(element* father) {
    element* data = calloc(1, sizeof(element));
    if (father != NULL) {
        data->color = father->color;
        data->em = father->em;
        data->i = father->i;
        data->u = father->u;
    }
    int flag = get_type(&data->type);
    if (data->type == NULL) {
        return NULL;
    }
    if (strcmp(data->type, "div") == 0) {
        if (flag == 1) {
            char* item, * digit;
            int t = 1;
            while (t) {
                t = get_attribute(&item, &digit);
                if (strcmp(item, "h") == 0)
                    data->height = atoi(digit);
                else if (strcmp(item, "w") == 0)
                    data->width = atoi(digit);
                else if (strcmp(item, "direction") == 0)
                    data->direction = digit;
                else if (strcmp(item, "align-items") == 0)
                    data->align_items = digit;
                else if (strcmp(item, "justify-content") == 0)
                    data->justify_content = digit;
                if (strcmp(item, "color") == 0)
                    data->color = digit;
                else if (strcmp(item, "em") == 0)
                    data->em = 1;
                else if (strcmp(item, "i") == 0)
                    data->i = 1;
                else if (strcmp(item, "u") == 0)
                    data->u = 1;
            }
        }
        int max_h = 0, max_w = 0, total_h = 0, total_w = 0;
        while (1) {
            element* Son = get_element(data);
            if (Son == NULL) {
                break;
            }
            max_h = max(max_h, Son->height);
            max_w = max(max_w, Son->width);
            total_h = total_h + Son->height;
            total_w = total_w + Son->width;
            data->son[data->son_length++] = Son;
        }
        bool mark = true;
        if(data->direction == NULL) {
            mark = false;
        }
        else if(strcmp(data->direction, "row")==0){
            mark=false;
        }
        if (data->height == 0) {//判断div区域的大小
            if (mark == true) {
                data->height = max_h;
            }
            else {
                data->height = total_h;
            }
        }
        if (data->width == 0) {
            if (mark == true) {
                data->width = total_w;
            }
            else {
                data->width = max_w;
            }
        }
        int position_offset, distribution_offset = 0;//位置偏移量和一个特殊的偏移量
        if (mark == false) {
            position_offset = get_position_offset(data->align_items, data->height, total_h, data->son_length);
            if (data->align_items != NULL && strcmp(data->align_items, "space-evenly") == 0) {
                distribution_offset = position_offset;
            }
        }
        else {
            position_offset = get_position_offset(data->justify_content, data->width, total_w, data->son_length);
            if (data->justify_content != NULL && strcmp(data->justify_content, "space-evenly") == 0) {
                distribution_offset = position_offset;
            }
        }
        for (int i = 0; i < data->son_length; i++) {
            if (mark == true) {
                data->son[i]->x = get_position_offset(data->align_items, data->height, data->son[i]->height, 1);
                data->son[i]->y = position_offset;
                position_offset += data->son[i]->width;
            }
            else {
                data->son[i]->x = position_offset;
                data->son[i]->y = get_position_offset(data->justify_content, data->width, data->son[i]->width, 1);
                position_offset += data->son[i]->height;
            }
            position_offset = position_offset+distribution_offset;
        }
        return data;
    }
    else if (strcmp(data->type, "/div") == 0) {
        return NULL;
    }
    else if (strcmp(data->type, "img") == 0) {
        char* item, * digit;
        int t = 1;
        while (t) {
            t = get_attribute(&item, &digit);
            if (strcmp(item, "src") == 0) {
                data->src = digit;
            }
            else if (strcmp(item, "width") == 0) {
                data->width = atoi(digit);
            }
        }
        data->height = strlen(data->src) / data->width;
    }
    else {
        if (flag == 1) {
            char* item, * digit;
            int t = 1;
            while (t) {
                t = get_attribute(&item, &digit);
                if (strcmp(item, "color") == 0) {
                    data->color = digit;
                }
                else if (strcmp(item, "em") == 0) {
                    data->em = 1;
                }
                else if (strcmp(item, "i") == 0) {
                    data->i = 1;
                }
                else if (strcmp(item, "u") == 0) {
                    data->u = 1;
                }
            }
        }
        data->content = get_content();
        if (strcmp(data->type, "h") == 0) {
            for (int i = 0;i<strlen(data->content);i++) {
                data->content[i] = toupper(data->content[i]);
            }
        }
        data->width = strlen(data->content);
        data->height = 1;
    }
    while (1) {
        char input = getchar();
        if (input == '>') {
            break;
        }
    }
    return data;
}
int main() {
    char img[10][50];
    element* output[10][50] = {NULL};

    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 49; j++) {
            img[i][j] = ' ';
        }
    }

    int x = 0, y = 0;
    while (1) {
        element* data = get_element(NULL);
        if (data == NULL) {
            break;
        } else {
            if (strcmp(data->type, "h") == 0 || strcmp(data->type, "p") == 0) {
                output[x + data->x][y + data->y] = data;
            } else if (strcmp(data->type, "img") == 0) {
                int now_x = x + data->x;
                int now_y = y + data->y;
                for (int i = 0; i < data->height; i++) {
                    for (int j = 0; j < data->width; j++) {
                        img[now_x + i][now_y + j] = data->src[i * data->width + j];
                    }
                }
            } else if (strcmp(data->type, "div") == 0) {
                for (int i = 0; i < data->son_length; i++) {
                    element* child = data->son[i];
                    if (strcmp(child->type, "h") == 0 || strcmp(child->type, "p") == 0) {
                        output[x + child->x][y + child->y] = child;
                    } else if (strcmp(child->type, "img") == 0) {
                        int now_x = x + child->x;
                        int now_y = y + child->y;
                        for (int i = 0; i < child->height; i++) {
                            for (int j = 0; j < child->width; j++) {
                                img[now_x + i][now_y + j] = child->src[i * child->width + j];
                            }
                        }
                    }
                }
            }
            x += data->height;
        }
    }

    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 49; j++) {
            if (output[i][j] == NULL) {
                printf("%c", img[i][j]);
            } else {
                element* data = output[i][j];
                int flag = 0;
                if (data->color != NULL) {
                    if (strcmp(data->color, "red") == 0) {
                        printf("\033[31m");
                    } else if (strcmp(data->color, "blue") == 0) {
                        printf("\033[34m");
                    } else if (strcmp(data->color, "green") == 0) {
                        printf("\033[32m");
                    }
                    flag = 1;
                }
                if (data->em == 1) {
                    printf("\033[1m");
                }
                if (data->i == 1) {
                    printf("\033[3m");
                }
                if (data->u == 1) {
                    printf("\033[4m");
                }
                flag |= data->em | data->i | data->u;
                printf("%s", data->content);
                if (flag) {
                    printf("\033[0m");
                }
                j += data->width - 1;
            }
        }
        printf("\n");
    }

    return 0;
}