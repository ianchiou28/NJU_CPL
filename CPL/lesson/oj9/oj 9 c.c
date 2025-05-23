#include <stdio.h>
#include <string.h>

typedef struct {
    char name[21];
    double attck;
    double defense;
    double points;
} Team;

void swap(Team *a, Team *b) {
    Team temp = *a;
    *a = *b;
    *b = temp;
}

void sort_teams(Team teams[], int n, char type) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double score1, score2;
            if (type == 'A') {
                score1 = teams[j].attck;
                score2 = teams[j + 1].attck;
            } else if (type == 'D') {
                score1 = teams[j].defense;
                score2 = teams[j + 1].defense;
            } else {
                score1 = teams[j].points;
                score2 = teams[j + 1].points;
            }
            if (score1 < score2) {
                swap(&teams[j], &teams[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Team teams[1000];
    for (int i = 0; i < n; i++) {
        scanf("%s", teams[i].name);

        double total_a = 0, total_d = 0, total_t = 0;
        for (int j = 0; j < 11; j++) {
            char player_name[21];
            int attack, defense, tactics;
            scanf("%s %d %d %d", player_name, &attack, &defense, &tactics);
            total_a += attack;
            total_d += defense;
            total_t += tactics;
        }

        teams[i].attck = total_a / 11;
        teams[i].defense = total_d / 11;
        teams[i].points = total_t / 11;
    }

    sort_teams(teams, n, 'A');
    for (int i = 0; i < n; i++) {
        printf("%s ", teams[i].name);
    }
    printf("\n");

    sort_teams(teams, n, 'D');
    for (int i = 0; i < n; i++) {
        printf("%s ", teams[i].name);
    }
    printf("\n");

    sort_teams(teams, n, 'T');
    for (int i = 0; i < n; i++) {
        printf("%s ", teams[i].name);
    }
    printf("\n");

    return 0;
}