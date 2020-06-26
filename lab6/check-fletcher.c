#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char** argv) {
    char* filename = argv[1];
    short time = 0;
    if (argc == 3)
        time = 1;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("cant open file\n");
    }
    struct timeval tv1, tv2;
    char c;
    int16_t sum;
    uint8_t sum1;
    uint8_t sum2;
    gettimeofday(&tv1, NULL);
    fread(&c, 1, 1, fp);
    sum1 = (uint8_t) c;

    while (fread(&c, 1, 1, fp) != 0) {
        sum1 = ((uint8_t) c + sum1) % 255;
        sum2 = (sum1 + sum2) % 255;
    }
    sum = (sum1 << 8) + sum2;
    gettimeofday(&tv2, NULL);
    fclose(fp);
    printf("%d", sum);
    if (time) {
        printf("\ntime elapsed: %f sec\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    }
    return 0;
}
