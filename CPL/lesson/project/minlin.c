#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ATTR_NUM 5
#define max(a, b) (a > b ? a : b)

typedef struct _ele{
    char *tag;
    char *color;
    char *src;
    int emphasis, italic, underline, width, higth;
    char *direction, *align, *justify;
    char *content;
    int offset_x, offset_y;

    struct _ele *child[105];
    int child_len;
} element;

int read_tag(char **tag){
    *tag = calloc(4, sizeof(char));
    int start = 0;
    while(1){
        char x = getchar();
        if(x == EOF){
            free(*tag);
            *tag = NULL;
            return 0;
        }
        if(x == '<'){
            start = 1;
            continue;
        }
        if(x == ' ' || x == '\n' || x == '\t'){
            if(start) return 1;
            else continue;
        }
        if(x == '>') return 0;
        (*tag)[start-1] = x;
        start++;
    }
}

int read_attr(char **key, char **value){
    int idx = 0, start = 0;
    *key = calloc(20, sizeof(char));
    *value = NULL;

    while(1){
        char x = getchar();
        if(x == '=') break;
        if(x == '>') return 0;
        if(x == ' ' || x == '\n' || x == '\t'){
            if(start) return 1;
            continue;
        }
        start = 1;
        (*key)[idx++] = x;
    }

    idx = 0;
    start = 0;
    *value = calloc(10, sizeof(char));
    int size = 10;
    while(1){
        char x = getchar();
        if(x == '\"'){
            if(start) break;
            start = 1;
            continue;  
        }
        if(!start) continue;

        if(idx == size){
            size *= 2;
            *value = realloc(*value, size);
        }
        (*value)[idx++] = x;
    }
    if(idx == size){
        size += 2;
        *value = realloc(*value, size);
    }
    (*value)[idx] = 0;
    return 1;
}

char* read_content(){
    char *str = malloc(sizeof(char) * 10);
    int size = 10, len = 0;
    int start = 0;
    while(1){
        char x = getchar();
        if(x == '<')
            break;
        if(size == len){
            size *= 2;
            str = realloc(str, size);
        }
        str[len++] = x;
    }
    if(size == len){
        size += 2;
        str = realloc(str, size);
    }
    str[len] = 0;
    return str;
}

void str_upper(char *str){
    int i=0;
    while(str[i]){
        str[i] = toupper(str[i]);
        i++;
    }
}

int get_offset(char *type, int element, int total, int num){
    if(type == NULL || !strcmp(type, "start"))
        return 0;
    else if(!strcmp(type, "end"))
        return element - total;
    else if(!strcmp(type, "center"))
        return (element - total) / 2;
    else if(!strcmp(type, "space-evenly"))
        return (element - total) / (num + 1);
    return 0;
}

