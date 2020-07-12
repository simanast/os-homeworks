#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 4096
char* filename;

void create_csum() {
    uint8_t xor = 0;
    unsigned char block[BLOCK_SIZE];
    FILE* fp = fopen(filename, "r");
    FILE* fpw = fopen("csum.txt", "w");
    if (fp == NULL) {
        printf("cant open file\n");
        exit(1);
    }

    int size;
    while (size = fread(block, BLOCK_SIZE, 1, fp) != 0) {
        for (int i = 0; i < size; ++i) {
            xor ^= (uint8_t) block[i];
        }
        fwrite(&xor, 1, 1, fpw);
    }
    fclose(fp);
    fclose(fpw);
}

void check_csum() {
    unsigned char block[BLOCK_SIZE];
    uint8_t xor = 0;
    uint8_t old_xor = 0;
    FILE* fp = fopen(filename, "r");
    FILE* fpr = fopen("csum.txt", "r");
    int size = 0;

    while (size = fread(block, BLOCK_SIZE, 1, fp) != 0) {
        for (int i = 0; i < size; i++) {
            xor ^= block[i];
        }
        if (!fread(&old_xor, 1, 1, fpr)) {
            exit(1);
        };

        if (old_xor != xor) {
            printf("Check-sum FAILED!\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("PASS check-sum\n");
    fclose(fp);
    fclose(fpr);
}

int main(int argc, char** argv) {
    filename = argv[1];
    create_csum();
    check_csum();
    return 0;
}
