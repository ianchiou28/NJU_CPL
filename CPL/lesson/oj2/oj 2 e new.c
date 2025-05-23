#include <stdio.h>

int main() {
    int sum = 0;
    int N;

    scanf("%d", &N);
    int a = 495;

    while (N != a && N>0) {

        int digits[3] = {N % 10, (N / 10) % 10, N / 100};

        for (int i = 0; i < 2; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (digits[i] < digits[j]) {
                    int temp = digits[i];
                    digits[i] = digits[j];
                    digits[j] = temp;
                }
            }
        }

        int max_num = digits[0] * 100 + digits[1] * 10 + digits[2];
        int min_num = digits[2] * 100 + digits[1] * 10 + digits[0];
        int diff = max_num - min_num;
        int result = N-diff;

        if (result>0) {
            sum += result;
            N = N - result;
        }
        else{
            N = N - result;

        }
    }
    printf("%d", sum);
    return 0;
}