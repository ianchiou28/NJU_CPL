#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char input[1048];
    scanf("%1024[^\n]", input);
    int len = strlen(input);
    for(int i=0; i<len; i++){
        if(isupper(input[i]) && i!=0){
            printf(" %c", tolower(input[i]));
        }
        else{
            printf("%c", tolower(input[i]));
        }
    }

    return 0;
}
