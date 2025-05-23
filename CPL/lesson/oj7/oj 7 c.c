#include <stdio.h>
#include <string.h>

int main(){
    char *s, *t;
    size_t lens = 0, lent = 0;
    s = (char *)malloc(100005 * sizeof(char));
    t = (char *)malloc(100005 * sizeof(char));
    scanf("%s", &*s);
    scanf("%s", &*t);
    char *ptr = s;
    while(*ptr++) lens++;
    ptr = t;
    while(*ptr++) lent++;

    for(char *i = s; i<=s+lens - lent; i++){
        char *j = i, *k = t;
        while(*k && *j == *k){
            j++;
            k++;
        }

        if not(*k){
            printf("lld ", i-s);
        }
    }
    free(s);
    free(t);

    return 0;
}