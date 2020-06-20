#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void print_goodbye(int signo) {
    printf("goodbye\n");
    exit(0);
}

int main() {
    int parent_id = getpid();
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc > 0) { // parent
        signal(SIGCHLD, print_goodbye);
        sleep(1);
    }
    if (rc == 0) { // child
        printf("hello\n");
        kill(parent_id, SIGCHLD);
        exit(0);
    }
}
