#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int p[2];

    if (pipe(p) < 0)
        exit(1);

    int n = 23;
    char msg[] = "Child #1 says hi to #2";
    char buf[n];

    int rc1 = fork();
    if (rc1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork #1 failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // Child #1
        write(p[1], msg, n);
        close(p[1]);
    } else {
        // Parent process
        wait(NULL);
        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "fork #2 failed\n");
            exit(1);
        } else if (rc2 == 0) {
            // Child #2
            read(p[0], buf, n);
            printf("%s", buf);
        }
    }

    return 0;
}
