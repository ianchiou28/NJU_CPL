#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WIDTH 80
#define HEIGHT 40

void apply_formatting(const char *text, const char *styles, char *output) {
    const char *em = "\033[1m";
    const char *italic = "\033[3m";
    const char *underline = "\033[4m";
    const char *color_green = "\033[32m";
    const char *color_red = "\033[31m";
    const char *color_blue = "\033[34m";
    const char *reset = "\033[0m";
    output[0] = '\0';
    if (strstr(styles, "em")) strcat(output, em);
    if (strstr(styles, "i")) strcat(output, italic);
    if (strstr(styles, "u")) strcat(output, underline);
    if (strstr(styles, "color_green")) strcat(output, color_green);
    if (strstr(styles, "color_red")) strcat(output, color_red);
    if (strstr(styles, "color_blue")) strcat(output, color_blue);
    strcat(output, text);
    strcat(output, reset);
}

void render_html(char lines[][256], int num_lines) {
    char output[HEIGHT][WIDTH + 1];
    int cursor_x = 0, cursor_y = 0;
    for (int i = 0; i < HEIGHT; i++) {
        memset(output[i], ' ', WIDTH);
        output[i][WIDTH] = '\0';
    }
    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        char tag[16], attrs[128], content[256];
        int img_width, div_width, div_height;
        char formatted_content[512];
        if (sscanf(line, "<%15[^ >]%127[^>]>%255[^<]</%*[^>]>", tag, attrs, content) == 3) {
            char styles[128] = "";
            if (strstr(attrs, "em")) strcat(styles, "em ");
            if (strstr(attrs, "i")) strcat(styles, "i ");
            if (strstr(attrs, "u")) strcat(styles, "u ");
            if (strstr(attrs, "color=\"green\"")) strcat(styles, "color_green ");
            if (strstr(attrs, "color=\"red\"")) strcat(styles, "color_red ");
            if (strstr(attrs, "color=\"blue\"")) strcat(styles, "color_blue ");
            for (int j = 0; content[j]; j++) {
                content[j] = toupper(content[j]);
            }
            apply_formatting(content, styles, formatted_content);
            for (int j = 0; formatted_content[j] && cursor_x < WIDTH; j++) {
                output[cursor_y][cursor_x++] = formatted_content[j];
            }
            cursor_x = 0;
            cursor_y++;
        } else if (sscanf(line, "<img src=\"%255[^\"]\" width=\"%d\">", content, &img_width) == 2) {
            img_width = img_width > WIDTH ? WIDTH : img_width;
            for (int j = 0; j < img_width && cursor_x < WIDTH; j++) {
                output[cursor_y][cursor_x++] = content[j % strlen(content)];
            }
            cursor_x = 0;
            cursor_y++;
        } else if (sscanf(line, "<div w=\"%d\" h=\"%d\">", &div_width, &div_height) == 2) {
            cursor_y += div_height;
        }
        if (cursor_y >= HEIGHT) break;
    }
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", output[i]);
    }
}

int main() {
    char lines[100][256];
    int num_lines = 0;
    while (fgets(lines[num_lines], sizeof(lines[num_lines]), stdin)) {
        lines[num_lines][strcspn(lines[num_lines], "\n")] = '\0';
        num_lines++;
    }
    render_html(lines, num_lines);
    return 0;
}
