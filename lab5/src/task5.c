#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

int main(int argc, char** argv) {
    char* path;
    int n;
    short l = 0;
    if (argc == 1) {
        char buf[256];
        getcwd(buf, 256);
        path = buf;
    }
    if (argc == 3) {
        l = 1;
        path = argv[2];
    }
    if (argc == 2) {
        if (strcmp(argv[1], "-l") == 0) {
            l = 1;
            char buf[256];
            getcwd(buf, 256);
            path = buf;
        } else
            path = argv[1];
    }

    DIR* dp = opendir(path);
    struct dirent* dir;
    struct stat st;
    strcat(path, "/");

    while (dir = readdir(dp)) {
        char* name = dir->d_name;
        printf("%s\n", name);
        char* buf = strdup(path);
        strcat(buf, name);
        free(buf);
        if (!l || stat(dir->d_name, &st) == -1) {
            continue;
        }
        printf("\tst_size = %ld, ", st.st_size);
        printf("st_mode = %u, ", st.st_mode);
        printf("uid = %u, ", st.st_uid);
        printf("gid = %u, ", st.st_gid);
        printf("st_blocks = %ld, ", st.st_blocks);
        printf("nlink = %ld", st.st_nlink);
        printf("\n");
    }
    closedir(dp);
}
