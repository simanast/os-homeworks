/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

int global;

void f() {
    int f_local = 5;
    printf("Address of f_local is \t%p\n", &f_local);
}

int main() {
    int local = 5;
    int local1 = 5;
    int local2 = 5;
    void* p = malloc(64);
    void* ptr = malloc(4);

    printf("Address of main is \t\t%p\n", main);
    printf("Address of global is \t%p\n", &global);
    printf("Address of p is \t\t%p\n", p);
    printf("Address of ptr is \t\t%p\n", ptr);
    printf("Address of &p is \t\t%p\n", &p);
    f();
    printf("Address of local is \t%p\n", &local);
    printf("Address of local1 is \t%p\n", &local1);
    printf("Address of local2 is \t%p\n", &local2);

    return 0;
}
