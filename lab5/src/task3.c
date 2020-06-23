#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv) {
    int n = 0;
    char* buf = argv[1] + 1;
    n = atoi(buf);
    char* filename = argv[2];

    struct stat st;
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "can't open file\n");
        exit(1);
    }
    stat(filename, &st);

    int filesize = st.st_size;
    int i = 0;
    char ch;
    int len = 0;

    char* buffer[n];
    int pos = filesize;

    while (i <= n && pos) {
        lseek(fd, -(filesize - pos + 1), SEEK_END);
        if (read(fd, &ch, 1) == -1) {
            printf("read error\n");
            exit(0);
        }
        pos--;
        len++;
        if (ch == '\n') {
            lseek(fd, -(filesize - pos) + 1, SEEK_END);
            buffer[i] = (char*) calloc(len + 1, sizeof(char));
            read(fd, buffer[i++], len);
            lseek(fd, -len, SEEK_CUR);
            len = 0;
            continue;
        }
        if (!pos) {
            buffer[i] = (char*) calloc(len + 1, sizeof(char));
            buffer[i][0] = ch;
            read(fd, buffer[i++] + 1, len);
            break;
        }
    }


    printf("%s\n", buffer[i - 1]);
    for (int j = i - 2; j >= 0; j--) {
        printf("%s", buffer[j]);
    }
    close(fd);

    return 0;
}

