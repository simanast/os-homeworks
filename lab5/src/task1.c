#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int size = 300 * 1042;
    char record[size];
    char filepath[] = "test.txt";
    struct timeval tv1, tv2;

    gettimeofday(&tv1, NULL);
    int fd = creat(filepath, S_IRWXU);
    gettimeofday(&tv2, NULL);
    printf("time elapsed: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));

    if (fd == -1) {
        fprintf(stderr, "cant create file");
        _exit(1);
    }

    gettimeofday(&tv1, NULL);
    write(fd, record, size);

    gettimeofday(&tv2, NULL);
    printf("time elapsed: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));


    gettimeofday(&tv1, NULL);
    ftruncate(fd, 0);
    gettimeofday(&tv2, NULL);
    printf("time elapsed: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));

    gettimeofday(&tv1, NULL);
    close(fd);
    gettimeofday(&tv2, NULL);
    printf("time elapsed: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));


    gettimeofday(&tv1, NULL);
    remove(filepath);
    gettimeofday(&tv2, NULL);
    printf("time elapsed: %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec));

    return 0;
}
