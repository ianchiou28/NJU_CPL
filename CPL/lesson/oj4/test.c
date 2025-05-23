#include <stdio.h>
#include <stdbool.h>

int check(int n, int x, int board[10][10], int player) {
    for (int i = 0; i < n; i++) {
        int row = 0, col = 0;
        for (int j = 0; j < n; j++) {
            row = (board[i][j] == player) ? row + 1 : 0;
            col = (board[j][i] == player) ? col + 1 : 0;
            if (row == x || col == x) return player;
        }
    }
    for (int d = 0; d <= n - x; d++) {
        int main = 0, anti = 0;
        for (int i = 0; i < x; i++) {
            main = (board[d + i][d + i] == player) ? main + 1 : 0;
            anti = (board[d + i][n - d - i - 1] == player) ? anti + 1 : 0;
            if (main == x || anti == x) return player;
        }
    }
    return 0;
}

int main() {
    int t, x;
    scanf("%d %d", &t, &x);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        int board[10][10];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &board[i][j]);
            }
        }

        bool winners[3] = {0, 0, 0};
        for (int player = 1; player <= 4; player <<= 1) {
            if (check(n, x, board, player)) {
                winners[player == 1 ? 0 : (player == 2 ? 1 : 2)] = true;
            }
        }

        int win_count = winners[0] + winners[1] + winners[2];
        if (win_count == 0) printf("draw\n");
        else if (win_count > 1) printf("draw\n");
        else if (winners[0]) printf("1\n");
        else if (winners[1]) printf("2\n");
        else if (winners[2]) printf("4\n");
    }

    return 0;
}
