#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char** argv) {
    char* filename = argv[1];
    struct stat st;
    stat(filename, &st);
    printf("stat:\n");
    printf("st_size = \t\t%ld\n", st.st_size);
    printf("st_mode = \t\t%u\n", st.st_mode);
    printf("uid = \t\t\t%u\n", st.st_uid);
    printf("st_blocks = \t\t%ld\n", st.st_blocks);
    printf("nlink = \t\t%ld\n", st.st_nlink);
}