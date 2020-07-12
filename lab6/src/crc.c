#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>


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
    unsigned short crc = 0xFFFF;
    gettimeofday(&tv1, NULL);
    while (fread(&c, 1, 1, fp) != 0) {
        crc ^= c << 8;
        for (int i = 0; i < 8; i++) {
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
        }
    }
    gettimeofday(&tv2, NULL);
    fclose(fp);
    printf("%u", crc);
    if (time)
        printf("\ntime elapsed: %f sec\n",
               (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    return 0;
}
