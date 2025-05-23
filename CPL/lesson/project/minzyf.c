#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD 105
#define MAX_ROWS 10
#define MAX_COLS 50

// 用于存储 HTML 元素属性的结构体
typedef struct Element {
    char *name;
    char *color;
    char *src;
    int em;
    int it;
    int un;
    int width;
    int height;
    char *direction;
    char *align_items;
    char *justify_content;
    char *content;
    int div_x;
    int div_y;                  // div 中元素的相对坐标
    struct Element *child[MAX_CHILD]; // 子元素数组
    int count;                  // 子元素数量
} Element;

char img[MAX_ROWS][MAX_COLS];       // 存储渲染的图像
Element *out[MAX_ROWS][MAX_COLS];   // 存储文本元素

// 动态读取标签名
int read_tag(char **tag) {
    int capacity = 4;
    *tag = calloc(capacity, sizeof(char));
    int index = 0;

    while (1) {
        char ch = getchar();
        if (ch == EOF) {
            free(*tag);
            *tag = NULL;
            return 0;
        }
        switch (ch) {
            case '<':
                index = 1;
                break;
            case ' ':
            case '\n':
            case '\t':
                if (index > 0) return 1;
                break;
            case '>':
                return 1;
            default:
                if (index >= capacity) {
                    capacity *= 2;
                    *tag = realloc(*tag, capacity * sizeof(char));
                }
                (*tag)[index - 1] = ch;
                index++;
                break;
        }
    }
}

// 动态读取属性键值对
int read_attr(char **key, char **value) {
    int key_size = 20, val_size = 10;
    int idx = 0, start = 0;
    char ch;

    *key = calloc(key_size, sizeof(char));
    *value = NULL;

    while ((ch = getchar()) != EOF) {
        if (ch == '=') break;
        if (ch == '>') return 0;
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (start) return 1;
            continue;
        }
        start = 1;
        (*key)[idx++] = ch;
        if (idx == key_size) {
            key_size *= 2;
            *key = realloc(*key, key_size);
        }
    }

    idx = 0;
    start = 0;
    *value = calloc(val_size, sizeof(char));
    while ((ch = getchar()) != EOF) {
        if (ch == '"') {
            if (start) break;
            start = 1;
            continue;
        }
        if (!start) continue;
        (*value)[idx++] = ch;
        if (idx == val_size) {
            val_size *= 2;
            *value = realloc(*value, val_size);
        }
    }
    (*value)[idx] = '\0';
    return 1;
}

// 读取元素内容
char* read_content() {
    int size = 10;
    int len = 0;
    char *str = malloc(size);
    char ch;

    while ((ch = getchar()) != EOF) {
        if (ch == '<') break;
        if (len == size) {
            size *= 2;
            str = realloc(str, size);
        }
        str[len++] = ch;
    }
    str[len] = '\0';
    return str;
}

