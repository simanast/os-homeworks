#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int n = 300000;
    int size = 1;
    char record[size];
    char filepath1[] = "test1.txt";
    char filepath2[] = "test2.txt";
    struct timeval tv1, tv2;

    int fd = creat(filepath1, S_IRWXU);
    if (fd == -1) {
        fprintf(stderr, "cant create file");
        _exit(1);
    }

    gettimeofday(&tv1, NULL);
    for (int i = 0; i < n; ++i) {
        write(fd, record, size);
    }

    gettimeofday(&tv2, NULL);
    printf("time elapsed for POSIX function\t\t: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));
    close(fd);

    FILE* file2 = fopen(filepath2, "w");
    gettimeofday(&tv1, NULL);
    for (int j = 0; j < n; ++j) {
        fwrite(record, size, 1, file2);
    }
    gettimeofday(&tv2, NULL);
    printf("time elapsed for <stdio.h> function\t: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));


    return 0;
}