element *read_element(element *inherit){
    element *e = calloc(1, sizeof(element));
    if(inherit != NULL){
        e->color = inherit->color;
        e->emphasis = inherit->emphasis;
        e->italic = inherit->italic;
        e->underline = inherit->underline;
    }

    int has_attr = read_tag(&e->tag);

    if(e->tag == NULL)
        return NULL;

    if(!strcmp(e->tag, "div")){
        if(has_attr){
            char *key, *value;
            int next = 1;
            while(next){
                next = read_attr(&key, &value);
                if(!strcmp(key, "h"))
                    e->higth = atoi(value);
                else if(!strcmp(key, "w"))
                    e->width = atoi(value);
                else if(!strcmp(key, "direction"))
                    e->direction = value;
                else if(!strcmp(key, "align-items"))
                    e->align = value;
                else if(!strcmp(key, "justify-content"))
                    e->justify = value;

                if(!strcmp(key, "color"))
                    e->color = value;
                else if(!strcmp(key, "em"))
                    e->emphasis = 1;
                else if(!strcmp(key, "i"))
                    e->italic = 1;
                else if(!strcmp(key, "u"))
                    e->underline = 1;
            }
        }

        int max_h = 0, max_w = 0;
        int total_h = 0, total_w = 0;
        
        while(1){
            element *child = read_element(e);
            if(child == NULL) break;
            max_h = max(max_h, child->higth);
            max_w = max(max_w, child->width);
            total_h += child->higth;
            total_w += child->width;
            e->child[e->child_len++] = child;
        }


        int is_column = 1;
        if(e->direction == NULL || !strcmp(e->direction, "row")) is_column = 0;

        if(e->higth == 0)
            if(is_column) e->higth = max_h;
            else e->higth = total_h;
        if(e->width == 0)
            if(is_column) e->width = total_w;
            else e->width = max_w;

        int offset, doff = 0;
        if(is_column == 0){
            offset = get_offset(e->align, e->higth, total_h, e->child_len);
            if(e->align != NULL && !strcmp(e->align, "space-evenly")) doff = offset;
        }
        else{
            offset = get_offset(e->justify, e->width, total_w, e->child_len);
            if(e->justify != NULL && !strcmp(e->justify, "space-evenly")) doff = offset;
        }

        for(int i=0; i<e->child_len; i++){
            if(is_column){
                e->child[i]->offset_x = get_offset(e->align, e->higth, e->child[i]->higth, 1);
                e->child[i]->offset_y = offset;
                offset += e->child[i]->width;
            }
            else{
                e->child[i]->offset_x = offset;
                e->child[i]->offset_y = get_offset(e->justify, e->width, e->child[i]->width, 1);
                offset += e->child[i]->higth;
            }
            offset += doff;
        }
        return e;
    }
    else if(!strcmp(e->tag, "/div"))
        return NULL;
    else if(!strcmp(e->tag, "img")){
        char *key, *value;
        int next = 1;
        while(next){
            next = read_attr(&key, &value);
            if(!strcmp(key, "src"))
                e->src = value;
            else if(!strcmp(key, "width"))
                e->width = atoi(value);
        }
        e->higth = strlen(e->src) / e->width;
    }
    else{
        if(has_attr){
            char *key, *value;
            int next = 1;
            while(next){
                next = read_attr(&key, &value);
                if(!strcmp(key, "color"))
                    e->color = value;
                else if(!strcmp(key, "em"))
                    e->emphasis = 1;
                else if(!strcmp(key, "i"))
                    e->italic = 1;
                else if(!strcmp(key, "u"))
                    e->underline = 1;
            }
        }

        e->content = read_content();
        if(!strcmp(e->tag, "h"))
            str_upper(e->content);
        e->width = strlen(e->content);
        e->higth = 1;
    }
    while(1){
        char x = getchar();
        if(x == '>') break;
    }
    return e;
}

char image[10][50];
element *txt[10][50];
int x = 0, y = 0;

void rendering(element *e, int pos_x, int pos_y){
    if(!strcmp(e->tag, "h") || !strcmp(e->tag, "p")){
        txt[pos_x + e->offset_x][pos_y + e->offset_y] = e;
    }
    else if(!strcmp(e->tag, "img")){
        int now_x = pos_x + e->offset_x;
        int now_y = pos_y + e->offset_y;
        for(int i=0; i<e->higth; i++)
            for(int j=0; j<e->width; j++)
                image[now_x+i][now_y+j] = e->src[i*e->width + j];
    }
    else if(!strcmp(e->tag, "div")){
        for(int i=0; i<e->child_len; i++){
            rendering(e->child[i], pos_x + e->offset_x, pos_y + e->offset_y);
        }
    }
}

void show_txt(element *e){
    int has_change = 0;
    if(e->color != NULL){
        if(!strcmp(e->color, "red"))
            printf("\033[31m");
        else if(!strcmp(e->color, "blue"))
            printf("\033[34m");
        else if(!strcmp(e->color, "green"))
            printf("\033[32m");
        has_change = 1;
    }
    if(e->emphasis) printf("\033[1m");
    if(e->italic) printf("\033[3m");
    if(e->underline) printf("\033[4m");

    has_change |= e->emphasis | e->italic | e->underline;
    printf("%s", e->content);
    if(has_change)
        printf("\033[0m");
}

void show(){
    for(int i=0; i<10; i++){
        for(int j=0; j<50; j++){
            if(txt[i][j] != NULL){
                show_txt(txt[i][j]);
                j += txt[i][j]->width-1;
            }
            else
                printf("%c", image[i][j]);
        }
        printf("\n");
    }
}

int main(){
    
    int pos_x = 0, pos_y = 0;
    memset(image, ' ', sizeof(image));
    while(1){
        element *e = read_element(NULL);
        if(e == NULL) break;

        rendering(e, pos_x, pos_y);
        pos_x += e->higth;
    }
    show();

    return 0;
}
