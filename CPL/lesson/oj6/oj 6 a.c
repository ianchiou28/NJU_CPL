#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int value;
    int max_volume;
} Drink;

int cmp(const void *a, const void *b) {
    Drink *drink_a = (Drink *)a;
    Drink *drink_b = (Drink *)b;
    return drink_b->value - drink_a->value;
}

int max_value(int n, int L, int *values, int *volumes) {
    Drink drinks[n];
    for (int i = 0; i < n; i++) {
        drinks[i].value = values[i];
        drinks[i].max_volume = volumes[i];
    }
    qsort(drinks, n, sizeof(Drink), cmp);
    int total_value = 0;
    int current_volume = 0;
    for (int i = 0; i < n; i++) {
        if (current_volume >= L) {
            break;
        }

        int add_volume = fmin(drinks[i].max_volume, L - current_volume);
        total_value += add_volume * drinks[i].value;
        current_volume += add_volume;
    }

    return total_value;
}

int main() {
    int n, L;
    scanf("%d %d", &n, &L);
    int values[n];
    for(int i=0; i<n; i++){
        scanf("%d ", &values[i]);
    }
    scanf("\n");
    int volumes[n];
    for(int i=0; i<n; i++){
        scanf("%d ", &volumes[i]);
    }
    int result = max_value(n, L, values, volumes);
    printf("%d", result);

    return 0;
}