#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int size = 2 * n - 1;
    int arr[size];
    
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    qsort(arr, size, sizeof(int), compare);

    int result = arr[size - 1];

    for (int i = 0; i < size - 1; i += 2) {
        if (arr[i] != arr[i + 1]) {
            result = arr[i];
            break;
        }
    }
    printf("%d", result);
    return 0;
}