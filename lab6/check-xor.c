#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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
    uint8_t xor;
    gettimeofday(&tv1, NULL);
    fread(&c, 1, 1, fp);
    xor = (uint8_t) c;

    while (fread(&c, 1, 1, fp) != 0) {
        xor ^= (uint8_t) c;
    }
    gettimeofday(&tv2, NULL);
    printf("%d", xor);
    if (time)
        printf("\ntime elapsed: %f sec\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    fclose(fp);
    return 0;
}
