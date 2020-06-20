#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("parent process started\n");
    int rc = fork();
    if (rc < 0) { // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) { // child
        printf("I am child process %d\n", getpid());
        sleep(2);
        exit(0);
    } else { // parent
        pid_t rc_ = wait(NULL);
        printf("parent process continued afted %d\n", rc_);
    }
    return 0;
}

