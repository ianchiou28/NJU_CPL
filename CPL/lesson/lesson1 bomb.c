#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    //1.取范??机?
    int tries = 7;
    //2. 初始化隨機數種子
    srand(time(NULL));
    //3. 生成1到100之間的隨機數
    int r = rand() % 100 + 1;
    //4.提示?入
    while (tries > 0) {
        int guess;
        printf("%s", "Please enter your guess.");
        scanf_s("%d", &guess);
        //5.??大小
        if (guess == r) {
            printf("%s\n", "Congratulation!!! The bomb is stopped.");
        }
        else if (guess < r) {
            printf("%s\n", "Your guess is lower than the bomb.");
        }
        else {
            printf("%s\n", "Your guess is greater than the bomb.");
        }
        tries = tries - 1;
    }
    if (tries == 0) {
        printf("%s\n", "You lose~~~~ hahahaha");
        printf("%s", "The answer is ");
        printf("%d.\n", r);
    }

    return 0;

}