// 将字符串转换为大写
void str_upper(char *str) {
    if (str == NULL) return;
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

// 计算对齐方式的偏移量
int get_offset(char *alignment, int cap, int size, int count) {
    if (alignment == NULL || !strcmp(alignment, "len"))
        return 0;
    if (!strcmp(alignment, "end"))
        return cap - size;
    if (!strcmp(alignment, "center"))
        return (cap - size) / 2;
    if (!strcmp(alignment, "space-evenly"))
        return (cap - size) / (count + 1);
    return 0;
}

// 读取通用属性
void read_common_attrs(Element *e) {
    char *key, *value;
    int next = 1;
    while (next) {
        next = read_attr(&key, &value);
        if (!strcmp(key, "color"))
            e->color = value;
        else if (!strcmp(key, "em"))
            e->em = 1;
        else if (!strcmp(key, "i"))
            e->it = 1;
        else if (!strcmp(key, "u"))
            e->un = 1;
    }
}

// 递归读取元素
Element* read_element(Element *inherit) {
    Element *e = calloc(1, sizeof(Element));

    if (inherit != NULL) {
        e->color = inherit->color;
        e->em = inherit->em;
        e->it = inherit->it;
        e->un = inherit->un;
    }

    int has_attr = read_tag(&e->name);
    if (e->name == NULL)
        return NULL;

    if (!strcmp(e->name, "div")) {
        if (has_attr) {
            read_common_attrs(e);
            char *key, *value;
            int next = 1;
            while (next) {
                next = read_attr(&key, &value);
                if (!strcmp(key, "h"))
                    e->height = atoi(value);
                else if (!strcmp(key, "w"))
                    e->width = atoi(value);
                else if (!strcmp(key, "direction"))
                    e->direction = value;
                else if (!strcmp(key, "align-items"))
                    e->align_items = value;
                else if (!strcmp(key, "justify-content"))
                    e->justify_content = value;
            }
        }

        int max_h = 0, max_w = 0, total_h = 0, total_w = 0;
        int capacity = 2;
        e->count = 0;

        while (1) {
            Element *child = read_element(e);
            if (child == NULL) break;
            e->child[e->count++] = child;
            max_h = fmax(max_h, child->height);
            max_w = fmax(max_w, child->width);
            total_h += child->height;
            total_w += child->width;
        }

        int is_column = (e->direction == NULL || strcmp(e->direction, "row") != 0);
        if (e->height == 0)
            e->height = is_column ? max_h : total_h;
        if (e->width == 0)
            e->width = is_column ? total_w : max_w;

        int offset = get_offset(e->align_items, e->height, total_h, e->count);
        for (int i = 0; i < e->count; i++) {
            e->child[i]->div_x = offset;
            offset += is_column ? e->child[i]->height : e->child[i]->width;
        }
        return e;
    }

    if (!strcmp(e->name, "/div")) {
        return NULL;
    }

    if (!strcmp(e->name, "img")) {
        char *key, *value;
        int next = 1;
        while (next) {
            next = read_attr(&key, &value);
            if (!strcmp(key, "src"))
                e->src = value;
            else if (!strcmp(key, "width"))
                e->width = atoi(value);
        }
        e->height = strlen(e->src) / e->width;
    } else {
        if (has_attr)
            read_common_attrs(e);
        e->content = read_content();
        if (!strcmp(e->name, "h"))
            str_upper(e->content);
        e->width = strlen(e->content);
        e->height = 1;
    }

    while (1) {
        char x = getchar();
        if (x == '>') break;
    }
    return e;
}

// 输出文本元素
void output_text(Element *ele) {
    if (ele->color != NULL) {
        if (!strcmp(ele->color, "red"))
            printf("\033[31m");
        else if (!strcmp(ele->color, "green"))
            printf("\033[32m");
        else if (!strcmp(ele->color, "blue"))
            printf("\033[34m");
    }
    if (ele->em) printf("\033[1m");
    if (ele->it) printf("\033[3m");
    if (ele->un) printf("\033[4m");

    printf("%s\033[0m", ele->content);
}

// 输出渲染结果
void output_render() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (out[i][j] != NULL) {
                output_text(out[i][j]);
                j += out[i][j]->width - 1;
            } else {
                printf("%c", img[i][j]);
            }
        }
        printf("\n");
    }
}

// 释放元素内存
void free_element(Element *ele) {
    if (ele == NULL) return;
    free(ele->name);
    free(ele->color);
    free(ele->src);
    free(ele->direction);
    free(ele->align_items);
    free(ele->justify_content);
    free(ele->content);
    for (int i = 0; i < ele->count; i++) {
        free_element(ele->child[i]);
    }
    free(ele);
}

int x = 0, y = 0;

// 主函数
int main() {
    Element *ele = NULL;
    memset(img, ' ', sizeof(img));
    while (1) {
        ele = read_element(NULL);
        if (ele == NULL) break;
        // judge(x, y, ele); // 假设有渲染逻辑
        x += ele->height;
    }
    output_render();
    free_element(ele);
    return 0;
}

