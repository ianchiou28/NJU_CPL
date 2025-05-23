#include <stdio.h>
#include <stdlib.h>

int main() {
    char res[40];
    long long unsigned int start = 0;
    long long unsigned int end = 4294967296;
    long long unsigned int mid = 4294967296/2;

    while (start <= end) {
        printf("%llu\n", mid);
        fflush(stdout);
        scanf("%s", res);
        mid = (start + end)/2;
        switch (res[0]){
            case 'G':{
                end = mid;
                break;
            }
            case 'L':{
                start = mid;
            }  
            case 'E': return 0;
            case 'O': return 0;     
        }
    }
    return mid;
}
