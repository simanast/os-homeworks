#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>

int main() {
    int rc = fork();
    char* file = "../test.txt";
    int n = 10;
    char buf[n];
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc > 0) { // parent
        int fd = open(file, O_RDONLY);
        sleep(1);
        read(fd, buf, n - 1);
        buf[n - 1] = '\0';
        close(fd);
        printf("%s\n", buf);
    }
    if (rc == 0) { // child
        unlink(file);
        exit(0);
    }

}