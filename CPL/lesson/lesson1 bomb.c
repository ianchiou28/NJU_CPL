#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    //1.���S??��?
    int tries = 7;
    //2. ��l���H���ƺؤl
    srand(time(NULL));
    //3. �ͦ�1��100�������H����
    int r = rand() % 100 + 1;
    //4.����?�J
    while (tries > 0) {
        int guess;
        printf("%s", "Please enter your guess.");
        scanf_s("%d", &guess);
        //5.??�j�p
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