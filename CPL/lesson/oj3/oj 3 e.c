#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);

    char **a = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        a[i] = (char *)malloc(99999 * sizeof(char));
    }

    for (int i = 0; i < n; i++) {
        fgets(a[i], 99999, stdin);
        a[i][strcspn(a[i], "\n")] = '\0';
        int m = strlen(a[i]);
        int sum = 0;
        int Errorflag = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') {
                sum += pow(3, m - j - 1);
            } else if (a[i][j] == 'Z') {
                sum += (-1) * pow(3, m - j - 1);
            } else if (a[i][j] != '0') {
                printf("Radix Error\n");
                Errorflag++;
            }
            if(Errorflag>0){
            break;
            }
        }
        if(Errorflag==0){
            printf("%d\n", sum);
        }
    }
    for (int i = 0; i < n; i++){
        free(a[i]);
    }
    free(a);

    return 0;
}