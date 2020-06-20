#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100;
    char *args[2];
    args[0] = "/bin/ls";
    args[1] = NULL;
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) { // child
        execv(args[0], args);
        exit(0);
    } else { // parent
        int rc_wait = wait(NULL);
    }
    return 0;
}

