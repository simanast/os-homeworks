#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BLOCK 4096
char* pathname;

void create_csum() {
    unsigned char xor = 0;
    unsigned char blocks[BLOCK];
    int fdr;
    int fdw;
    int not_end = 0;
    if ((fdr = open(pathname, O_RDONLY)) == -1) {
        exit(1);
    }
    if ((fdw = open("csum.txt", O_WRONLY | O_CREAT)) == -1) {
        exit(1);
    }
    while ((not_end = read(fdr, blocks, BLOCK)) != -1 && not_end) {
        for (int i = 0; i < not_end; i++) { //the number of bytes read is returned
            xor ^= blocks[i];
        }
        if (write(fdw, &xor, 1) == -1) {
            exit(1);
        }
    }
    close(fdr);
    close(fdw);
}

void check_csum() {
    int fdt;
    if ((fdt = open("test.txt", O_WRONLY | O_APPEND)) == -1) {
        exit(1);
    }
    unsigned char xor = 0;
    unsigned char blocks[BLOCK];
    unsigned char old_xor = 0;
    int fda;
    int fdo;
    int not_end = 0;

    if ((fda = open(pathname, O_RDONLY)) == -1) {
        exit(1);
    }
    if ((fdo = open("csum.txt", O_RDONLY)) == -1) {
        exit(1);
    }
    while ((not_end = read(fda, blocks, BLOCK)) != -1 && not_end) {
        for (size_t i = 0; i < not_end; i++) {
            xor ^= blocks[i];
        }

        if ((not_end = read(fdo, &old_xor, 1)) == -1) {
            exit(1);
        }
        if (old_xor != xor) {
            printf("Check-sum FAILED!\n");
            write(fdt, "Check-sum FAILED!\n", 25);
            exit(EXIT_FAILURE);
        }
    }
    printf("PASS check-sum\n");
    if (write(fdt, "PASS check-sum\n", 20) == -1){
        exit(1);
    }
    close(fda);
    close(fdo);
    close(fdt);
}

int main(int argc, char *argv[]) {
    pathname = argv[1];
    create_csum();
    check_csum();
    return 0;
}
