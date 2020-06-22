#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// argv[1] - требуемое количество памяти в мб
// argv[2] - заданное количество секунд
int main(int argc, char* argv[]) {
    int bytes = strtol(argv[1], NULL, 10) * 1024 * 1024;
    int sec = 100;
    if (argc > 2) {
        sec = strtol(argv[2], NULL, 10);
    }
    int* array = (int*) malloc(bytes);
    if (!array) {
        printf("malloc() error\n");
        return 0;
    }
    printf("allocated %d bytes\n", bytes);
    int n = bytes / 4;
    clock_t start = clock();
    int i = 0;
    while ((clock() - start) / CLOCKS_PER_SEC <= sec) {
        if (i < n) {
            array[i] = i;
        }
        i++;
    }
    printf("finishing\n");
    return 0;
}
