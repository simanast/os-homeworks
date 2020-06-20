#include <stdlib.h>

int main() {
    int n = 100;
    int* data = malloc(sizeof(int) * n);
    data[n] = 0;
    return 0;
}