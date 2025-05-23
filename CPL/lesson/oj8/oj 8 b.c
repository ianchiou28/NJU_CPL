#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    int T;
    scanf("%d\n", &T);
    char *s1, *s2;
    char *input = (char*)malloc(3001*sizeof(char));
    int ds1, ds2, size;
    while(T--){
        scanf("%s", input);
        s1 = strtok(input, ";");
        s2 = strtok(NULL, ";");
        ds1 = stoi(strtok(NULL, ";"));
        ds2 = stoi(strtok(NULL, ";"));
        size = stoi(strtok(NULL, ";"));
        char *s3 = (char *)malloc(size * sizeof(char));
        size_t len1 = strlen(s1), len2 = strlen(s2), len3 = size - 1;
        size_t i=0, j=0, k=0;
        while(i<len1&&j<len2&&k<len3){
            for(size_t a = 0; a<ds1; a++){
                s3[k++] = s1[i++];
            }
            for(size_t b = 0; b<ds2; b++){
                s3[k++] = s2[j++];
            }
            while(i<len1&&k<len3){
                s3[k++] = s1[i++];
            }
            while(j<len2&&k<len3){
                s3[k++] = s2[j++];
            }
            s3[k] = 0;
            printf("%s\n", s3);
            free(s3);
        }
    }
    return 0;

}