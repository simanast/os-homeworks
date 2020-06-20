#include <stdlib.h>
#include <stdio.h>

int main() {
    int n = 100;
    int i = 5;
    int* data = malloc(sizeof(int) * n);
    data[i] = 1281;
    free(data);
    printf("%d\n", data[i]);
    return 0;
}

