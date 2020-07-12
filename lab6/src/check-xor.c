#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char* filename = argv[1];
    short time = 0;
    if (argc == 3 && !strcmp(argv[2], "-time"))
        time = 1;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("cant open file\n");
        exit(1);
    }
    struct timeval tv1, tv2;
    unsigned char c;
    uint8_t xor;
    gettimeofday(&tv1, NULL);
    fread(&c, 1, 1, fp);
    xor = (uint8_t) c;

    while (fread(&c, 1, 1, fp) != 0) {
        xor ^= (uint8_t) c;
    }
    gettimeofday(&tv2, NULL);
    fclose(fp);
    printf("%u", xor);
    if (time) {
        printf("\ntime elapsed: %f sec\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    }
    return 0;
}
