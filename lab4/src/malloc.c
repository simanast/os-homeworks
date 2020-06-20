#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr1 = malloc(sizeof(int));
    int* ptr2 = malloc(sizeof(int));
    int x = *ptr1;
    int y = *ptr2;
    free(ptr1);
    return 0;
}