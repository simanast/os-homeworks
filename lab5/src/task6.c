#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int PrintNameAndSize(int n, char* name, int size) {
    for (int i = 0; i < n; ++i) {
        printf("--");
    }
    printf("%s\t%dc\n", name, size);
}

int PrintName(int n, char* name) {
    for (int i = 0; i < n; ++i) {
        printf("--");
    }
    printf("%s\n", name);
}

void DepthSearch(int n, char* path) {
    DIR* dp  = opendir(path);
    if (!dp)
        return;
    struct dirent* dir;
    struct stat st;
    while (dir = readdir(dp)) {
        if (strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".") == 0)
            continue;
        char new_path[256];
        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, dir->d_name);
        stat(new_path, &st);
        PrintName(n, dir->d_name);
        DepthSearch(n++, new_path);
    }
    closedir(dp);
}

void DepthSearchWithSize(int n, char* path) {
    DIR* dp  = opendir(path);
    if (!dp)
        return;
    struct dirent* dir;
    struct stat st;
    while (dir = readdir(dp)) {
        if (strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".") == 0)
            continue;
        char new_path[256];
        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, dir->d_name);
        stat(new_path, &st);
        PrintNameAndSize(n, dir->d_name, st.st_size);
        DepthSearchWithSize(n++, new_path);
    }
    closedir(dp);
}



int main(int argc, char** argv) {
    char path[256];
    if (argc == 1) {
        getcwd(path, 256);
        DepthSearch(0, path);
    }
    if (argc == 2) {
        if (strcmp(argv[1], "-size") == 0) {
            getcwd(path, 256);
            DepthSearchWithSize(0, path);
        } else {
            strcpy(path, argv[1]);
            DepthSearch(0, path);
        }
    }
    if (argc == 3) {
        strcpy(path, argv[2]);
        DepthSearchWithSize(0, path);
    }
}