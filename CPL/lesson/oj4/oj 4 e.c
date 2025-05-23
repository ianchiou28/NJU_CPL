#include <stdio.h>
#include <stdbool.h>

bool is_valid_set(int arr[]) {
    bool seen[10] = {false};
    for (int i = 0; i < 9; i++) {
        int num = arr[i];
        if (num < 1 || num > 9 || seen[num]) {
            return false;
        }
        seen[num] = true;
    }
    return true;
}

bool check_rows(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        int row[9];
        for (int j = 0; j < 9; j++) {
            row[j] = sudoku[i][j];
        }
        if (!is_valid_set(row)) {
            return false;
        }
    }
    return true;
}

bool check_columns(int sudoku[9][9]) {
    for (int j = 0; j < 9; j++) {
        int column[9];
        for (int i = 0; i < 9; i++) {
            column[i] = sudoku[i][j];
        }
        if (!is_valid_set(column)) {
            return false;
        }
    }
    return true;
}

bool check_subgrids(int sudoku[9][9]) {
    for (int row = 0; row < 9; row += 3) {
        for (int col = 0; col < 9; col += 3) {
            int subgrid[9];
            int idx = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    subgrid[idx++] = sudoku[row + i][col + j];
                }
            }
            if (!is_valid_set(subgrid)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int sudoku[9][9];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &sudoku[i][j]);
        }
    }

    if (check_rows(sudoku) && check_columns(sudoku) && check_subgrids(sudoku)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
