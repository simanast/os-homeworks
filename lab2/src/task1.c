#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) { // child
        printf("child: x = %d\n", x);
        x = 0;
        printf("child: new x = %d\n", x);
        exit(0);
    } else { // parent
        printf("parent: x = %d\n", x);
        x = 5;
        printf("parent: new x = %d\n", x);
    }
    return 0;
}

