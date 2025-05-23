#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000000

typedef struct {
    int key;
    int value;
} Pair;

Pair* create_pair(int key, int value){
    Pair* pair = (Pair*)malloc(sizeof(Pair));
    pair->key = key;
    pair->value = value;
    return pair;
}

void insert(Pair** hash_table, int key, int value, int size){
    int index = key % size;
    while(hash_table[index] != NULL){
        index = (index + 1) % size;
    }
    hash_table[index] = create_pair(key, value);
}

int search(Pair** hash_table, int key, int size){
    int index = key % size;
    while(hash_table[index] != NULL){
        if(hash_table[index]->key == key){
            return hash_table[index]->value;
        }
        index = (index + 1) % size;
    }
    return -1;
}

int main(){
    int n;
    long long int q;
    scanf("%d %lld", &n, &q);
    int *a = (int*)malloc(n * sizeof(int));
    Pair** hash_table = (Pair**)malloc(n * sizeof(Pair*));
    memset(hash_table, 0, n * sizeof(Pair*));
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        insert(hash_table, a[i], i, n);
    }
    while(q--){
        int x;
        scanf("%d\n", &x);
        int result = search(hash_table, x, n);
        printf("%d\n", result);
    }
    free(a);
    for(int i = 0; i < n; i++){
        if(hash_table[i] != NULL){
            free(hash_table[i]);
        }
    }
    free(hash_table);
    return 0;
}

